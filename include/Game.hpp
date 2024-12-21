//
//  Game.hpp
//  SevenMonkeys
//

#ifndef Game_hpp
#define Game_hpp

#include "SevenMonkeys.hpp"

#include "Animations.hpp"
#include "SoundManager.hpp"

class Game
{
public:

    Game();
    ~Game() = default;

    static Game& instance();

    Animations& getAnimations()
    {
        return *mvpAnimations;
    }

    SoundManager& getSoundManager()
    {
        return *mvpSoundManager;
    }

    int mTotalStars;

    bool HDR;

    void updateStars(int stars);
    void updateLevels();

    void setLevel(int level);

    const char* getHumanizeMode(int mode);

private:

    Animations *mvpAnimations;
    SoundManager *mvpSoundManager;
};

#endif /* Game_hpp */
