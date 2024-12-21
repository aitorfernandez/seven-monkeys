//
//  BestHandPuzzle.hpp
//  SevenMonkeys
//

#ifndef BestHandPuzzle_hpp
#define BestHandPuzzle_hpp

#include "SevenMonkeys.hpp"

#include "Deck.hpp"
#include "HashHandEvaluator.hpp"

#include "PuzzleLayer.hpp"

class BestHandPuzzle : public PuzzleLayer
{
public:

    BestHandPuzzle();
    virtual ~BestHandPuzzle();

    virtual bool init();

    CREATE_FUNC(BestHandPuzzle);

    void update(float dt);

private:

    void deal();

    void addPlayers();
    void addHoleCards();
    void addCommunityCards();

    void setRankings();

    sevenmonkeys::Deck *mvpDeck;
    sevenmonkeys::HashHandEvaluator *mvpHashHandEval;
};

#endif /* BestHandPuzzle_hpp */
