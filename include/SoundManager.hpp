//
//  SoundManager.hpp
//  SevenMonkeys
//

#ifndef SoundManager_hpp
#define SoundManager_hpp

#include "SevenMonkeys.hpp"

class SoundManager
{
public:

    ~SoundManager() = default;

    // Sounds

    void playButtonGoSound();

    void playButtonNextSound();

    void playOptionSound();

    void playResetSound();

    void playFairyHouseMarkerSound();
    void playFairyHousePictureSound();

    void playMapMarkerSound();

    void playNavNextSound();
    void playNavPrevSound();
    void playNavCloseSound();

    void playCountDownSound();

    void playDealSound();

    void playRightSound();
    void playWrongSound();

    void playPauseSound();
    void playResumeSound();
    void playQuitSound();

    void playFinishedTimeSound();

    void playPlayerSpeedSound();

    void playChipsSound();

    // Music

    void playMainMusic();

    void playMapMusic();

    void playOptionsMusic();

    void playFairyHouseMusic();

    void playPokerHandsMusic();
    void playOrderMusic();
    void playBestHandMusic();
    void playOutsMusic();
    void playFlopTextureMusic();
    void playOddsMusic();
    void playPreFlopMusic();

    void playEndMusic();


    void stopAllEffects();
    void stopMusic();

private:

    void playSound(const char* sound);
    void playMusic(const char* sound);
};

#endif /* SoundManager_hpp */
