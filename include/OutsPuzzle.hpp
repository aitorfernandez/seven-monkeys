//
//  OutsPuzzle.hpp
//  SevenMonkeys
//

#ifndef OutsPuzzle_hpp
#define OutsPuzzle_hpp

#include "SevenMonkeys.hpp"

#include "Deck.hpp"

#include "HandEvaluator.hpp"
#include "HashHandEvaluator.hpp"

#include "PuzzleLayer.hpp"

class OutsPuzzle : public PuzzleLayer
{
public:

    OutsPuzzle();
    virtual ~OutsPuzzle();

    virtual bool init();

    CREATE_FUNC(OutsPuzzle);

    void update(float dt);

private:

    void deal();

    void addPlayers();
    void addCommunityCards();

    void setRankings();

    void showPlayerMessage();

    void findOuts();

    int compareHands(std::vector<int>& handA, std::vector<int>& handB);

    void addTokens();

    sevenmonkeys::Deck *mvpDeck;
    sevenmonkeys::HandEvaluator *mvpHandEval;
    sevenmonkeys::HashHandEvaluator *mvpHashHandEval;

    int mvAhead;
    int mvTotalOuts;
};

#endif /* OutsPuzzle_hpp */
