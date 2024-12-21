//
//  FlopEvaluator.hpp
//  SevenMonkeys
//

#ifndef FlopEvaluator_hpp
#define FlopEvaluator_hpp

#include "SevenMonkeys.hpp"

NS_SM_BEGIN

class FlopEvaluator
{
public:

    FlopEvaluator();
    ~FlopEvaluator() = default;

    int evalSuit(std::vector<int>& cards);
    int evalMatch(std::vector<int>& cards);
    int evalConnect(std::vector<int>& cards);

private:

    int isEqual(int &a, int& b);
};

NS_SM_END

#endif /* FlopEvaluator_hpp */
