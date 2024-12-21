//
//  FlopTexturePuzzle.hpp
//  SevenMonkeys
//

#ifndef FlopTexturePuzzle_hpp
#define FlopTexturePuzzle_hpp

#include "SevenMonkeys.hpp"

#include "Deck.hpp"
#include "FlopEvaluator.hpp"

#include "PuzzleLayer.hpp"

class FlopTexturePuzzle : public PuzzleLayer
{
public:

    FlopTexturePuzzle();
    virtual ~FlopTexturePuzzle();

    virtual bool init();

    CREATE_FUNC(FlopTexturePuzzle);

    void update(float dt);

private:

    void deal();

    void addCommunityCards();
    void addTokens();

    void showPlayerMessage();

    sevenmonkeys::Deck *mvpDeck;
    sevenmonkeys::FlopEvaluator *mvpFlopEval;

    std::vector<int> mvCards;

    int mvSuit;
    int mvMatch;
    int mvConnect;
};

#endif /* FlopTexturePuzzle_hpp */
