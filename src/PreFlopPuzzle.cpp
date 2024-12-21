//
//  PreFlop.cpp
//  SevenMonkeys
//

#include "PreFlopPuzzle.hpp"

USING_NS_CC;
USING_NS_SM;

PreFlopPuzzle::PreFlopPuzzle()
{
    CCLOG("// PreFlopPuzzle %x Constructor", (int)(long)this);

    mvpDeck = new Deck();

    mvpPreFlopEval = new PreFlopEvaluator();

    mvPokerOrder.push_back(BTN);
    mvPokerOrder.push_back(SB);
    mvPokerOrder.push_back(BB);
}

PreFlopPuzzle::~PreFlopPuzzle()
{
    CCLOG("// PreFlopPuzzle %x Destructor", (int)(long)this);

    CC_SAFE_DELETE(mvpDeck);
    CC_SAFE_DELETE(mvpPreFlopEval);

    mvPokerOrder.clear();
    mvPokerOrder.shrink_to_fit();

    mvPositionsBackup.clear();
    mvPositionsBackup.shrink_to_fit();

    mvPlayerActions.clear();
    mvPlayerActions.shrink_to_fit();

    mvPokerActions.clear();
    mvPokerActions.shrink_to_fit();
}

bool PreFlopPuzzle::init()
{
    if (!PuzzleLayer::init()) {
        return false;
    }

    if (UserDefault::getInstance()->getIntegerForKey("mode") == EASY) {
        mvPokerActionInterval = 2.f;
    }
    else if (UserDefault::getInstance()->getIntegerForKey("mode") == NORMAL) {
        mvPokerActionInterval = 2.f;
    }
    else {
        mvPokerActionInterval = 1.f;
    }

    mvPokerActions.push_back(RAISE);
    mvPokerActions.push_back(FOLD);

    if (UserDefault::getInstance()->getIntegerForKey("mode") > EASY) {
        mvPokerActions.push_back(CALL);
    }

    this->scheduleUpdate();

    return true;
}

void PreFlopPuzzle::update(float dt)
{
    if (isRunningPuzzle() && !isWaitingPuzzle()) {

        // Save a backup of the positions for future references

        if (mvPositionsBackup.empty()) {
            for (auto player : mtpPlayers) {
                mvPositionsBackup.push_back(player->mPositions);
            }

            switch (mtpPlayers.size()) {
                case (4): {
                    mvPokerOrder.push_back(CO);
                }
                break;

                case (6): {
                    mvPokerOrder.push_back(UTG);
                    mvPokerOrder.push_back(MP);
                    mvPokerOrder.push_back(CO);
                }
                break;
            }
        }

        mvHero = randInt((int32_t)mtpPlayers.size());


        addPlayers();


        // Find first player to speak

        for (auto const& player : mtpPlayers) {
            if (
                player->getPokerOrder() == CO ||
                player->getPokerOrder() == UTG) {

                mvCurrentPos = player->getPos();
                break;
            }
        }

        mvIsRunningPokerActions = true;


        this->schedule(CC_SCHEDULE_SELECTOR(PreFlopPuzzle::runPokerActions), 1.0f);

        setWaitingPuzzle(true);
    }

    if (mvIsRunningPokerActions && !isRunningPuzzle()) {
        this->unschedule(CC_SCHEDULE_SELECTOR(PreFlopPuzzle::runPokerActions));
    }
}

void PreFlopPuzzle::addPlayers()
{
    mvpDeck->placeCards();
    mvpDeck->shuffle();


    // Positions, shuffle and assign the new random position

    std::vector<int> randomPositions;

    for (int i = 0; i < mtpPlayers.size(); ++i)
        randomPositions.push_back(i);

    Rand::shuffle(randomPositions);

    for (int i = 0; i < mtpPlayers.size(); ++i)
        mtpPlayers[i]->setRandomPos(randomPositions[i]);


    // Set poker table order

    std::sort(mtpPlayers.begin(), mtpPlayers.end(), [](Player const* a, Player const* b) {
        return a->getRandomPos() < b->getRandomPos();
    });

    for (int i = 0; i < mtpPlayers.size(); ++i)
        mtpPlayers[i]->setPokerOrder(mvPokerOrder[i]);


    mtpPlayers[mvHero]->setHero(true);


    // Sit players starting in a random position

    int randomPosition = randInt((int32_t)mtpPlayers.size());

    for (int i = 0; i < mtpPlayers.size(); ++i) {

        randomPosition++;

        if (randomPosition >= mtpPlayers.size())
            randomPosition = 0;


        mtpPlayers[i]->setPos(randomPosition);


        auto position = mvPositionsBackup[randomPosition];


        auto spriteName = mtpPlayers[i]->isHero() ? "HeroSticker.png" : "VillainSticker" + std::to_string(i) + ".png";
        auto sprite = Sprite::createWithSpriteFrameName(spriteName);

        sprite->setOpacity(0);
        sprite->setNormalizedPosition(position.sticker);

        this->addChild(sprite, kZOrderPuzzle::players);

        sprite->runAction(FadeIn::create(.25f * i));


        switch (mtpPlayers[i]->getPokerOrder()) {
            case (BTN): {
                auto btn = Sprite::createWithSpriteFrameName("BTN.png");

                btn->setOpacity(0);
                btn->setNormalizedPosition(position.btn);

                this->addChild(btn, kZOrderPuzzle::btn);

                btn->runAction(FadeIn::create(.25f));
            }
            break;

            case (SB): {
                auto sb = Sprite::createWithSpriteFrameName("SB.png");

                sb->setOpacity(0);
                sb->setNormalizedPosition(position.blinds);

                this->addChild(sb, kZOrderPuzzle::blinds);

                sb->runAction(FadeIn::create(.25f));
            }
            break;

            case (BB): {
                auto bb = Sprite::createWithSpriteFrameName("BB.png");

                bb->setOpacity(0);
                bb->setNormalizedPosition(position.blinds);

                this->addChild(bb, kZOrderPuzzle::blinds);

                bb->runAction(FadeIn::create(.25f));
            }
            break;
        }

        // add hole cards

        for (short j = 0; j < 2; ++j) {
            int card = mvpDeck->dealCard();

            mtpPlayers[i]->pushCard(card);

            auto spriteCard = Sprite::createWithSpriteFrameName(mtpPlayers[i]->isHero() ? gHumanizeCards[card] + ".png" : "BackCard.png");

            spriteCard->setOpacity(0);
            spriteCard->setScale(0.6);
            spriteCard->setNormalizedPosition(Vec2(
                                                   position.sticker.x + .02f + (j * .035f),
                                                   position.sticker.y - (j * .01f)));

            this->addChild(spriteCard, kZOrderPuzzle::holeCards);

            spriteCard->runAction(FadeIn::create(.25f));
        }

    }

    randomPositions.clear();
    randomPositions.shrink_to_fit();
}

void PreFlopPuzzle::runPokerActions(float dt)
{
    // Hero decision

    if (mtpPlayers[mvHero]->getPos() == mvCurrentPos) {
        mvIsRunningPokerActions = false;

        this->unschedule(CC_SCHEDULE_SELECTOR(PreFlopPuzzle::runPokerActions));

        int correctAction = findPreFlopAction(mvHero);

        addTokens(correctAction);

        // Clean villains actions
        mvPlayerActions.clear();

        scheduleHelpPlayer();

        return;
    }

    if (
        HARD > UserDefault::getInstance()->getIntegerForKey("mode") &&
        dt == 1.0f) {

        // interval parameter will be updated without scheduling it again
        this->schedule(CC_SCHEDULE_SELECTOR(PreFlopPuzzle::runPokerActions), mvPokerActionInterval);
    }


    int action = findPreFlopAction(mvCurrentPos);

    if (!mvPlayerActions.empty()) {
        if (mvPlayerActions.back() == RAISE && action == RAISE) {
            action = RERAISE;
        }
    }

    mvPlayerActions.push_back(action);

    if (action == RERAISE || action == RAISE || action == CALL) {
        Game::instance().getSoundManager().playChipsSound();
    }

    auto sprite = Sprite::createWithSpriteFrameName("PokerAction" + std::to_string(action) + ".png");

    sprite->setNormalizedPosition(mvPositionsBackup[mvCurrentPos].sticker);

    this->addChild(sprite, kZOrderPuzzle::actions);

    sprite->runAction(Sequence::create(
                                       DelayTime::create(mvPokerActionInterval),
                                       FadeOut::create(.25f),
                                       RemoveSelf::create(true),
                                       nullptr));

    mvCurrentPos++;

    if (mvCurrentPos >= mtpPlayers.size())
        mvCurrentPos = 0;
}

void PreFlopPuzzle::addTokens(int& correctAction)
{
    Rand::shuffle(mvPokerActions);

    for (short i = 0; i < mtpTokens.size(); ++i) {

        auto spriteName = "PokerActionToken" + std::to_string(mvPokerActions[i]) + ".png";

        auto sprite = Sprite::createWithSpriteFrameName(spriteName);

        sprite->setOpacity(0);
        sprite->setNormalizedPosition(mtpTokens[i]->getPosition());

        this->addChild(sprite, kZOrderPuzzle::tokens, i);

        sprite->runAction(FadeIn::create(.25f * i));

        if (correctAction == mvPokerActions[i]) {
            mtpTokens[i]->setCorrect(true);

            mtRightAnswer = i;
        }
    }
}

int PreFlopPuzzle::findPreFlopAction(int player)
{
    if (mvPlayerActions.empty())
        return mvpPreFlopEval->evalOR(mtpPlayers[player]->getPokerOrder(), mtpPlayers[player]->getCards());

    int r = 0;

    for (auto action : mvPlayerActions) {
        if (action == RAISE || action == RERAISE) {
            r++;
        }
    }

    int preFlopAction;

    if (r == 0)
        preFlopAction = mvpPreFlopEval->evalROL(mtpPlayers[player]->getPokerOrder(), mtpPlayers[player]->getCards());

    if (r == 1)
        preFlopAction = mvpPreFlopEval->eval3bet(mtpPlayers[player]->getPokerOrder(), mtpPlayers[player]->getCards());

    if (r > 1)
        preFlopAction = mvpPreFlopEval->eval4bet(mtpPlayers[player]->getPokerOrder(), mtpPlayers[player]->getCards());

    // Should I CALL instead FOLD?

    if (
        UserDefault::getInstance()->getIntegerForKey("mode") > EASY &&
        preFlopAction == FOLD &&
        r < 2) {

        preFlopAction = mvpPreFlopEval->evalCall(mtpPlayers[player]->getPokerOrder(), mtpPlayers[player]->getCards());
    }

    return preFlopAction;
}
