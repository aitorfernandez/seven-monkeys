//
//  OddsPuzzle.cpp
//  SevenMonkeys
//

#include "OddsPuzzle.hpp"

USING_NS_CC;
USING_NS_SM;

OddsPuzzle::OddsPuzzle()
{
    CCLOG("// OddsPuzzle %x Constructor", (int)(long)this);
}

OddsPuzzle::~OddsPuzzle()
{
    CCLOG("// OddsPuzzle %x Destructor", (int)(long)this);

    if (mvpPotLabel) {
        mvpPotLabel->removeFromParentAndCleanup(true);
        mvpPotLabel = nullptr;
    }
}

bool OddsPuzzle::init()
{
    if (!PuzzleLayer::init()) {
        return false;
    }

    if (UserDefault::getInstance()->getIntegerForKey("mode") == EASY) {
        mvPokerActionInterval = 2.f;
    }
    else if (UserDefault::getInstance()->getIntegerForKey("mode") == NORMAL) {
        mvPokerActionInterval = 1.5f;
    }
    else {
        mvPokerActionInterval = 1.f;
    }

    this->scheduleUpdate();

    return true;
}

void OddsPuzzle::update(float dt)
{
    if (isRunningPuzzle() && !isWaitingPuzzle()) {
        deal();
        setWaitingPuzzle(true);
    }

    if (mvIsRunningPokerActions && !isRunningPuzzle()) {
        this->unschedule(CC_SCHEDULE_SELECTOR(OddsPuzzle::runPokerActions));
    }
}

void OddsPuzzle::deal()
{
    mvBlind = 2;

    if (UserDefault::getInstance()->getIntegerForKey("mode") > NORMAL) {
        mvBlind = 3;
    }

    mvPot = randInt(1, (int)mtpPlayers.size()) * mvBlind;


    addPlayers();
    addChips();


    mvPrevAmount = 0;
    mvPrevAction = 0;

    mvCurrentPlayer = 1;

    mvIsRunningPokerActions = true;

    this->schedule(CC_SCHEDULE_SELECTOR(OddsPuzzle::runPokerActions), 1.0f);
}

void OddsPuzzle::addPlayers()
{
    // std::vector<int> stacks { 1000, 2000, 2500, 5000 };
    std::vector<int> stacks { 1000, 2000 };

    mtpPlayers[0]->setHero(true);

    for (short i = 0; i < mtpPlayers.size(); ++i) {

        mtpPlayers[i]->setAmount(stacks[randInt((int32_t)stacks.size())]);

        auto spriteName = mtpPlayers[i]->isHero() ? "HeroSticker.png" : "VillainSticker" + std::to_string(i) + ".png";
        auto sprite = Sprite::createWithSpriteFrameName(spriteName);

        sprite->setOpacity(0);
        sprite->setNormalizedPosition(mtpPlayers[i]->mPositions.sticker);

        this->addChild(sprite, kZOrderPuzzle::players);

        sprite->runAction(FadeIn::create(.25f * i));
    }

    stacks.clear();
    stacks.shrink_to_fit();
}

void OddsPuzzle::addChips()
{
    for (short i = 0; i < mtpPlayers.size(); ++i) {
        auto stack = Sprite::createWithSpriteFrameName("Stack" + std::to_string(mtpPlayers[i]->getAmount()) + ".png");

        stack->setOpacity(0);
        stack->setNormalizedPosition(mtpPlayers[i]->mPositions.stack);

        this->addChild(stack, kZOrderPuzzle::stack);

        stack->runAction(FadeIn::create(.25f * i));
    }

    // Pot

    auto pot = Sprite::createWithSpriteFrameName("Pot.png");

    pot->setOpacity(0);
    pot->setNormalizedPosition(Vec2(.5f, .42f));

    this->addChild(pot, kZOrderPuzzle::pot);

    pot->runAction(FadeIn::create(.25f));

    // Marker

    auto potMarker = Sprite::createWithSpriteFrameName("ChipsMarker.png");

    potMarker->setOpacity(0);
    potMarker->setNormalizedPosition(Vec2(.5f, .5f));

    this->addChild(potMarker, kZOrderPuzzle::pot);

    potMarker->runAction(FadeIn::create(.25f));

    // Label

    mvpPotLabel = Label::createWithTTF(std::to_string(mvPot), "fonts/OpenSans-ExtraBold.ttf", 11);

    mvpPotLabel->setOpacity(0);
    mvpPotLabel->setNormalizedPosition(Vec2(.5f, .518f));

    this->addChild(mvpPotLabel, kZOrderPuzzle::pot);

    mvpPotLabel->runAction(FadeIn::create(.25f));
}


void OddsPuzzle::runPokerActions(float dt)
{
    if (
        HARD > UserDefault::getInstance()->getIntegerForKey("mode") &&
        dt == 1.0f) {
        // interval parameter will be updated without scheduling it again
        this->schedule(CC_SCHEDULE_SELECTOR(OddsPuzzle::runPokerActions), mvPokerActionInterval);
    }

    PokerAction *pokerAction = new PokerAction();

    pokerAction->setBlind(mvBlind);

    int action = pokerAction->chooseAction(mvPrevAction, mvPrevAmount);

    auto fadeOut = FadeOut::create(.25f);

    cocos2d::Sprite* pokerActionSprite;

    if (
        action == BET ||
        action == RAISE ||
        action == RERAISE ||
        action == CALL) {

        Game::instance().getSoundManager().playChipsSound();

        pokerActionSprite = Sprite::createWithSpriteFrameName("PokerActionWithValue" + std::to_string(action) + ".png");


        auto amount = Label::createWithTTF(std::to_string(pokerAction->getAmount()), "fonts/OpenSans-ExtraBold.ttf", 11);

        amount->setNormalizedPosition(Vec2(
                                           mtpPlayers[mvCurrentPlayer]->mPositions.sticker.x + .025f,
                                           mtpPlayers[mvCurrentPlayer]->mPositions.sticker.y));

        this->addChild(amount, kZOrderPuzzle::actions + 1);

        amount->runAction(Sequence::create(
                                           DelayTime::create(mvPokerActionInterval),
                                           fadeOut->clone(),
                                           RemoveSelf::create(true),
                                           nullptr));
    }
    else {
        pokerActionSprite = Sprite::createWithSpriteFrameName("PokerAction" + std::to_string(action) + ".png");
    }


    pokerActionSprite->setNormalizedPosition(mtpPlayers[mvCurrentPlayer]->mPositions.sticker);

    this->addChild(pokerActionSprite, kZOrderPuzzle::actions);


    pokerActionSprite->runAction(Sequence::create(
                                                  DelayTime::create(mvPokerActionInterval),
                                                  fadeOut,
                                                  RemoveSelf::create(true),
                                                  nullptr));

    // Save the data for the next player
    mvPrevAction = action;
    mvPrevAmount = pokerAction->getAmount();

    mvPot += pokerAction->getAmount();

    mvpPotLabel->setString(std::to_string(mvPot));


    CC_SAFE_DELETE(pokerAction);


    mvCurrentPlayer++;

    if (mvCurrentPlayer >= mtpPlayers.size()) {
        mvIsRunningPokerActions = false;

        this->unschedule(CC_SCHEDULE_SELECTOR(OddsPuzzle::runPokerActions));

        addTokens();

        scheduleHelpPlayer();
    }
}

void OddsPuzzle::addTokens()
{
    int odds = (int)((float)((mvPrevAmount / (float)(mvPot + mvPrevAmount)) * 100));

    std::vector<int> randomTokens;

    randomTokens.push_back(odds);

    for (short i = 0; i < mtpTokens.size() - 1; ++i) {
        if (randBool() || odds > 90) {
            randomTokens.push_back(randInt(1, odds));
        }
        else {
            randomTokens.push_back(randInt(odds, 90));
        }
    }

    Rand::shuffle(randomTokens);

    for (short i = 0; i < mtpTokens.size(); ++i) {
        auto sprite = Sprite::createWithSpriteFrameName("EmptyToken.png");

        sprite->setOpacity(0);
        sprite->setNormalizedPosition(mtpTokens[i]->getPosition());

        this->addChild(sprite, kZOrderPuzzle::tokens, i);

        sprite->runAction(FadeIn::create(.25f * i));


        int percent = randomTokens[i];

        if (percent == odds) {
            mtRightAnswer = i;

            mtpTokens[i]->setCorrect(true);
        }

        auto label = Label::createWithTTF(std::to_string(percent) + "%", "fonts/OpenSans-ExtraBold.ttf", 11);

        label->setOpacity(0);
        label->setNormalizedPosition(Vec2(mtpTokens[i]->getPosition().x + .02, mtpTokens[i]->getPosition().y - .03f));

        this->addChild(label, kZOrderPuzzle::tokens, kTagsPuzzle::labels);

        label->runAction(FadeIn::create(.25f));
    }

    randomTokens.clear();
    randomTokens.shrink_to_fit();
}
