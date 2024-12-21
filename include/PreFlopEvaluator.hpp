//
//  PreFlopEvaluator.hpp
//  SevenMonkeys
//

#ifndef PreFlopEvaluator_hpp
#define PreFlopEvaluator_hpp

#include "SevenMonkeys.hpp"

#include "charts.hpp"

NS_SM_BEGIN

class PreFlopEvaluator
{
public:

    PreFlopEvaluator();
    ~PreFlopEvaluator() = default;

    int evalOR(int order, std::vector<int> cards);
    int evalROL(int order, std::vector<int> cards);
    int eval3bet(int order, std::vector<int> cards);
    int eval4bet(int order, std::vector<int> cards);
    int evalCall(int order, std::vector<int> cards);

private:

    void sortCards(std::vector<int>& cards);
};

NS_SM_END

#endif /* PreFlopEvaluator_hpp */
