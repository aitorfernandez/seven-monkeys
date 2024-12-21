//
//  HandEvaluator.cpp
//  SevenMonkeys
//

#include "HandEvaluator.hpp"

NS_SM_BEGIN

static int c0, c1, c2, c3, c4;

HandEvaluator::HandEvaluator()
{

}

int HandEvaluator::eval6(std::vector<int> cards)
{
    std::sort(cards.begin(), cards.end(), util::sortDescendingOrder());

    int v, rankValue = 10;

    c0 = rank[cards[0]];
    c1 = rank[cards[1]];
    c2 = rank[cards[2]];
    c3 = rank[cards[3]];
    c4 = rank[cards[4]];

    v = getRanking(cards[0], cards[1], cards[2], cards[3], cards[4]);
    if (v < rankValue) rankValue = v;

    c4 = rank[cards[5]];

    v = getRanking(cards[0], cards[1], cards[2], cards[3], cards[5]);
    if (v < rankValue) rankValue = v;

    c3 = rank[cards[4]];
    c4 = rank[cards[5]];

    v = getRanking(cards[0], cards[1], cards[2], cards[4], cards[5]);
    if (v < rankValue) rankValue = v;

    c2 = rank[cards[3]];
    c3 = rank[cards[4]];
    c4 = rank[cards[5]];

    v = getRanking(cards[0], cards[1], cards[3], cards[4], cards[5]);
    if (v < rankValue) rankValue = v;

    c1 = rank[cards[2]];
    c2 = rank[cards[3]];
    c3 = rank[cards[4]];
    c4 = rank[cards[5]];

    v = getRanking(cards[0], cards[2], cards[3], cards[4], cards[5]);
    if (v < rankValue) rankValue = v;

    c0 = rank[cards[1]];
    c1 = rank[cards[2]];
    c2 = rank[cards[3]];
    c3 = rank[cards[4]];
    c4 = rank[cards[5]];

    v = getRanking(cards[1], cards[2], cards[3], cards[4], cards[5]);
    if (v < rankValue) rankValue = v;

    return rankValue;
}


int HandEvaluator::getRanking(int& card1, int& card2, int& card3, int& card4, int& card5)
{
    bool flush = (suit[card1] == suit[card2] && suit[card2] == suit[card3] && suit[card3] == suit[card4] && suit[card4] == suit[card5]);
    bool straight = false;

    int diff = 0;

    if (c0 != c1) diff++;
    if (c1 != c2) diff++;
    if (c2 != c3) diff++;
    if (c3 != c4) diff++;

    if (diff == 4) {
        straight = (c0 - 4 == c4) && (c1 - 2 == c3) && (c2 - 2 == c4);
    }

    if (straight && flush) {
        return STRAIGHT_FLUSH;
    }

    if (diff == 1) {
        // x x x x y, y x x x x
        if (c0 == c3 || c1 == c4) {
            return FOUR_OF_A_KIND;
        }

        // x x x y y, x x y y y
        if (c0 == c2 || c2 == c4) {
            return FULL_HOUSE;
        }
    }

    if (flush) {
        return FLUSH;
    }

    if (straight) {
        return STRAIGHT;
    }

    if (diff == 2) {
        // x x x b c, a x x x c, a b x x x
        if (c0 == c2 || c1 == c3 || c2 == c4) {
            return THREE_OF_A_KIND;
        }

        // x x y y a, x x a y y, a x x y y
        if (c0 == c1 || c2 == c3 || c3 == c4) {
            if (c3 == c4) return TWO_PAIR;
        }
    }

    if (diff == 3) {
        // x x a b c, a x x b c, a b x x c, a b c xx
        if (c0 == c1 || c1 == c2 || c2 == c3 || c3 == c4) {
            return ONE_PAIR;
        }
    }
    
    return HIGH_CARD;
}

NS_SM_END
