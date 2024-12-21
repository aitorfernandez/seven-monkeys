//
//  LoadingLayer.cpp
//  SevenMonkeys
//

#include "LoadingLayer.hpp"

using namespace CocosDenshion;
USING_NS_CC;

Scene* LoadingLayer::createScene()
{
    auto scene = Scene::create();

    auto loadingLayer = LoadingLayer::create();

    scene->addChild(loadingLayer);

    return scene;
}

LoadingLayer::LoadingLayer()
{
    CCLOG("// LoadingLayer %x Constructor", (int)(long)this);
}

LoadingLayer::~LoadingLayer()
{
    CCLOG("// LoadingLayer %x Destructor", (int)(long)this);
}

bool LoadingLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    mvNumberOfResources = 0;

    auto sprite = Sprite::create("Default@2x.png");

    sprite->setRotation(-90.0f);
    sprite->setNormalizedPosition(Vec2(0.5f, 0.5f));

    this->addChild(sprite);

    mvpProgressBar = ProgressTimer::create(Sprite::create("ProgressLoadingLayerContent.png"));

    mvpProgressBar->setType(ProgressTimer::Type::BAR);
    mvpProgressBar->setNormalizedPosition(Vec2(0.502f, 0.11f));
    mvpProgressBar->setPercentage(mvNumberOfResources);

    this->addChild(mvpProgressBar);


    // Default Game Options

    if (UserDefault::getInstance()->getIntegerForKey("sound", gUserDefaultIntValue) == gUserDefaultIntValue)
        UserDefault::getInstance()->setIntegerForKey("sound", 1);

    if (UserDefault::getInstance()->getIntegerForKey("music", gUserDefaultIntValue) == gUserDefaultIntValue)
        UserDefault::getInstance()->setIntegerForKey("music", 1);

    if (UserDefault::getInstance()->getIntegerForKey("vibrate", gUserDefaultIntValue) == gUserDefaultIntValue)
        UserDefault::getInstance()->setIntegerForKey("vibrate", 0);

    if (UserDefault::getInstance()->getIntegerForKey("mode", gUserDefaultIntValue) == gUserDefaultIntValue)
        UserDefault::getInstance()->setIntegerForKey("mode", 2);

    // UserDefault::getInstance()->flush();


//    UserDefault::getInstance()->setIntegerForKey("1-level0", 1);
//    UserDefault::getInstance()->setIntegerForKey("1-level1", 1);
//    UserDefault::getInstance()->setIntegerForKey("1-level2", 1);
//    UserDefault::getInstance()->setIntegerForKey("1-level3", 1);
//    UserDefault::getInstance()->setIntegerForKey("1-level4", 1);
//    UserDefault::getInstance()->setIntegerForKey("1-level5", 1);
//    UserDefault::getInstance()->setIntegerForKey("1-level6", 1);
//
//    UserDefault::getInstance()->setIntegerForKey("2-level0", 1);
//    UserDefault::getInstance()->setIntegerForKey("2-level1", 1);
//    UserDefault::getInstance()->setIntegerForKey("2-level2", 1);
//    UserDefault::getInstance()->setIntegerForKey("2-level3", 1);
//    UserDefault::getInstance()->setIntegerForKey("2-level4", 1);
//    UserDefault::getInstance()->setIntegerForKey("2-level5", 1);
//    UserDefault::getInstance()->setIntegerForKey("2-level6", 1);
//
//    UserDefault::getInstance()->setIntegerForKey("3-level0", 1);
//    UserDefault::getInstance()->setIntegerForKey("3-level1", 1);
//    UserDefault::getInstance()->setIntegerForKey("3-level2", 1);
//    UserDefault::getInstance()->setIntegerForKey("3-level3", 1);
//    UserDefault::getInstance()->setIntegerForKey("3-level4", 1);
//    UserDefault::getInstance()->setIntegerForKey("3-level5", 1);
//    UserDefault::getInstance()->setIntegerForKey("3-level6", 1);


    this->scheduleUpdate();

    return true;
}

void LoadingLayer::update(float dt)
{
    mvpProgressBar->setPercentage(mvNumberOfResources);

    if (mvNumberOfResources == 0) {
        loadResources();
    }

    if (mvNumberOfResources == 100) {
        this->unscheduleUpdate();

        auto scene = MainLayer::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(.9f, scene, Color3B::BLACK));
    }
}

void LoadingLayer::loadResources()
{
    mvNumberOfResources = 10;

    std::vector<const char*> music {
        // Main
        "music/Firmament.mp3",
        // Map
        "music/IKnewaGuy.mp3",
        // Options
        "music/Ultralounge.mp3",
        // FairyHouse
        "music/LobbyTime.mp3",
        // Puzzles
        "music/BackedVibesClean.mp3",
        "music/BumbaCrossing.mp3",
        "music/CovertAffair.mp3",
        "music/DeadlyRoulette.mp3",
        "music/FiveCardShuffle.mp3",
        "music/Hyperfun.mp3",
        "music/ThiefIntheNight.mp3",
        // End game
        "music/MonkeysSpinningMonkeys.mp3"
    };

    for (auto const &m : music) {
        SimpleAudioEngine::getInstance()->preloadBackgroundMusic(m);
    }

    music.clear();
    music.shrink_to_fit();

    std::vector<const char*> sounds {
        "sounds/41471__dj-jones__woodfrog5.wav",
        "sounds/41468__dj-jones__woodfrog2.wav",
        "sounds/41467__dj-jones__woodfrog1.wav",
        "sounds/80935__robinhood76__01273-tin-can-smash-4.wav",
        "sounds/117643__joedeshon__wooden-cabinet-door-closing.wav",
        "sounds/41469__dj-jones__woodfrog3.wav",
        "sounds/29411__junggle__btn231.wav",
        "sounds/29410__junggle__btn230.wav",
        "sounds/41472__dj-jones__woodfrog6.wav",
        "sounds/41473__dj-jones__woodfrog7.wav",
        "sounds/41470__dj-jones__woodfrog4.wav",
        "sounds/337841__newagesoup__small-metal-scrape-04.wav",
        "sounds/41344__ivanbailey__1.wav",
        "sounds/41345__ivanbailey__2.wav",
        "sounds/19245__deathpie__shuffle.wav",
        "sounds/274806__barkerspinhead__alarm-timer-watch-countdown.wav",
        "sounds/270404__littlerobotsoundfactory__jingle-achievement-00.wav",
        "sounds/201807__fartheststar__poker-chips1.wav",
        "sounds/231277__steel2008__race-start-ready-go.wav"
    };

    for (auto const &s : sounds) {
        SimpleAudioEngine::getInstance()->preloadEffect(s);
    }

    sounds.clear();
    sounds.shrink_to_fit();

    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.f);
    SimpleAudioEngine::getInstance()->setEffectsVolume(1.f);


    int spriteSheets = Game::instance().HDR ? 12 : 5;

    for (int i = 0; i < spriteSheets; ++i) {
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
                                                                 "SpriteSheets" + std::to_string(i) + ".plist",
                                                                 "SpriteSheets" + std::to_string(i) + ".png");
    }


    Game::instance().getAnimations().initFairy();
    Game::instance().getAnimations().initCountDown();
    Game::instance().getAnimations().initStarsMarkers();

    mvNumberOfResources = 100;
}
