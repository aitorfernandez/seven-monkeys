//
//  PokerAction.hpp
//  SevenMonkeys
//

#ifndef PokerAction_hpp
#define PokerAction_hpp

#include "SevenMonkeys.hpp"

#include "Rand.hpp"

class PokerAction
{
public:

    PokerAction();
    ~PokerAction() = default;

    int chooseAction(int& prevAction, int& prevAmount);

    CC_SYNTHESIZE(int, mtBlind, Blind);
    CC_SYNTHESIZE(int, mtAmount, Amount);

private:

    int randomAction(const int a, const int b);
    int randomAction(const int a, const int b, const int c);
};

#endif /* PokerAction_hpp */
