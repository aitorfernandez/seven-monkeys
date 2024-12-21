//
//  SoundManager.cpp
//  SevenMonkeys
//

#include "SoundManager.hpp"

using namespace CocosDenshion;
USING_NS_CC;

// Sounds

void SoundManager::playButtonGoSound()
{
    playSound("sounds/41471__dj-jones__woodfrog5.wav");
}

void SoundManager::playButtonNextSound()
{
    playSound("sounds/41468__dj-jones__woodfrog2.wav");
}

void SoundManager::playOptionSound()
{
    playSound("sounds/41467__dj-jones__woodfrog1.wav");
}

void SoundManager::playResetSound()
{
    playSound("sounds/80935__robinhood76__01273-tin-can-smash-4.wav");
}

void SoundManager::playFairyHouseMarkerSound()
{
    playSound("sounds/117643__joedeshon__wooden-cabinet-door-closing.wav");
}

void SoundManager::playFairyHousePictureSound()
{
    playSound("sounds/41469__dj-jones__woodfrog3.wav");
}

void SoundManager::playNavNextSound()
{
    playSound("sounds/29411__junggle__btn231.wav");
}

void SoundManager::playNavPrevSound()
{
    playSound("sounds/29411__junggle__btn231.wav");
}

void SoundManager::playNavCloseSound()
{
    playSound("sounds/29410__junggle__btn230.wav");
}

void SoundManager::playPauseSound()
{
    playSound("sounds/41472__dj-jones__woodfrog6.wav");
}

void SoundManager::playResumeSound()
{
    playSound("sounds/41473__dj-jones__woodfrog7.wav");
}

void SoundManager::playQuitSound()
{
    playSound("sounds/41470__dj-jones__woodfrog4.wav");
}

void SoundManager::playMapMarkerSound()
{
    playSound("sounds/337841__newagesoup__small-metal-scrape-04.wav");
}

void SoundManager::playRightSound()
{
    playSound("sounds/41344__ivanbailey__1.wav");
}

void SoundManager::playWrongSound()
{
    playSound("sounds/41345__ivanbailey__2.wav");
}

void SoundManager::playDealSound()
{
    playSound("sounds/19245__deathpie__shuffle.wav");
}

void SoundManager::playFinishedTimeSound()
{
    playSound("sounds/274806__barkerspinhead__alarm-timer-watch-countdown.wav");
}

void SoundManager::playPlayerSpeedSound()
{
    playSound("sounds/270404__littlerobotsoundfactory__jingle-achievement-00.wav");
}

void SoundManager::playChipsSound()
{
    playSound("sounds/201807__fartheststar__poker-chips1.wav");
}

void SoundManager::playCountDownSound()
{
    playSound("sounds/231277__steel2008__race-start-ready-go.wav");
}

// Music

void SoundManager::playMainMusic()
{
    playMusic("music/Firmament.mp3");
}

void SoundManager::playMapMusic()
{
    playMusic("music/IKnewaGuy.mp3");
}

void SoundManager::playOptionsMusic()
{
    playMusic("music/Ultralounge.mp3");
}

void SoundManager::playFairyHouseMusic()
{
    playMusic("music/LobbyTime.mp3");
}

void SoundManager::playPokerHandsMusic()
{
    playMusic("music/BumbaCrossing.mp3");
}

void SoundManager::playOrderMusic()
{
    playMusic("music/Hyperfun.mp3");
}

void SoundManager::playBestHandMusic()
{
    playMusic("music/CovertAffair.mp3");
}

void SoundManager::playOutsMusic()
{
    playMusic("music/ThiefIntheNight.mp3");
}

void SoundManager::playOddsMusic()
{
    playMusic("music/BackedVibesClean.mp3");
}

void SoundManager::playFlopTextureMusic()
{
    playMusic("music/FiveCardShuffle.mp3");
}

void SoundManager::playPreFlopMusic()
{
    playMusic("music/DeadlyRoulette.mp3");
}

void SoundManager::playEndMusic()
{
    playMusic("music/MonkeysSpinningMonkeys.mp3");
}


void SoundManager::stopAllEffects()
{
    SimpleAudioEngine::getInstance()->stopAllEffects();
}

void SoundManager::stopMusic()
{
    SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void SoundManager::playSound(const char* sound)
{
    if (UserDefault::getInstance()->getIntegerForKey("sound") == 1)
        SimpleAudioEngine::getInstance()->playEffect(sound);
}

void SoundManager::playMusic(const char* music)
{
    if (UserDefault::getInstance()->getIntegerForKey("music") == 1) {
        // stop music first
        stopMusic();

        SimpleAudioEngine::getInstance()->playBackgroundMusic(music, true);
    }
}
