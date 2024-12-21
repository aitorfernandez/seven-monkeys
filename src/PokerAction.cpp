//
//  PokerAction.cpp
//  SevenMonkeys
//

#include "PokerAction.hpp"

USING_NS_SM;

PokerAction::PokerAction()
{
    CCLOG("// PokerAction %x Constructor", (int)(long)this);
}

int PokerAction::chooseAction(int& prevAction, int& prevAmount)
{
    int action;

    switch (prevAction) {
        // No previous action
        case (0): {
            action = randomAction(BET, CHECK);
        }
        break;

        case (BET):
        case (RAISE):
        case (CALL): {
            action = randomAction(RAISE, FOLD, CALL);
        }
        break;

        case (RERAISE): {
            action = randomAction(RERAISE, FOLD, CALL);
        }
        break;

        case (FOLD): {
            action = FOLD;
        }
        break;

        case (CHECK): {
            // action = randomChoices(BET, CHECK);
            action = BET;
        }
        break;
    }

    switch (action) {
        case (BET): {
            setAmount(getBlind() * randInt(1, 3));
        }
        break;

        case (RAISE): {
            setAmount(prevAmount + (getBlind() * randInt(1, 3)));
        }
        break;

        case (RERAISE): {
            setAmount(prevAmount + (getBlind() * randInt(3, 5)));
        }
        break;

        case (FOLD):
        case (CALL):
        case (CHECK): {
            setAmount(prevAmount);
        }
        break;
    }

    return action;
}

int PokerAction::randomAction(const int a, const int b)
{
    int rnd = randInt(2);

    if (rnd == 0)
        return a;
    else
        return b;
}

int PokerAction::randomAction(const int a, const int b, const int c)
{
    int rnd = randInt(3);

    if (rnd == 0)
        return a;
    else if (rnd == 1)
        return b;
    else
        return c;
}
