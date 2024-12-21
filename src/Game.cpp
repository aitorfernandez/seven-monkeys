//
//  Game.cpp
//  SevenMonkeys
//

#include "Game.hpp"

USING_NS_CC;

Game& Game::instance()
{
    static Game *instance = new (std::nothrow) Game();

    return *instance;
}

Game::Game()
{
    CCLOG("// Game %x Constructor", (int)(long)this);

    mTotalStars = 0;
}

const char* Game::getHumanizeMode(int mode)
{
    if (mode == EASY) {
        return "easy";
    }
    else if (mode == NORMAL) {
        return "normal";
    }
    else {
        return "hard";
    }
}

void Game::updateStars(int stars)
{
    int mode = UserDefault::getInstance()->getIntegerForKey("mode");
    int currentLevel = UserDefault::getInstance()->getIntegerForKey("currentLevel");

    char speedMarkerKey[20];
    sprintf(speedMarkerKey, "%d-%d-StarsMarker", mode, currentLevel);

    int speedMarker = UserDefault::getInstance()->getIntegerForKey(speedMarkerKey);

    if (speedMarker < stars) {
        UserDefault::getInstance()->setIntegerForKey(speedMarkerKey, stars);
    }
}

void Game::updateLevels()
{
    // After each level calculate the total stars
    mTotalStars = 0;

    char speedMarkerKey[20];

    for (short i = 0; i < 7; ++i) {
        sprintf(speedMarkerKey, "%d-%d-StarsMarker", UserDefault::getInstance()->getIntegerForKey("mode"), i);

        mTotalStars = mTotalStars + UserDefault::getInstance()->getIntegerForKey(speedMarkerKey);
    }

    // Exit if not enough stars

    if (mTotalStars < 2) {
        return;
    }

    // Level 0 0  Stars
    // Level 1 2  Stars
    // Level 2 4  Stars

    // Level 3 6  Stars
    // Level 4 8  Stars
    // Level 5 14 Stars
    // Level 6 22 Stars

    int levels;

    if (mTotalStars > 21) {
        levels = 7;
    }
    else if (mTotalStars > 13) {
        levels = 6;
    }
    else if (mTotalStars > 7) {
        levels = 5;
    }
    else if (mTotalStars > 5) {
        levels = 4;
    }
    else if (mTotalStars > 3) {
        levels = 3;
    }
    else {
        levels = 2;
    }

    for (short i = 0; i < levels; ++i)
        this->setLevel(i);
}

void Game::setLevel(int level)
{
    char levelKey[20];

    sprintf(levelKey, "%d-level%d", UserDefault::getInstance()->getIntegerForKey("mode"), level);
    UserDefault::getInstance()->setIntegerForKey(levelKey, 1);
}
