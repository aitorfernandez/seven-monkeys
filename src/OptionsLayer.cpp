//
//  OptionsLayer.cpp
//  SevenMonkeys
//

#include "OptionsLayer.hpp"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* OptionsLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = OptionsLayer::create();

    scene->addChild(layer);

    return scene;
}

OptionsLayer::OptionsLayer()
{
    CCLOG("// OptionsLayer %x Constructor", (int)(long)this);
}

OptionsLayer::~OptionsLayer()
{
    CCLOG("// OptionsLayer %x Destructor", (int)(long)this);
}

bool OptionsLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    initBackground();

    initLabels();

    initButtons();

    selectDefaultOptions();

    // Here the music instead of onEnter to avoid reload when the user come back from CreditsLayer or DisclaimerLayer

    Game::instance().getSoundManager().playOptionsMusic();

    return true;
}

void OptionsLayer::initBackground()
{
    auto background = Sprite::createWithSpriteFrameName("OptionsBackground.png");

    background->setNormalizedPosition(Vec2(.5f, .5f));

    this->addChild(background);
}

void OptionsLayer::initLabels()
{
    auto options = Label::createWithTTF("Options", "fonts/firecat_medium.ttf", 32);
    options->setNormalizedPosition(Vec2(.5f, .8f));

    this->addChild(options);

    auto sound = Label::createWithTTF("Sound", "fonts/firecat_medium.ttf", 15);
    sound->setNormalizedPosition(Vec2(.43f, .63f));

    this->addChild(sound);

    auto music = Label::createWithTTF("Music", "fonts/firecat_medium.ttf", 15);
    music->setNormalizedPosition(Vec2(.43f, .5f));

    this->addChild(music);

    auto vibrate = Label::createWithTTF("Vibrate", "fonts/firecat_medium.ttf", 15);
    vibrate->setNormalizedPosition(Vec2(.405f, .37f));

    this->addChild(vibrate);
}

void OptionsLayer::initButtons()
{
    mvpSound = checkBoxCreate();
    mvpSound->setNormalizedPosition(Vec2(.57f, .64f));
    mvpSound->addEventListener(CC_CALLBACK_2(OptionsLayer::menuSoundCallback, this));

    this->addChild(mvpSound);

    mvpMusic = checkBoxCreate();
    mvpMusic->setNormalizedPosition(Vec2(.57f, .51f));
    mvpMusic->addEventListener(CC_CALLBACK_2(OptionsLayer::menuMusicCallback, this));

    this->addChild(mvpMusic);

    mvpVibrate = checkBoxCreate();
    mvpVibrate->setNormalizedPosition(Vec2(.57f, .38f));
    mvpVibrate->addEventListener(CC_CALLBACK_2(OptionsLayer::menuVibrateCallback, this));

    this->addChild(mvpVibrate);


    mvpModeEasy = MenuItemSprite::create(
                                         Sprite::createWithSpriteFrameName("ButtonModeEasyOff.png"),
                                         Sprite::createWithSpriteFrameName("ButtonModeEasyOn.png"),
                                         nullptr,
                                         CC_CALLBACK_1(OptionsLayer::menuModeEasyCallback, this));

    mvpModeEasy->setNormalizedPosition(Vec2(.35f, .2f));

    mvpModeNormal = MenuItemSprite::create(
                                           Sprite::createWithSpriteFrameName("ButtonModeMediumOff.png"),
                                           Sprite::createWithSpriteFrameName("ButtonModeMediumOn.png"),
                                           nullptr,
                                           CC_CALLBACK_1(OptionsLayer::menuModeNormalCallback, this));

    mvpModeNormal->setNormalizedPosition(Vec2(.51f, .2f));

    mvpModeHard = MenuItemSprite::create(
                                         Sprite::createWithSpriteFrameName("ButtonModeHardOff.png"),
                                         Sprite::createWithSpriteFrameName("ButtonModeHardOn.png"),
                                         nullptr,
                                         CC_CALLBACK_1(OptionsLayer::menuModeHardCallback, this));

    mvpModeHard->setNormalizedPosition(Vec2(.67f, .2f));


    auto buttonMain = MenuItemSprite::create(
                                             Sprite::createWithSpriteFrameName("ButtonBack.png"),
                                             nullptr,
                                             Sprite::createWithSpriteFrameName("ButtonBack.png"),
                                             CC_CALLBACK_1(OptionsLayer::menuMainCallback, this));

    buttonMain->setNormalizedPosition(Vec2(.1f, .85f));
    buttonMain->setRotation(3.5f);

    auto buttonCredits = MenuItemSprite::create(
                                                Sprite::createWithSpriteFrameName("ButtonCredits.png"),
                                                nullptr,
                                                Sprite::createWithSpriteFrameName("ButtonCredits.png"),
                                                CC_CALLBACK_1(OptionsLayer::menuCreditsCallback, this));

    buttonCredits->setNormalizedPosition(Vec2(.9f, .85f));
    buttonCredits->setRotation(-3.5f);

    auto buttonReset = MenuItemSprite::create(
                                              Sprite::createWithSpriteFrameName("ButtonReset.png"),
                                              nullptr,
                                              Sprite::createWithSpriteFrameName("ButtonReset.png"),
                                              CC_CALLBACK_1(OptionsLayer::menuResetCallback, this));

    buttonReset->setNormalizedPosition(Vec2(.9f, .74f));
    buttonReset->setRotation(-3.5f);

    auto buttonDisclaimer = MenuItemSprite::create(
                                                   Sprite::createWithSpriteFrameName("ButtonDisclaimer.png"),
                                                   nullptr,
                                                   Sprite::createWithSpriteFrameName("ButtonDisclaimer.png"),
                                                   CC_CALLBACK_1(OptionsLayer::menuDisclaimerCallback, this));

    buttonDisclaimer->setNormalizedPosition(Vec2(.9f, .63f));
    buttonDisclaimer->setRotation(-3.5f);

    auto menu = Menu::create(
                             mvpModeEasy,
                             mvpModeNormal,
                             mvpModeHard,
                             buttonMain,
                             buttonCredits,
                             buttonReset,
                             buttonDisclaimer, nullptr);
    
    menu->setPosition(Vec2::ZERO);
    
    this->addChild(menu);
}

void OptionsLayer::onEnter()
{
    Layer::onEnter();
}

void OptionsLayer::onExit()
{
    Layer::onExit();

    // Keep music for Credits and Disclaimer layers
    // Game::instance().getSoundManager().stopMusic();
}

void OptionsLayer::menuSoundCallback(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
    Game::instance().getSoundManager().playOptionSound();

    switch (type)
    {
        case CheckBox::EventType::SELECTED:
            UserDefault::getInstance()->setIntegerForKey("sound", 1);
            break;

        case CheckBox::EventType::UNSELECTED:
            UserDefault::getInstance()->setIntegerForKey("sound", 0);
            break;

        default:
            break;
    }
}

void OptionsLayer::menuMusicCallback(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
    Game::instance().getSoundManager().playOptionSound();

    switch (type)
    {
        case CheckBox::EventType::SELECTED:
            UserDefault::getInstance()->setIntegerForKey("music", 1);
            Game::instance().getSoundManager().playOptionsMusic();
            break;

        case CheckBox::EventType::UNSELECTED:
            UserDefault::getInstance()->setIntegerForKey("music", 0);
            Game::instance().getSoundManager().stopMusic();
            break;

        default:
            break;
    }
}

void OptionsLayer::menuVibrateCallback(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type)
{
    Game::instance().getSoundManager().playOptionSound();

    switch (type)
    {
        case CheckBox::EventType::SELECTED:
            UserDefault::getInstance()->setIntegerForKey("vibrate", 1);
            break;

        case CheckBox::EventType::UNSELECTED:
            UserDefault::getInstance()->setIntegerForKey("vibrate", 0);
            break;

        default:
            break;
    }
}

void OptionsLayer::menuModeEasyCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playOptionSound();

    auto button = (MenuItemSprite*)pSender;

    auto updateModes = CallFunc::create([&]() {
        mvpModeNormal->unselected();
        mvpModeHard->unselected();

        mvpModeEasy->selected();

        UserDefault::getInstance()->setIntegerForKey("mode", 1);
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), updateModes, nullptr);

    button->runAction(seq);
}

void OptionsLayer::menuModeNormalCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playOptionSound();

    auto button = (MenuItemSprite*)pSender;

    auto updateModes = CallFunc::create([&]() {
        mvpModeEasy->unselected();
        mvpModeHard->unselected();

        mvpModeNormal->selected();

        UserDefault::getInstance()->setIntegerForKey("mode", 2);
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), updateModes, nullptr);

    button->runAction(seq);
}

void OptionsLayer::menuModeHardCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playOptionSound();

    auto button = (MenuItemSprite*)pSender;

    auto updateModes = CallFunc::create([&]() {
        mvpModeEasy->unselected();
        mvpModeNormal->unselected();

        mvpModeHard->selected();

        UserDefault::getInstance()->setIntegerForKey("mode", 3);
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), updateModes, nullptr);

    button->runAction(seq);
}

void OptionsLayer::menuMainCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playButtonGoSound();

    auto button = (MenuItemSprite*)pSender;

    auto popScene = CallFunc::create([&]() {
        // MainLayer again
        Director::getInstance()->popScene();
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), popScene, nullptr);

    button->runAction(seq);
}

void OptionsLayer::menuResetCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playResetSound();

    auto button = (MenuItemSprite*)pSender;

    auto setDefaultUserOptions = CallFunc::create([&]() {

        std::vector<std::string> keys {
            "sound",
            "music",
            "vibrate",
            "mode",

            "pictureTutorial",
            "currentLevel",
            "endGame",

            "1-0-StarsMarker",
            "1-1-StarsMarker",
            "1-2-StarsMarker",
            "1-3-StarsMarker",
            "1-4-StarsMarker",
            "1-5-StarsMarker",
            "1-6-StarsMarker",

            "2-0-StarsMarker",
            "2-1-StarsMarker",
            "2-2-StarsMarker",
            "2-3-StarsMarker",
            "2-4-StarsMarker",
            "2-5-StarsMarker",
            "2-6-StarsMarker",

            "3-0-StarsMarker",
            "3-1-StarsMarker",
            "3-2-StarsMarker",
            "3-3-StarsMarker",
            "3-4-StarsMarker",
            "3-5-StarsMarker",
            "3-6-StarsMarker",

            "1-level0",
            "1-level1",
            "1-level2",
            "1-level3",
            "1-level4",
            "1-level5",
            "1-level6",

            "2-level0",
            "2-level1",
            "2-level2",
            "2-level3",
            "2-level4",
            "2-level5",
            "2-level6",

            "3-level0",
            "3-level1",
            "3-level2",
            "3-level3",
            "3-level4",
            "3-level5",
            "3-level6"
        };

        for (auto const &k : keys) {
            UserDefault::getInstance()->deleteValueForKey(k.c_str());
        }

        keys.clear();
        keys.shrink_to_fit();

        UserDefault::getInstance()->setIntegerForKey("sound", 1);
        UserDefault::getInstance()->setIntegerForKey("music", 1);
        UserDefault::getInstance()->setIntegerForKey("vibrate", 0);

        UserDefault::getInstance()->setIntegerForKey("mode", 2);

        // UserDefault::getInstance()->flush();

        selectDefaultOptions();
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), setDefaultUserOptions, nullptr);

    button->runAction(seq);
}

void OptionsLayer::menuCreditsCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playButtonGoSound();

    auto button = (MenuItemSprite*)pSender;

    auto pushScene = CallFunc::create([&]() {
        auto scene = CreditsLayer::createScene();
        Director::getInstance()->pushScene(scene);
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), pushScene, nullptr);

    button->runAction(seq);
}

void OptionsLayer::menuDisclaimerCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playButtonGoSound();

    auto button = (MenuItemSprite*)pSender;

    auto pushScene = CallFunc::create([&]() {
        auto scene = DisclaimerLayer::createScene();
        Director::getInstance()->pushScene(scene);
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), pushScene, nullptr);

    button->runAction(seq);
}

void OptionsLayer::selectDefaultOptions()
{
    if (UserDefault::getInstance()->getIntegerForKey("sound") == 0)
        mvpSound->setSelected(false);
    else
        mvpSound->setSelected(true);

    if (UserDefault::getInstance()->getIntegerForKey("music") == 0)
        mvpMusic->setSelected(false);
    else
        mvpMusic->setSelected(true);

    if (UserDefault::getInstance()->getIntegerForKey("vibrate") == 0)
        mvpVibrate->setSelected(false);
    else
        mvpVibrate->setSelected(true);


    if (UserDefault::getInstance()->getIntegerForKey("mode") == EASY) {
        mvpModeEasy->selected();
        mvpModeNormal->unselected();
        mvpModeHard->unselected();
    }

    if (UserDefault::getInstance()->getIntegerForKey("mode") == NORMAL) {
        mvpModeEasy->unselected();
        mvpModeNormal->selected();
        mvpModeHard->unselected();
    }

    if (UserDefault::getInstance()->getIntegerForKey("mode") == HARD) {
        mvpModeEasy->unselected();
        mvpModeNormal->unselected();
        mvpModeHard->selected();
    }
}

cocos2d::ui::CheckBox* OptionsLayer::checkBoxCreate()
{
    return CheckBox::create(
                            "CheckBoxBackground.png",
                            "CheckBoxOn.png",
                            "CheckBoxOn.png",
                            "CheckBoxBackground.png",
                            "CheckBoxBackground.png");
}
