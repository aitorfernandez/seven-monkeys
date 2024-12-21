// Seven Monkeys Puzzles :)

static const std::string gPuzzles[] = {
    "PokerHands",
    "Order",
    "BestHand",
    "Outs",
    "Odds",
    "FlopTexture",
    "PreFlop"
};

// Cards to integer conversions

//                - ♣  ♦  ♠  ♥
//  0,  1,  2,  3 - 2c 2d 2s 2h -  0
//  4,  5,  6,  7 - 3c 3d 3s 3h -  1
//  8,  9, 10, 11 - 4c 4d 4s 4h -  2
// 12, 13, 14, 15 - 5c 5d 5s 5h -  3
// 16, 17, 18, 19 - 6c 6d 6s 6h -  4
// 20, 21, 22, 23 - 7c 7d 7s 7h -  5
// 24, 25, 26, 27 - 8c 8d 8s 8h -  6
// 28, 29, 30, 31 - 9c 9d 9s 9h -  7
// 32, 33, 34, 35 - Tc Td Ts Th -  8
// 36, 37, 38, 39 - Jc Jd Js Jh -  9
// 40, 41, 42, 43 - Qc Qd Qs Qh - 10
// 44, 45, 46, 47 - Kc Kd Ks Kh - 11
// 48, 49, 50, 51 - Ac Ad As Ah - 12

// Cards handling

static int rank[] = {
    0, 0, 0, 0,
    1, 1, 1, 1,
    2, 2, 2, 2,
    3, 3, 3, 3,
    4, 4, 4, 4,
    5, 5, 5, 5,
    6, 6, 6, 6,
    7, 7, 7, 7,
    8, 8, 8, 8,
    9, 9, 9, 9,
    10, 10, 10, 10,
    11, 11, 11, 11,
    12, 12, 12, 12
};

static int suit[] = {
    0, 1, 2, 3,
    0, 1, 2, 3,
    0, 1, 2, 3,
    0, 1, 2, 3,
    0, 1, 2, 3,
    0, 1, 2, 3,
    0, 1, 2, 3,
    0, 1, 2, 3,
    0, 1, 2, 3,
    0, 1, 2, 3,
    0, 1, 2, 3,
    0, 1, 2, 3,
    0, 1, 2, 3
};

static const std::string gHumanizeCards[] = {
    "2c", "2d", "2s", "2h",
    "3c", "3d", "3s", "3h",
    "4c", "4d", "4s", "4h",
    "5c", "5d", "5s", "5h",
    "6c", "6d", "6s", "6h",
    "7c", "7d", "7s", "7h",
    "8c", "8d", "8s", "8h",
    "9c", "9d", "9s", "9h",
    "Tc", "Td", "Ts", "Th",
    "Jc", "Jd", "Js", "Jh",
    "Qc", "Qd", "Qs", "Qh",
    "Kc", "Kd", "Ks", "Kh",
    "Ac", "Ad", "As", "Ah"
};

#define STANDARD_52_CARD_DECK 52

// Hand categories

// PokerHands

#define ROYAL_STRAIGHT_FLUSH 0

// HandEvaluator
// HashHandEvaluator

#define STRAIGHT_FLUSH	1
#define FOUR_OF_A_KIND	2
#define FULL_HOUSE      3
#define FLUSH           4
#define STRAIGHT        5
#define THREE_OF_A_KIND	6
#define TWO_PAIR        7
#define ONE_PAIR        8
#define HIGH_CARD       9

// Poker actions

#define BET     1
#define RAISE   2
#define RERAISE 3
#define FOLD    4
#define CALL    5
#define CHECK   6

// Poker table order

#define BTN 0
#define SB  1
#define BB  2
#define UTG 3
#define MP  4
#define CO  5

#define FULL_OPACITY 255
#define HALF_OPACITY 155

#define END_GAME_STARS 28

#define EASY 1
#define NORMAL 2
#define HARD 3


const int gUserDefaultIntValue = 66;


// ZOrder Puzzle Elements

enum kZOrderPuzzle
{
    communityCards,
    players,
    holeCards,
    btn,
    blinds,
    stack,
    pot,
    actions,
    tokens,
    ticks
};

enum kTagsPuzzle
{
    labels = 303
};
