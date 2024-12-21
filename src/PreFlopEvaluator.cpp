//
//  PreFlopEvaluator.cpp
//  SevenMonkeys
//

#include "PreFlopEvaluator.hpp"

NS_SM_BEGIN

static int c0, c1, preFlopAction;

PreFlopEvaluator::PreFlopEvaluator()
{

}

int PreFlopEvaluator::evalOR(int order, std::vector<int> cards)
{
    sortCards(cards);

    if (suit[c0] != suit[c1]) {
        preFlopAction = doingOR[12 - rank[c1]][12 - rank[c0]];
    }
    else {
        preFlopAction = doingOR[12 - rank[c0]][12 - rank[c1]];
    }

    if (preFlopAction == 0) {
        return FOLD;
    }

    switch (order) {
        case (MP):
        case (UTG): {
            preFlopAction = (preFlopAction == 4) ? RAISE : FOLD;
        }
        break;

        case (CO): {
            preFlopAction = (preFlopAction == 4 ||
                             preFlopAction == 3) ? RAISE : FOLD;
        }
        break;

        case (BTN): {
            preFlopAction = (preFlopAction == 4 ||
                             preFlopAction == 3 ||
                             preFlopAction == 2) ? RAISE : FOLD;
        }
        break;

        case (BB):
        case (SB): {
            preFlopAction = (preFlopAction != 0) ? RAISE : FOLD;
        }
        break;
    }

    return preFlopAction;
}

int PreFlopEvaluator::evalROL(int order, std::vector<int> cards)
{
    sortCards(cards);

    if (suit[c0] != suit[c1]) {
        preFlopAction = doingROL[12 - rank[c1]][12 - rank[c0]];
    }
    else {
        preFlopAction = doingROL[12 - rank[c0]][12 - rank[c1]];
    }

    if (preFlopAction == 0) {
        return FOLD;
    }

    switch (order) {
        case (MP):
        case (UTG):
        case (CO): {
            preFlopAction = (preFlopAction == 4) ? RAISE : FOLD;
        }
        break;

        case (BTN):
        case (BB):
        case (SB): {
            preFlopAction = (preFlopAction == 4 ||
                             preFlopAction == 3) ? RAISE : FOLD;
        }
            break;
    }

    return preFlopAction;
}

int PreFlopEvaluator::eval3bet(int order, std::vector<int> cards)
{
    sortCards(cards);

    if (suit[c0] != suit[c1]) {
        preFlopAction = doing3bet[12 - rank[c1]][12 - rank[c0]];
    }
    else {
        preFlopAction = doing3bet[12 - rank[c0]][12 - rank[c1]];
    }

    if (preFlopAction == 0) {
        return FOLD;
    }

    switch (order) {
        case (MP):
        case (UTG):
        case (CO): {
            preFlopAction = (preFlopAction == 4 ||
                             preFlopAction == 3) ? RAISE : FOLD;
        }
        break;

        case (BTN):
        case (BB):
        case (SB): {
            preFlopAction = (preFlopAction == 4 ||
                             preFlopAction == 3 ||
                             preFlopAction == 2) ? RAISE : FOLD;
        }
        break;
    }

    return preFlopAction;
}

int PreFlopEvaluator::eval4bet(int order, std::vector<int> cards)
{
    sortCards(cards);

    if (suit[c0] != suit[c1]) {
        preFlopAction = doing4bet[12 - rank[c1]][12 - rank[c0]];
    }
    else {
        preFlopAction = doing4bet[12 - rank[c0]][12 - rank[c1]];
    }

    if (preFlopAction == 0) {
        return FOLD;
    }

    switch (order) {
        case (MP):
        case (UTG):
        case (CO): {
            preFlopAction = (preFlopAction == 4) ? RAISE : FOLD;
        }
            break;

        case (BTN):
        case (BB):
        case (SB): {
            preFlopAction = (preFlopAction == 4 ||
                             preFlopAction == 3 ||
                             preFlopAction == 2) ? RAISE : FOLD;
        }
            break;
    }

    return preFlopAction;
}

int PreFlopEvaluator::evalCall(int order, std::vector<int> cards)
{
    sortCards(cards);

    if (suit[c0] != suit[c1]) {
        preFlopAction = doingCall[12 - rank[c1]][12 - rank[c0]];
    }
    else {
        preFlopAction = doingCall[12 - rank[c0]][12 - rank[c1]];
    }

    if (preFlopAction == 0) {
        return FOLD;
    }

    switch (order) {
        case (SB):
        case (BB): {
            preFlopAction = (preFlopAction == 4) ? CALL : FOLD;
        }
        break;

        case (MP): {
            preFlopAction = (preFlopAction == 3) ? CALL : FOLD;
        }
        break;

        case (CO):
        case (BTN): {
            preFlopAction = (preFlopAction == 4 ||
                             preFlopAction == 3 ||
                             preFlopAction == 2) ? CALL : FOLD;
        }
            break;
    }

    return preFlopAction;
}

void PreFlopEvaluator::sortCards(std::vector<int>& cards)
{
    std::sort(cards.begin(), cards.end(), util::sortDescendingOrder());

    c0 = cards[0];
    c1 = cards[1];
}

NS_SM_END
