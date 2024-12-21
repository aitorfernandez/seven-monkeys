//
//  OrderPuzzle.cpp
//  SevenMonkeys
//
//

#include "OrderPuzzle.hpp"

USING_NS_CC;
USING_NS_SM;

OrderPuzzle::OrderPuzzle()
{
    CCLOG("// OrderPuzzle %x Constructor", (int)(long)this);
}

OrderPuzzle::~OrderPuzzle()
{
    CCLOG("// OrderPuzzle %x Destructor", (int)(long)this);

    mvPositionsBackup.clear();
    mvPositionsBackup.shrink_to_fit();
}

bool OrderPuzzle::init()
{
    if (!PuzzleLayer::init()) {
        return false;
    }

    this->scheduleUpdate();

    return true;
}

void OrderPuzzle::update(float dt)
{
    if (isRunningPuzzle() && !isWaitingPuzzle()) {

        // Save the positions for future references

        if (mvPositionsBackup.empty()) {
            for (auto player : mtpPlayers) {
                mvPositionsBackup.push_back(player->mPositions);
            }
        }

        movePlayers();
        setWaitingPuzzle(true);
        scheduleHelpPlayer();
    }
}

void OrderPuzzle::movePlayers()
{
    // Move this vector at the beggining to avoid repeat all the time

    std::vector<int> tableOrder {
        BTN,
        SB,
        BB
    };

    switch (mtpPlayers.size()) {
        case (4): {
            tableOrder.push_back(CO);
        }
        break;

        case (6): {
            tableOrder.push_back(UTG);
            tableOrder.push_back(MP);
            tableOrder.push_back(CO);
        }
        break;
    }

    int hero = randInt((int32_t)mtpPlayers.size());

    addPlayers(tableOrder, hero);
    addTokens(tableOrder, hero);

    tableOrder.clear();
    tableOrder.shrink_to_fit();
}

void OrderPuzzle::addPlayers(std::vector<int> &tableOrder, int& hero)
{
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
        mtpPlayers[i]->setPokerOrder(tableOrder[i]);


    mtpPlayers[hero]->setHero(true);


    // Sit players starting in a random position

    int randomPosition = randInt((int32_t)mtpPlayers.size());

    for (int i = 0; i < mtpPlayers.size(); ++i) {

        randomPosition++;

        if (randomPosition == mtpPlayers.size())
            randomPosition = 0;

        mtpPlayers[i]->setPos(randomPosition);


        auto position = mvPositionsBackup[randomPosition];

        auto spriteName = mtpPlayers[i]->isHero() ? "HeroSticker.png" : "VillainSticker" + std::to_string(UserDefault::getInstance()->getIntegerForKey("mode")) + ".png";

        auto sprite = Sprite::createWithSpriteFrameName(spriteName);

        sprite->setNormalizedPosition(position.sticker);
        sprite->setOpacity(0);

        this->addChild(sprite, kZOrderPuzzle::players);

        sprite->runAction(FadeIn::create(.25f * i));

        switch (mtpPlayers[i]->getPokerOrder()) {
            case (BTN): {
                auto btn = Sprite::createWithSpriteFrameName("BTN.png");
                btn->setNormalizedPosition(position.btn);

                this->addChild(btn, kZOrderPuzzle::btn);
            }
            break;

            case (SB): {
                auto sb = Sprite::createWithSpriteFrameName("SB.png");
                sb->setNormalizedPosition(position.blinds);

                this->addChild(sb, kZOrderPuzzle::blinds);
            }
            break;

            case (BB): {
                auto bb = Sprite::createWithSpriteFrameName("BB.png");
                bb->setNormalizedPosition(position.blinds);

                this->addChild(bb, kZOrderPuzzle::blinds);
            }
            break;
        }
    }

    randomPositions.clear();
    randomPositions.shrink_to_fit();
}

void OrderPuzzle::addTokens(std::vector<int>& tableOrder, int& hero)
{
    tableOrder.erase(std::remove(
                                 tableOrder.begin(),
                                 tableOrder.end(),
                                 mtpPlayers[hero]->getPokerOrder()), tableOrder.end());

    Rand::shuffle(tableOrder);

    int idx = randInt((int)mtpTokens.size());

    mtpTokens[idx]->setCorrect(true);

    tableOrder.insert((std::begin(tableOrder) + idx), mtpPlayers[hero]->getPokerOrder());

    for (short i = 0; i < mtpTokens.size(); ++i) {
        auto spriteName = "OrderToken" + std::to_string(mtpTokens[i]->isCorrect() ? mtpPlayers[hero]->getPokerOrder() : tableOrder[i]) + ".png";

        auto sprite = Sprite::createWithSpriteFrameName(spriteName);

        if (mtpTokens[i]->isCorrect()) {
            mtRightAnswer = i;
        }

        sprite->setNormalizedPosition(mtpTokens[i]->getPosition());
        sprite->setOpacity(0);

        this->addChild(sprite, kZOrderPuzzle::tokens, i);

        sprite->runAction(FadeIn::create(.25f * i));
    }
}
