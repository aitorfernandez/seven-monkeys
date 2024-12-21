//
//  PokerHandsPuzzle.hpp
//  SevenMonkeys
//

#ifndef PokerHandsPuzzle_hpp
#define PokerHandsPuzzle_hpp

#include "SevenMonkeys.hpp"

#include "PokerHands.hpp"

#include "PuzzleLayer.hpp"

class PokerHandsPuzzle : public PuzzleLayer
{
public:

    PokerHandsPuzzle();
    virtual ~PokerHandsPuzzle();

    virtual bool init();

    CREATE_FUNC(PokerHandsPuzzle);

    void update(float dt);

private:

    void deal();

    void addCommunityCards(int& handRanking);
    void addTokens(int& handRanking);

    sevenmonkeys::PokerHands *mvpPokerHands;
};

#endif /* PokerHandsPuzzle_hpp */
