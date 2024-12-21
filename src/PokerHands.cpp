//
//  PokerHands.cpp
//  SevenMonkeys
//

#include "PokerHands.hpp"

NS_SM_BEGIN

PokerHands::PokerHands()
{
    CCLOG("// PokerHands %x Constructor", (int)(long)this);
}

std::vector<int> PokerHands::getHand(int& rank)
{
    std::vector<int> hand;
    std::vector<int> row { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

    Rand::shuffle(row);

    int middleRndPosition;

    for (int &r: row) {
        if (r < 8) {
            middleRndPosition = r;
            break;
        }
    }

    switch (rank) {
        case (ROYAL_STRAIGHT_FLUSH): {
            int rndCard = 32 + randInt(4);

            for (unsigned i = 0; i < 5; ++i) {
                int card = rndCard + (i * 4);
                hand.push_back(card);
            }
        }
        break;

        case (STRAIGHT_FLUSH): {
            int rndCard = (middleRndPosition * 4) + randInt(4);

            for (unsigned i = 0; i < 5; ++i) {
                int card = rndCard + (i * 4);
                hand.push_back(card);
            }
        }
        break;

        case (FOUR_OF_A_KIND): {
            int rndCard = row[0] * 4;

            for (unsigned i = 0; i < 4; ++i) {
                int card = rndCard + i;
                hand.push_back(card);
            }

            int card = (row[1] * 4) + randInt(4);
            hand.push_back(card);
        }
        break;

        case (FULL_HOUSE): {
            int rndCard = row[0] * 4;
            int column = (randInt(2) == 0) ? 0 : 1;

            for (unsigned i = 0; i < 3; ++i) {
                int card = rndCard + column + i;
                hand.push_back(card);
            }

            rndCard = row[1] * 4;
            column = (randInt(2) == 0) ? 1 : 2;

            for (unsigned i = 0; i < 2; ++i) {
                int card = rndCard + column + i;
                hand.push_back(card);
            }
        }
        break;

        case (FLUSH): {
            int column = randInt(4);

            for (unsigned i = 0; i < 5; ++i) {
                int card = (row[i] * 4) + column;
                hand.push_back(card);
            }
        }
        break;

        case (STRAIGHT): {
            int rndCard = middleRndPosition * 4;

            for (unsigned i = 0; i < 5; ++i) {
                int card = (rndCard + (i * 4)) + randInt(4);
                hand.push_back(card);
            }
        }
        break;

        case (THREE_OF_A_KIND): {
            int rndCard = row[0] * 4;
            int column = (randInt(2) == 0) ? 0 : 1;

            for (unsigned i = 0; i < 3; ++i) {
                int card = rndCard + column + i;
                hand.push_back(card);
            }

            for (unsigned i = 1; i < 3; ++i) {
                int card = (row[i] * 4) + randInt(4);
                hand.push_back(card);
            }
        }
        break;

        case (TWO_PAIR): {
            for (unsigned i = 0; i < 2; ++i) {
                int column = (randInt(2) == 0) ? 0 : 2;

                for (unsigned j = 0; j < 2; ++j) {
                    int card = (row[i] * 4) + column + j;
                    hand.push_back(card);
                }
            }

            int card = (row[3] * 4) + randInt(4);
            hand.push_back(card);
        }
        break;

        case (ONE_PAIR): {
            int rndCard = row[0] * 4;
            int column = (randInt(2) == 0) ? 0 : 2;

            for (unsigned i = 0; i < 2; ++i) {
                int card = rndCard + column + i;
                hand.push_back(card);
            }

            for (unsigned i = 1; i < 4; ++i) {
                int card = (row[i] * 4) + randInt(4);
                hand.push_back(card);
            }
        }
        break;

        // HIGH_CARD
        default: {
            for (unsigned i = 0; i < 5; ++i) {
                int card = (row[i] * 4) + randInt(4);
                hand.push_back(card);
            }
        }
        break;
    }

    return hand;
}

NS_SM_END
