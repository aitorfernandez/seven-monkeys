//
//  PreFlopPuzzle.hpp
//  SevenMonkeys
//

#ifndef PreFlopPuzzle_hpp
#define PreFlopPuzzle_hpp

#include "SevenMonkeys.hpp"

#include "Rand.hpp"
#include "Deck.hpp"

#include "PreFlopEvaluator.hpp"

#include "Player.hpp"

#include "PuzzleLayer.hpp"

class PreFlopPuzzle : public PuzzleLayer
{
public:

    PreFlopPuzzle();
    virtual ~PreFlopPuzzle();

    virtual bool init();

    CREATE_FUNC(PreFlopPuzzle);

    void update(float dt);

private:

    std::vector<sevenmonkeys::util::Positions> mvPositionsBackup;

    std::vector<int> mvPokerOrder;
    std::vector<int> mvPlayerActions;
    std::vector<int> mvPokerActions;

    int mvHero;
    int mvCurrentPos;

    float mvPokerActionInterval;

    sevenmonkeys::Deck *mvpDeck;

    sevenmonkeys::PreFlopEvaluator *mvpPreFlopEval;

    void addPlayers();

    bool mvIsRunningPokerActions;

    void runPokerActions(float dt);

    int findPreFlopAction(int player);

    void addTokens(int& correctAction);
};

#endif /* PreFlopPuzzle_hpp */
