//
//  Deck.cpp
//  SevenMonkeys
//

#include "deck.hpp"

NS_SM_BEGIN

Deck::Deck()
{
    CCLOG("// Deck %x Constructor", (int)(long)this);
}

Deck::~Deck()
{
    CCLOG("// Deck %x Destructor", (int)(long)this);

    mtCards.clear();
    mtCards.shrink_to_fit();
}

void Deck::placeCards()
{
    mtCards.clear();

    for (short i = 0; i < STANDARD_52_CARD_DECK; ++i) {
        mtCards.push_back(i);
    }
}

void Deck::shuffle()
{
    Rand::shuffle(mtCards);
}

int Deck::dealCard()
{
    int card = mtCards.back();
    mtCards.pop_back();

    return card;
}

void Deck::removeCard(int card)
{
    // https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
    mtCards.erase(std::remove(mtCards.begin(), mtCards.end(), card), mtCards.end());
}

NS_SM_END
