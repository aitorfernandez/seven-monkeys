//
//  PokerHands.hpp
//  SevenMonkeys
//

#ifndef PokerHands_hpp
#define PokerHands_hpp

#include "SevenMonkeys.hpp"

#include "Rand.hpp"

NS_SM_BEGIN

class PokerHands
{
public:

    PokerHands();
    ~PokerHands() = default;

    std::vector<int> getHand(int& rank);
};

NS_SM_END

#endif /* PokerHands_hpp */
