//
//  BestHandPuzzle.cpp
//  SevenMonkeys
//

#include "BestHandPuzzle.hpp"

USING_NS_CC;
USING_NS_SM;

BestHandPuzzle::BestHandPuzzle()
{
    CCLOG("// BestHandPuzzle %x Constructor", (int)(long)this);

    mvpDeck = new Deck();
    mvpHashHandEval = new HashHandEvaluator();
}

BestHandPuzzle::~BestHandPuzzle()
{
    CCLOG("// BestHandPuzzle %x Destructor", (int)(long)this);

    CC_SAFE_DELETE(mvpDeck);
    CC_SAFE_DELETE(mvpHashHandEval);
}

bool BestHandPuzzle::init()
{
    if (!PuzzleLayer::init()) {
        return false;
    }

    this->scheduleUpdate();

    return true;
}

void BestHandPuzzle::update(float dt)
{
    if (isRunningPuzzle() && !isWaitingPuzzle()) {
        deal();
        setWaitingPuzzle(true);
        scheduleHelpPlayer();
    }
}

void BestHandPuzzle::deal()
{
    Game::instance().getSoundManager().playDealSound();

    mvpDeck->placeCards();
    mvpDeck->shuffle();

    addPlayers();

    addHoleCards();
    addCommunityCards();

    setRankings();
}

void BestHandPuzzle::addPlayers()
{
    for (short i = 0; i < mtpPlayers.size(); ++i) {
        auto spriteName = "VillainSticker" + std::to_string(i) + ".png";
        auto sprite = Sprite::createWithSpriteFrameName(spriteName);

        sprite->setNormalizedPosition(mtpPlayers[i]->mPositions.sticker);
        sprite->setOpacity(0);

        this->addChild(sprite, kZOrderPuzzle::players, i);

        sprite->runAction(FadeIn::create(.25f * i));
    }
}

void BestHandPuzzle::addHoleCards()
{
    for (short i = 0; i < mtpPlayers.size(); ++i) {
        for (short j = 0; j < 2; ++j) {
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

void BestHandPuzzle::addCommunityCards()
{
    for (short i = 0; i < 5; ++i) {
        int card = mvpDeck->dealCard();

        for (short j = 0; j < mtpPlayers.size(); ++j)
            mtpPlayers[j]->pushCard(card);

        auto sprite = Sprite::createWithSpriteFrameName(gHumanizeCards[card] + ".png");

        sprite->setNormalizedPosition(Vec2(.3f + (i * .1f), .47f));
        sprite->setOpacity(0);

        this->addChild(sprite, kZOrderPuzzle::communityCards);

        sprite->runAction(FadeIn::create(.25f * i));
    }
}

void BestHandPuzzle::setRankings()
{
    // Set rankinkg for each player

    for (short i = 0; i < mtpPlayers.size(); ++i) {
        int totalRanking = mvpHashHandEval->eval(mtpPlayers[i]->getCards());

        mtpPlayers[i]->setTotalRanking(totalRanking);
        mtpPlayers[i]->setRanking(mvpHashHandEval->getRanking(totalRanking));
    }

    // Find winner

    auto player = *(std::min_element(mtpPlayers.begin(), mtpPlayers.end(), [] (Player const* lp, Player const* rp) {
        if (lp->getRanking() < rp->getRanking())
            return true;

        if (rp->getRanking() < lp->getRanking())
            return false;

        if (lp->getTotalRanking() < rp->getTotalRanking())
            return true;

        if (rp->getTotalRanking() < lp->getTotalRanking())
            return false;

        return false;
    }));

    player->setWinner(true);

    for (short i = 0; i < mtpPlayers.size(); ++i) {
        if (player->getRanking() == mtpPlayers[i]->getRanking() && player->getTotalRanking() == mtpPlayers[i]->getTotalRanking()) {

            mtRightAnswer = i;

            // ANSWER
            // this->getChildByTag(i)->setColor(Color3B::YELLOW);

            break;
        }
    }


}
