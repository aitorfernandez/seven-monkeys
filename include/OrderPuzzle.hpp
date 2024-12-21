//
//  OrderPuzzle.hpp
//  SevenMonkeys
//

#ifndef OrderPuzzle_hpp
#define OrderPuzzle_hpp

#include "SevenMonkeys.hpp"

#include "Rand.hpp"

#include "PuzzleLayer.hpp"

class OrderPuzzle : public PuzzleLayer
{
public:

    OrderPuzzle();
    virtual ~OrderPuzzle();

    virtual bool init();

    CREATE_FUNC(OrderPuzzle);

    void update(float dt);

private:

    std::vector<sevenmonkeys::util::Positions> mvPositionsBackup;

    void movePlayers();

    void addPlayers(std::vector<int>& tableOrder, int& hero);
    void addTokens(std::vector<int>& tableOrder, int& hero);
};

#endif /* OrderPuzzle_hpp */
