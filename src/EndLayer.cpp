//
//  EndLayer.cpp
//  SevenMonkeys
//

#include "EndLayer.hpp"

USING_NS_CC;

Scene* EndLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = EndLayer::create();

    scene->addChild(layer);

    return scene;
}

EndLayer::EndLayer()
{
    CCLOG("// EndLayer %x Constructor", (int)(long)this);
}

EndLayer::~EndLayer()
{
    CCLOG("// EndLayer %x Destructor", (int)(long)this);
}

bool EndLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    // Background

    auto background = Sprite::createWithSpriteFrameName("EndLayerBackground.png");

    background->setNormalizedPosition(Vec2(.5f, .5f));

    this->addChild(background);

    // Buttons

    auto buttonBack = MenuItemSprite::create(
                                             Sprite::createWithSpriteFrameName("ButtonBack.png"),
                                             nullptr,
                                             Sprite::createWithSpriteFrameName("ButtonBack.png"),
                                             CC_CALLBACK_1(EndLayer::menuMainCallback, this));

    buttonBack->setNormalizedPosition(Vec2(.1f, .9f));
    buttonBack->setRotation(-3.5f);

    auto menu = Menu::create(buttonBack, nullptr);

    menu->setPosition(Vec2::ZERO);

    this->addChild(menu);

    return true;
}

void EndLayer::onEnter()
{
    Layer::onEnter();

    Game::instance().getSoundManager().playEndMusic();

    UserDefault::getInstance()->setIntegerForKey("endGame", 1);
}

void EndLayer::menuMainCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playButtonGoSound();

    auto button = (MenuItemSprite*)pSender;

    auto scaleBy = ScaleBy::create(.1f, .95f);

    auto replaceScene = CallFunc::create([&]() {
        auto scene = MainLayer::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(.9f, scene, Color3B::BLACK));
    });

    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), replaceScene, nullptr);

    button->runAction(seq);
}
