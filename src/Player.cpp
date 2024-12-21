//
//  Player.cpp
//  SevenMonkeys
//

#include "Player.hpp"

Player::Player()
{
    CCLOG("// Player %x Constructor", (int)(long)this);

    setHero(false);
    setWinner(false);

    setRanking(0);
    setTotalRanking(0);

    setAmount(0);
}

Player::~Player()
{
    CCLOG("// Player %x Destructor", (int)(long)this);

    mvCards.clear();
    mvCards.shrink_to_fit();
}

void Player::cleanUp()
{
    setHero(false);
    setWinner(false);

    setRanking(0);
    setTotalRanking(0);

    setAmount(0);

    mvCards.clear();
}

void Player::pushCard(int card)
{
    mvCards.push_back(card);
}

std::vector<int> Player::getCards()
{
    return mvCards;
}
