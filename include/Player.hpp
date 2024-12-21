//
//  Player.hpp
//  SevenMonkeys
//

#ifndef Player_h
#define Player_h

#include "SevenMonkeys.hpp"

class Player
{
public:

    Player();
    ~Player();

    void cleanUp();

    sevenmonkeys::util::Positions mPositions;

    CC_SYNTHESIZE_BOOL(mtHero, Hero);

    CC_SYNTHESIZE_BOOL(mtWinner, Winner);

    // 0, 2, 1, 3... position in the table
    CC_SYNTHESIZE(int, mtRandomPos, RandomPos);
    CC_SYNTHESIZE(int, mtPos, Pos);

    // CO, BTN, SB...
    CC_SYNTHESIZE(int, mtPokerOrder, PokerOrder);

    CC_SYNTHESIZE(int, mtRanking, Ranking);
    CC_SYNTHESIZE(int, mtTotalRanking, TotalRanking);

    CC_SYNTHESIZE(int, mtAmount, Amount);

    void pushCard(int card);

    std::vector<int> getCards();

private:

    std::vector<int> mvCards;
};

#endif /* Player_h */
