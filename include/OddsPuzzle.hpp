//
//  OddsPuzzle.hpp
//  SevenMonkeys
//

#ifndef OddsPuzzle_hpp
#define OddsPuzzle_hpp

#include "SevenMonkeys.hpp"

#include "PokerAction.hpp"

#include "PuzzleLayer.hpp"

class OddsPuzzle : public PuzzleLayer
{
public:

    OddsPuzzle();
    virtual ~OddsPuzzle();

    virtual bool init();

    CREATE_FUNC(OddsPuzzle);

    void update(float dt);

private:

    void deal();

    void addPlayers();
    void addChips();

    bool mvIsRunningPokerActions;

    void runPokerActions(float dt);

    void addTokens();

    cocos2d::Label *mvpPotLabel;

    int mvBlind;

    int mvCurrentPlayer;

    int mvPrevAmount;
    int mvPrevAction;

    int mvPot;

    float mvPokerActionInterval;
};

#endif /* OddsPuzzle_hpp */
