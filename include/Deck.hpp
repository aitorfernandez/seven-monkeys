//
//  Deck.hpp
//  SevenMonkeys
//

#ifndef Deck_hpp
#define Deck_hpp

#include "SevenMonkeys.hpp"

#include "Rand.hpp"

NS_SM_BEGIN

class Deck
{
public:

    Deck();
    virtual ~Deck();

    // All cards back into the deck
    void placeCards();

    void shuffle();

    // Obtain the next card in the deck
    int dealCard();

    CC_SYNTHESIZE(std::vector<int>, mtCards, Cards);

    void removeCard(int card);
};

NS_SM_END

#endif /* Deck_hpp */
