//
//  FlopEvaluator.cpp
//  SevenMonkeys
//

#include "FlopEvaluator.hpp"

NS_SM_BEGIN

static int c0, c1, c2;

FlopEvaluator::FlopEvaluator()
{

}

int FlopEvaluator::evalSuit(std::vector<int>& cards)
{
    // { "Rainbow", "2Tone", "", "Monotone" }

    std::sort(cards.begin(), cards.end(), util::sortDescendingOrder());

    c0 = suit[cards[0]];
    c1 = suit[cards[1]];
    c2 = suit[cards[2]];

    return isEqual(c0, c1) + isEqual(c1, c2) + isEqual(c0, c2);
}

int FlopEvaluator::evalMatch(std::vector<int>& cards)
{
    // { "UnPaired", "Paired", "", "Triplet" }

    std::sort(cards.begin(), cards.end(), util::sortDescendingOrder());

    c0 = rank[cards[0]];
    c1 = rank[cards[1]];
    c2 = rank[cards[2]];

    return isEqual(c0, c1) + isEqual(c1, c2) + isEqual(c0, c2);
}

int FlopEvaluator::evalConnect(std::vector<int>& cards)
{
    // { "1gap", "2gap", "3+gap", "3straight", "connector" }

    std::sort(cards.begin(), cards.end(), util::sortDescendingOrder());

    c0 = rank[cards[0]];
    c1 = rank[cards[1]];
    c2 = rank[cards[2]];

    // 3 straight

    if (((c0 - 1 == c1) && (c1 - 1 == c2)) || ((c0 == 12) && (c1 - 1 == c2))) {
        return 3;
    }

    // Gaps

    int gaps = 0;

    std::vector<int> c { c0, c1, c2 };

    for (size_t i = c2; i < c0 + 1; ++i) {
        auto result = std::find(std::begin(c), std::end(c), i);

        if (result == std::end(c)) {
            ++gaps;
        }
    }

    c.clear();
    c.shrink_to_fit();

    // 4 == connector

    return gaps > 2 ? 2 : (gaps == 0) ? 4 : gaps - 1;
}

int FlopEvaluator::isEqual(int &a, int &b)
{
    return a == b ? 1 : 0;
}

NS_SM_END
