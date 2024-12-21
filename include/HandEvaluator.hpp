//
//  HandEvaluator.hpp
//  SevenMonkeys
//

#ifndef HandEvaluator_hpp
#define HandEvaluator_hpp

#include "SevenMonkeys.hpp"

NS_SM_BEGIN

class HandEvaluator
{
public:

    HandEvaluator();
    ~HandEvaluator() = default;
    
    int eval6(std::vector<int> cards);

    int getRanking(int& card1, int& card2, int& card3, int& card4, int& card5);
};

NS_SM_END

#endif /* HandEvaluator_hpp */
