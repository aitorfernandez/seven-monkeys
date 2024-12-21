//
//  PokerHandsPuzzle.cpp
//  SevenMonkeys
//

#include "PokerHandsPuzzle.hpp"

USING_NS_CC;
USING_NS_SM;

PokerHandsPuzzle::PokerHandsPuzzle()
{
    CCLOG("// PokerHandsPuzzle %x Constructor", (int)(long)this);

    mvpPokerHands = new PokerHands();
}

PokerHandsPuzzle::~PokerHandsPuzzle()
{
    CCLOG("// PokerHandsPuzzle %x Destructor", (int)(long)this);

    delete mvpPokerHands;
    mvpPokerHands = nullptr;
}

bool PokerHandsPuzzle::init()
{
    if (!PuzzleLayer::init()) {
        return false;
    }

    this->scheduleUpdate();

    return true;
}

void PokerHandsPuzzle::update(float dt)
{
    if (isRunningPuzzle() && !isWaitingPuzzle()) {
        deal();
        setWaitingPuzzle(true);
        scheduleHelpPlayer();
    }
}

void PokerHandsPuzzle::deal()
{
    Game::instance().getSoundManager().playDealSound();

    int handRanking = randInt(10);

    addCommunityCards(handRanking);
    addTokens(handRanking);
}

void PokerHandsPuzzle::addCommunityCards(int& handRanking)
{
    std::vector<int> communityCards = mvpPokerHands->getHand(handRanking);

    // Choose x when you want to work with copies.
    // Choose &x when you want to work with original items and may modify them.
    // Choose const &x when you want to work with original items and will not modify them.

    // for(int const& card : communityCards) {

    // ...

    if (UserDefault::getInstance()->getIntegerForKey("mode") > NORMAL) {
        Rand::shuffle(communityCards);
    }

    for (size_t i = 0; i < communityCards.size(); ++i) {
        auto sprite = Sprite::createWithSpriteFrameName(gHumanizeCards[communityCards[i]] + ".png");

        sprite->setNormalizedPosition(Vec2(.3f + (i * .1f), .47f));
        sprite->setOpacity(0);

        this->addChild(sprite, kZOrderPuzzle::communityCards);

        sprite->runAction(FadeIn::create(.25f * i));
    }

    communityCards.clear();
    communityCards.shrink_to_fit();
}

void PokerHandsPuzzle::addTokens(int& handRanking)
{
    std::vector<int> pokerPokerHandss {
        ROYAL_STRAIGHT_FLUSH,
        STRAIGHT_FLUSH,
        FOUR_OF_A_KIND,
        FULL_HOUSE,
        FLUSH,
        STRAIGHT,
        THREE_OF_A_KIND,
        TWO_PAIR,
        ONE_PAIR,
        HIGH_CARD
    };

    pokerPokerHandss.erase(std::remove(
                                       pokerPokerHandss.begin(),
                                       pokerPokerHandss.end(),
                                       handRanking), pokerPokerHandss.end());

    Rand::shuffle(pokerPokerHandss);

    int idx = randInt((int)mtpTokens.size());

    mtpTokens[idx]->setCorrect(true);

    pokerPokerHandss.insert((std::begin(pokerPokerHandss) + idx), handRanking);


    for (short i = 0; i < mtpTokens.size(); ++i) {
        auto spriteName = "PokerHandsToken" + std::to_string(mtpTokens[i]->isCorrect() ? handRanking : pokerPokerHandss[i]) + ".png";

        auto sprite = Sprite::createWithSpriteFrameName(spriteName);

        if (mtpTokens[i]->isCorrect()) {
            mtRightAnswer = i;
        }

        sprite->setNormalizedPosition(mtpTokens[i]->getPosition());
        sprite->setOpacity(0);

        this->addChild(sprite, kZOrderPuzzle::tokens, i);

        sprite->runAction(FadeIn::create(.25f * i));
    }

    pokerPokerHandss.clear();
    pokerPokerHandss.shrink_to_fit();
}
