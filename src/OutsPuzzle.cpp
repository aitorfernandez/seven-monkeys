//
//  OutsPuzzle.cpp
//  SevenMonkeys
//

#include "OutsPuzzle.hpp"

USING_NS_CC;
USING_NS_SM;

OutsPuzzle::OutsPuzzle()
{
    CCLOG("// OutsPuzzle %x Constructor", (int)(long)this);

    mvpDeck = new Deck();
    mvpHandEval = new HandEvaluator();
    mvpHashHandEval = new HashHandEvaluator();
}

OutsPuzzle::~OutsPuzzle()
{
    CCLOG("// OutsPuzzle %x Destructor", (int)(long)this);

    CC_SAFE_DELETE(mvpDeck);
    CC_SAFE_DELETE(mvpHandEval);
    CC_SAFE_DELETE(mvpHashHandEval);
}

bool OutsPuzzle::init()
{
    if (!PuzzleLayer::init()) {
        return false;
    }

    this->scheduleUpdate();

    return true;
}

void OutsPuzzle::update(float dt)
{
    if (isRunningPuzzle() && !isWaitingPuzzle()) {
        deal();
        setWaitingPuzzle(true);
        scheduleHelpPlayer();
    }
}

void OutsPuzzle::deal()
{
    Game::instance().getSoundManager().playDealSound();

    mvpDeck->placeCards();
    mvpDeck->shuffle();

    mtpPlayers[0]->setHero(true);

    addPlayers();
    addCommunityCards();

    setRankings();

    findOuts();

    addTokens();
}

void OutsPuzzle::addPlayers()
{
    // Players and hole cards

    for (short i = 0; i < mtpPlayers.size(); ++i) {
        auto spriteName = mtpPlayers[i]->isHero() ? "HeroSticker.png" : "VillainSticker" + std::to_string(UserDefault::getInstance()->getIntegerForKey("mode")) + ".png";

        auto sprite = Sprite::createWithSpriteFrameName(spriteName);

        sprite->setNormalizedPosition(mtpPlayers[i]->mPositions.sticker);
        sprite->setOpacity(0);

        this->addChild(sprite, kZOrderPuzzle::players);

        sprite->runAction(FadeIn::create(.25f * i));

        for (size_t j = 0; j < 2; ++j) {
            int card = mvpDeck->dealCard();

            mtpPlayers[i]->pushCard(card);

            auto spriteCard = Sprite::createWithSpriteFrameName(gHumanizeCards[card] + ".png");

            spriteCard->setScale(0.6);
            spriteCard->setOpacity(0);

            spriteCard->setNormalizedPosition(Vec2(
                                                   mtpPlayers[i]->mPositions.sticker.x + .02f + (j * .035f),
                                                   mtpPlayers[i]->mPositions.sticker.y - (j * .01f)));

            this->addChild(spriteCard, kZOrderPuzzle::holeCards);

            spriteCard->runAction(FadeIn::create(.25f * i));
        }
    }
}

void OutsPuzzle::addCommunityCards()
{
    for (size_t i = 0; i < 5; ++i) {

        cocos2d::Sprite* sprite;

        if (i > 3) {
            sprite = Sprite::createWithSpriteFrameName("BackCard.png");
        }
        else {
            int card = mvpDeck->dealCard();

            for (size_t j = 0; j < mtpPlayers.size(); ++j)
                mtpPlayers[j]->pushCard(card);

            sprite = Sprite::createWithSpriteFrameName(gHumanizeCards[card] + ".png");
        }

        sprite->setNormalizedPosition(Vec2(.3f + (i * .1f), .47f));
        sprite->setOpacity(0);

        this->addChild(sprite, kZOrderPuzzle::communityCards);

        sprite->runAction(FadeIn::create(.25f * i));
    }
}

void OutsPuzzle::setRankings()
{
    // Set rankings

    for (short i = 0; i < mtpPlayers.size(); ++i) {
        int ranking = mvpHandEval->eval6(mtpPlayers[i]->getCards());

        mtpPlayers[i]->setRanking(ranking);
    }

    if (mtpPlayers[0]->getRanking() > mtpPlayers[1]->getRanking()) {
        mvAhead = 1;
    }
    else if (mtpPlayers[0]->getRanking() < mtpPlayers[1]->getRanking()) {
        mvAhead = -1;
    }
    else {
        mvAhead = 0;
    }


    showPlayerMessage();
}

void OutsPuzzle::showPlayerMessage()
{
    std::string playerMessage;

    if (mvAhead == -1)
        playerMessage = "How many outs can you lose?";
    else
        playerMessage = "How many outs can you win?";

    auto sword = Sprite::createWithSpriteFrameName("sword.png");

    sword->setNormalizedPosition(Vec2(.6f, .08f));
    sword->setOpacity(0);

    this->addChild(sword);

    auto label = Label::createWithTTF(playerMessage, "fonts/OpenSans-ExtraBold.ttf", 10);

    label->setNormalizedPosition(Vec2(.5f, .075f));
    label->setOpacity(0);

    this->addChild(label);

    auto action = Sequence::create(
                                   FadeIn::create(.25f),
                                   DelayTime::create(2.f),
                                   FadeOut::create(.25f),
                                   RemoveSelf::create(true),
                                   nullptr);

    sword->runAction(action);
    label->runAction(action->clone());
}

void OutsPuzzle::findOuts()
{
    std::vector<int> outs;

    std::vector<int> cards = mvpDeck->getCards();

    std::vector<int> handA = mtpPlayers[0]->getCards();
    std::vector<int> handB = mtpPlayers[1]->getCards();

    while (!cards.empty()) {

        int card = cards.back();

        handA.push_back(card);
        handB.push_back(card);

        int ahead = compareHands(handA, handB);

        if ((0 <= mvAhead && 0 > ahead) ||
            (0 > mvAhead && 0 <= ahead)) {
            outs.push_back(card);
        }

        handA.pop_back();
        handB.pop_back();

        cards.pop_back();
    }

    std::sort(outs.begin(), outs.end());

    // Outs from 0 to +12

    mvTotalOuts = (int)outs.size() > 11 ? 12 : (int)outs.size();

    /*
        for (unsigned i = 0; i < outs.size(); ++i) {
            std::string str = gHumanizeCards[outs[i]];
            const char * c = str.c_str();

            CCLOG("// OutsPuzzle::findOuts %s", c);
        }
     */

    outs.clear();
    outs.shrink_to_fit();

    cards.clear();
    cards.shrink_to_fit();

    handA.clear();
    handA.shrink_to_fit();

    handB.clear();
    handB.shrink_to_fit();
}

int OutsPuzzle::compareHands(std::vector<int>& handA, std::vector<int>& handB)
{
    int totalRankA, totalRankB;

    totalRankA = mvpHashHandEval->eval(handA);
    totalRankB = mvpHashHandEval->eval(handB);

    // return < 0 if behind, 0 on tie, 1 if ahead

    if (totalRankA > totalRankB) {
        return 1;
    }
    else if (totalRankA < totalRankB) {
        return -1;
    }
    else {
        return 0;
    }
}

void OutsPuzzle::addTokens()
{
    std::vector<int> tokensValue { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    tokensValue.erase(std::remove(
                                  tokensValue.begin(),
                                  tokensValue.end(),
                                  mvTotalOuts), tokensValue.end());

    Rand::shuffle(tokensValue);

    int rndPos = randInt((int)mtpTokens.size());

    mtpTokens[rndPos]->setCorrect(true);

    tokensValue.insert((std::begin(tokensValue) + rndPos), mvTotalOuts);


    for (short i = 0; i < mtpTokens.size(); ++i) {
        auto sprite = Sprite::createWithSpriteFrameName("EmptyToken.png");

        if (tokensValue[i] == mvTotalOuts) {
            mtRightAnswer = i;
        }

        sprite->setNormalizedPosition(mtpTokens[i]->getPosition());
        sprite->setOpacity(0);

        this->addChild(sprite, kZOrderPuzzle::tokens, i);

        std::string value = tokensValue[i] == 12 ? "+" + std::to_string(tokensValue[i]) : std::to_string(tokensValue[i]);


        auto label = Label::createWithTTF(value, "fonts/OpenSans-ExtraBold.ttf", 11);

        label->setNormalizedPosition(Vec2(
                                          mtpTokens[i]->getPosition().x + .015,
                                          mtpTokens[i]->getPosition().y - .03f));
        label->setOpacity(0);

        this->addChild(label, kZOrderPuzzle::tokens, kTagsPuzzle::labels + i);


        sprite->runAction(FadeIn::create(.25f * i));
        label->runAction(FadeIn::create(.25f * i));
    }

    tokensValue.clear();
    tokensValue.shrink_to_fit();
}
