//
//  MainLayer.cpp
//  SevenMonkeys
//

#include "MainLayer.hpp"

USING_NS_CC;

Scene* MainLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    auto mainLayer = MainLayer::create();

    // add node as a child to scene
    scene->addChild(mainLayer);

    // return the scene
    return scene;
}

MainLayer::MainLayer()
{
    CCLOG("// MainLayer %x Constructor", (int)(long)this);
}

MainLayer::~MainLayer()
{
    CCLOG("// MainLayer %x Destructor", (int)(long)this);
}

bool MainLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    initBackground();
    initButtons();

    return true;
}

void MainLayer::initBackground()
{
    auto background = Sprite::createWithSpriteFrameName("MainLayerBackground.png");
    background->setNormalizedPosition(Vec2(.5f, .5f));

    this->addChild(background);
}

void MainLayer::initButtons()
{
    auto buttonMap = MenuItemSprite::create(
                                            Sprite::createWithSpriteFrameName("ButtonPlay.png"),
                                            nullptr,
                                            Sprite::createWithSpriteFrameName("ButtonPlay.png"),
                                            CC_CALLBACK_1(MainLayer::menuPlayCallback, this));

    buttonMap->setNormalizedPosition(Vec2(.9f, .85f));
    buttonMap->setRotation(-5.5f);

    auto buttonOptions = MenuItemSprite::create(
                                                Sprite::createWithSpriteFrameName("ButtonOptions.png"),
                                                nullptr,
                                                Sprite::createWithSpriteFrameName("ButtonOptions.png"),
                                                CC_CALLBACK_1(MainLayer::menuOptionsCallback, this));

    buttonOptions->setNormalizedPosition(Vec2(.1f, .85f));
    buttonOptions->setRotation(4.5f);

    // create menu, it's an autorelease object
    auto menu = Menu::create(buttonMap, buttonOptions, nullptr);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu);
}

void MainLayer::onEnter()
{
    Layer::onEnter();
    Game::instance().getSoundManager().playMainMusic();
}

void MainLayer::onExit()
{
    Layer::onExit();
}

void MainLayer::menuPlayCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playButtonGoSound();

    auto button = (MenuItemSprite*)pSender;

    auto replaceScene = CallFunc::create([&]() {
        auto scene = MapLayer::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(.9f, scene, Color3B::BLACK));
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), replaceScene, nullptr);

    button->runAction(seq);
}

void MainLayer::menuOptionsCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playButtonGoSound();

    auto button = (MenuItemSprite*)pSender;

    auto replaceScene = CallFunc::create([&]() {
        auto scene = OptionsLayer::createScene();
        Director::getInstance()->pushScene(scene);
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), replaceScene, nullptr);

    button->runAction(seq);
}
