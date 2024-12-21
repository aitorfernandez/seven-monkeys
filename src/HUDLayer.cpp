//
//  HUDLayer.cpp
//  SevenMonkeys
//

#include "HUDLayer.hpp"

USING_NS_CC;
using namespace cocos2d::ui;

HUDLayer::HUDLayer()
{
    CCLOG("// HUDLayer %x Constructor", (int)(long)this);

    mvAnswersCounter = 0;
    mvCurrentStar = 0;
    mvPercentCounter = 0;
}

HUDLayer::~HUDLayer()
{
    CCLOG("// HUDLayer %x Destructor", (int)(long)this);

    if (mvpClockCounter) {
        mvpClockCounter->removeFromParentAndCleanup(true);
        mvpClockCounter = nullptr;
    }

    mvpPlayerSpeed.clear();
    mvpPlayerSpeed.shrinkToFit();

    mvpStars.clear();
    mvpStars.shrinkToFit();

    mvLevelUp.clear();
    mvLevelUp.shrink_to_fit();
}

bool HUDLayer::init(const float puzzleTime, const int firstLevel, const int lastLevel, const float penalty)
{
    if (!Layer::init()) {
        return false;
    }

    mvIsPause = false;
    mvIsAlarmRinging = false;

    mvTime = .0f;
    mvPuzzleTime = puzzleTime;

    if (!mvPuzzleTime) {
        mvPuzzleTime = 90.f;
    }

    initLevelUp(firstLevel, lastLevel);

    initClock();

    initStars();

    initButtons();

    initPlayerSpeed();

    initPause();

    return true;
}

void HUDLayer::initLevelUp(const int &firstLevel, const int &lastLevel)
{
    int levels = 4;

    double B = log((double)lastLevel / firstLevel) / (levels - 1);
    double A = (double)firstLevel / (exp(B) - 1.0);

    for (int i = 1; i <= levels; i++)
    {
        int oldLevel = round(A * exp(B * (i - 1)));
        int newLevel = round(A * exp(B * i));

        mvLevelUp.push_back(newLevel - oldLevel);
    }
}

void HUDLayer::initClock()
{
    auto clock = Sprite::createWithSpriteFrameName("Watch.png");

    clock->setNormalizedPosition(Vec2(.5f, .875f));
    clock->setOpacity(155);

    this->addChild(clock, kZOrder::menu, kTag::clock);

    mvpClockCounter = Label::createWithTTF("", "fonts/firecat_medium.ttf", 14);

    mvpClockCounter->setNormalizedPosition(Vec2(.5f, .877f));

    this->addChild(mvpClockCounter, kZOrder::menu + 1, kTag::counterLabel);
}

void HUDLayer::initStars()
{
    auto progressStarBorder = Sprite::createWithSpriteFrameName("ProgressStarBorder.png");

    progressStarBorder->setNormalizedPosition(Vec2(.675f, .88f));
    progressStarBorder->setOpacity(155);

    this->addChild(progressStarBorder, kZOrder::stars, kTag::starsProgressContent);

    for (int i = 0; i < 4; ++i) {
        auto star = ProgressTimer::create(Sprite::createWithSpriteFrameName(
                                                                            "ProgressStarContent_" +
                                                                            std::to_string(UserDefault::getInstance()->getIntegerForKey("mode")) +
                                                                            ".png"));
        star->setType(ProgressTimer::Type::BAR);

        // Setup for a bar starting from the bottom since the midpoint is 0 for the y
        star->setMidpoint(Vec2(0, 0));

        // Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
        star->setBarChangeRate(Vec2(0, 1));

        star->setPercentage(0);

        this->addChild(star, kZOrder::stars);

        mvpStars.pushBack(star);
    }

    mvpStars.at(0)->setNormalizedPosition(Vec2(.6125f, .88f));
    mvpStars.at(1)->setNormalizedPosition(Vec2(.6545f, .88f));
    mvpStars.at(2)->setNormalizedPosition(Vec2(.6955f, .88f));
    mvpStars.at(3)->setNormalizedPosition(Vec2(.7375f, .88f));
}

void HUDLayer::initButtons()
{
    auto buttonExit = MenuItemSprite::create(
                                             Sprite::createWithSpriteFrameName("ButtonBackMap.png"),
                                             nullptr,
                                             Sprite::createWithSpriteFrameName("ButtonBackMap.png"),
                                             CC_CALLBACK_1(HUDLayer::menuExitCallback, this));

    buttonExit->setNormalizedPosition(Vec2(.3f, .88f));

    auto buttonPause = MenuItemSprite::create(
                                              Sprite::createWithSpriteFrameName("ButtonPause.png"),
                                              Sprite::createWithSpriteFrameName("ButtonResume.png"),
                                              nullptr,
                                              CC_CALLBACK_1(HUDLayer::menuPauseCallback, this));

    buttonPause->setNormalizedPosition(Vec2(.385f, .88f));

    mvpMenu = Menu::create(buttonPause, buttonExit, nullptr);

    mvpMenu->setPosition(Vec2::ZERO);
    mvpMenu->setEnabled(false);
    mvpMenu->setOpacity(155);

    this->addChild(mvpMenu, kZOrder::menu);
}

void HUDLayer::initPlayerSpeed()
{
    for (int i = 0; i < 5; ++i) {
        auto sprite = Sprite::createWithSpriteFrameName("PlayerSpeed" + std::to_string(i) + ".png");
        sprite->setNormalizedPosition(Vec2(.5f, .52f));

        mvpPlayerSpeed.pushBack(sprite);
    }
}

void HUDLayer::initPause()
{
    auto backgroundPause = Sprite::createWithSpriteFrameName("Pause.png");

    backgroundPause->setNormalizedPosition(Vec2(.5f, .5f));
    backgroundPause->setVisible(false);

    this->addChild(backgroundPause, kZOrder::pause, kTag::backgroundPause);
}

void HUDLayer::onEnter()
{
    Layer::onEnter();
    addEvents();
}

void HUDLayer::onExit()
{
    Layer::onExit();
    removeEvents();

    UserDefault::getInstance()->deleteValueForKey("currentLevel");
}

void HUDLayer::addEvents()
{
    mvpEventExitCountDown = EventListenerCustom::create(ON_EXIT_COUNT_DOWN, [=](EventCustom* event) {
        start();
    });

    mvpEventRightAnswer = EventListenerCustom::create(RIGHT_ANSWER, [=](EventCustom* event) {
        rightAnswer();
    });

    mvpEventWrongAnswer = EventListenerCustom::create(WRONG_ANSWER, [=](EventCustom* event) {
        wrongAnswer();
    });

    _eventDispatcher->addEventListenerWithFixedPriority(mvpEventExitCountDown, 1);
    _eventDispatcher->addEventListenerWithFixedPriority(mvpEventRightAnswer, 1);
    _eventDispatcher->addEventListenerWithFixedPriority(mvpEventWrongAnswer, 1);
}

void HUDLayer::removeEvents()
{
    _eventDispatcher->removeEventListener(mvpEventExitCountDown);
    _eventDispatcher->removeEventListener(mvpEventRightAnswer);
    _eventDispatcher->removeEventListener(mvpEventWrongAnswer);
}

void HUDLayer::start()
{
    mvpMenu->setEnabled(true);
    mvpMenu->setOpacity(255);

    this->getChildByTag(kTag::clock)->setOpacity(255);
    this->getChildByTag(kTag::starsProgressContent)->setOpacity(255);

    this->scheduleUpdate();
}

void HUDLayer::update(float dt)
{
    mvTime += dt;

    // mvpProgressTimer->setPercentage(100 - ((mvTime * 100) / mvPuzzleTime));

    mvpClockCounter->setString(std::to_string(static_cast<int>(mvPuzzleTime - mvTime)));

    if (mvTime + 10.5f > mvPuzzleTime && !mvIsAlarmRinging) {
        mvIsAlarmRinging = true;

        Game::instance().getSoundManager().playFinishedTimeSound();
    }

    if ((mvTime > mvPuzzleTime) || (mvCurrentStar == 4)) {
        Game::instance().getSoundManager().stopAllEffects();
        Game::instance().getSoundManager().stopMusic();

        finish();
    }
}

void HUDLayer::rightAnswer()
{
    Game::instance().getSoundManager().playRightSound();

    mvAnswersCounter++;

    setStarsProgress();
}

void HUDLayer::wrongAnswer()
{
    Game::instance().getSoundManager().playWrongSound();

    mvPuzzleTime = mvPuzzleTime - mvPenalty;

    mvpClockCounter->setColor(Color3B::RED);

    mvpClockCounter->stopAllActions();
    mvpClockCounter->setScale(1.f);

    auto setColor = CallFunc::create([&]() {
        mvpClockCounter->setColor(Color3B::WHITE);
    });

    auto scaleBy = ScaleBy::create(.5f, 1.25f);
    auto moveEaseIn = EaseBounceIn::create(scaleBy->clone());

    auto seq = Sequence::create(moveEaseIn, moveEaseIn->reverse(), DelayTime::create(.5f), setColor, nullptr);

    mvpClockCounter->runAction(seq);
}

void HUDLayer::setStarsProgress()
{
    mvPercentCounter++;

    if (mvAnswersCounter <= mvLevelUp[0])
        mvCurrentStar = 0;
    else if (mvAnswersCounter <= mvLevelUp[1])
        mvCurrentStar = 1;
    else if (mvAnswersCounter <= mvLevelUp[2])
        mvCurrentStar = 2;
    else if (mvAnswersCounter < mvLevelUp[3])
        mvCurrentStar = 3;
    else {
        mvCurrentStar = 4;
        mvpStars.at(3)->setPercentage(100);
    }

    int div = (mvCurrentStar == 0) ? mvLevelUp[0] : div = mvLevelUp[mvCurrentStar] - mvLevelUp[mvCurrentStar - 1];

    int percent = (int)((mvPercentCounter * 100) / div);

    if (percent >= 100) {
        mvPercentCounter = 0;
    }

    if (mvCurrentStar < 4) {
        mvpStars.at(mvCurrentStar)->setPercentage(percent);

        auto scaleBy = ScaleBy::create(.125f, 1.15f);
        auto seq = Sequence::create(scaleBy, scaleBy->reverse(), nullptr);

        mvpStars.at(mvCurrentStar)->runAction(seq);
    }
}

void HUDLayer::finish()
{
    this->unscheduleUpdate();

    mvpMenu->setEnabled(false);
    mvpMenu->setOpacity(HALF_OPACITY);

    mvpClockCounter->setString("");

    this->getChildByTag(kTag::clock)->setOpacity(HALF_OPACITY);
    this->getChildByTag(kTag::starsProgressContent)->setOpacity(HALF_OPACITY);

    for (int i = 0; i < 4; ++i) {
        mvpStars.at(i)->setOpacity(HALF_OPACITY);
    }


    EventCustom event(FINISH_HUD);
    _eventDispatcher->dispatchEvent(&event);


    showPlayerSpeed();


    Game::instance().updateStars(mvCurrentStar);
    Game::instance().updateLevels();


    auto buttonClose = MenuItemSprite::create(
                                              Sprite::createWithSpriteFrameName("NavClose.png"),
                                              nullptr,
                                              Sprite::createWithSpriteFrameName("NavClose.png"),
                                              CC_CALLBACK_1(HUDLayer::menuExitCallback, this));

    buttonClose->setNormalizedPosition(Vec2(.5f, .75f));

    auto menu = Menu::create(buttonClose, nullptr);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu, kZOrder::exit);
}

void HUDLayer::menuPauseCallback(cocos2d::Ref* pSender)
{
    auto button = (MenuItemSprite*)pSender;

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), nullptr);

    button->runAction(seq);

    if (mvIsPause) {

        Game::instance().getSoundManager().playResumeSound();

        button->unselected();

        this->getChildByTag(kTag::backgroundPause)->setOpacity(255);

        Director::getInstance()->resume();

        auto visibleFalse = CallFunc::create([&]() {
            this->getChildByTag(kTag::backgroundPause)->setVisible(false);
        });

        auto seq = Sequence::create(FadeOut::create(.25f), visibleFalse, nullptr);

        this->getChildByTag(kTag::backgroundPause)->runAction(seq);


        this->getChildByTag(kTag::clock)->setOpacity(FULL_OPACITY);
        this->getChildByTag(kTag::counterLabel)->setOpacity(FULL_OPACITY);
        this->getChildByTag(kTag::starsProgressContent)->setOpacity(FULL_OPACITY);
    }
    else {

        Game::instance().getSoundManager().playPauseSound();

        button->selected();

        this->getChildByTag(kTag::backgroundPause)->setOpacity(0);
        this->getChildByTag(kTag::backgroundPause)->setVisible(true);

        auto pause = CallFunc::create([&]() {
            Director::getInstance()->pause();
        });

        auto seq = Sequence::create(FadeIn::create(.25f), pause, nullptr);

        this->getChildByTag(kTag::backgroundPause)->runAction(seq);


        this->getChildByTag(kTag::clock)->setOpacity(HALF_OPACITY);
        this->getChildByTag(kTag::counterLabel)->setOpacity(HALF_OPACITY);
        this->getChildByTag(kTag::starsProgressContent)->setOpacity(HALF_OPACITY);
    }

    mvIsPause = !mvIsPause;

    EventCustom event(TOGGLE_PAUSE);
    _eventDispatcher->dispatchEvent(&event);
}

void HUDLayer::menuExitCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playQuitSound();

    if (mvIsPause)
        Director::getInstance()->resume();


    auto button = (MenuItemSprite*)pSender;

    auto replaceScene = CallFunc::create([&]() {
        Scene* scene;

        if (Game::instance().mTotalStars >= END_GAME_STARS)
            scene = EndLayer::createScene();
        else
            scene = MapLayer::createScene();

        Director::getInstance()->replaceScene(TransitionFade::create(.9f, scene, Color3B::BLACK));
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), replaceScene, nullptr);

    button->runAction(seq);
}

void HUDLayer::showPlayerSpeed()
{
    Game::instance().getSoundManager().playPlayerSpeedSound();

    auto playerSpeedBackground = Sprite::createWithSpriteFrameName("PlayerSpeedBackground.png");

    playerSpeedBackground->setNormalizedPosition(Vec2(.5f, .5f));

    this->addChild(playerSpeedBackground, kZOrder::playerSpeed);


    this->addChild(mvpPlayerSpeed.at(mvCurrentStar), kZOrder::playerSpeed + 1);


    auto scaleBy = ScaleBy::create(.5f, 1.25f);
    auto moveEaseIn = EaseBounceIn::create(scaleBy->clone());

    auto seq = Sequence::create(DelayTime::create(.15f), moveEaseIn, moveEaseIn->reverse(), nullptr);

    mvpPlayerSpeed.at(mvCurrentStar)->runAction(seq);
}

HUDLayer* HUDLayer::create(const float puzzleTime, const int firstLevel, const int lastLevel, const float penalty)
{
    HUDLayer *pHUDLayer = new(std::nothrow) HUDLayer();

    if (pHUDLayer && pHUDLayer->init(puzzleTime, firstLevel, lastLevel, penalty)) {
        pHUDLayer->autorelease();

        return pHUDLayer;
    }
    else {
        CC_SAFE_DELETE(pHUDLayer);
        return nullptr;
    }
}
