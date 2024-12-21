//
//  DisclaimerLayer.cpp
//  SevenMonkeys
//

#include "DisclaimerLayer.hpp"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* DisclaimerLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = DisclaimerLayer::create();

    scene->addChild(layer);

    return scene;
}

DisclaimerLayer::DisclaimerLayer()
{
    CCLOG("// DisclaimerLayer %x Constructor", (int)(long)this);
}

DisclaimerLayer::~DisclaimerLayer()
{
    CCLOG("// DisclaimerLayer %x Destructor", (int)(long)this);
}

bool DisclaimerLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    initBackground();

    initLabelAndText();

    initButtons();

    return true;
}

void DisclaimerLayer::initBackground()
{
    auto background = Sprite::createWithSpriteFrameName("OptionsBackground.png");

    background->setNormalizedPosition(Vec2(.5f, .5f));

    this->addChild(background);
}

void DisclaimerLayer::initLabelAndText()
{
    auto disclaimer = Label::createWithTTF("Disclaimer", "fonts/firecat_medium.ttf", 32);
    disclaimer->setNormalizedPosition(Vec2(.5f, .8f));

    this->addChild(disclaimer);

    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto text = Text::create("Although these puzzles...", 10);

    text->setTextAreaSize(Size(visibleSize.width / 1.25f, 0));
    text->setNormalizedPosition(Vec2(.555f, .4f));

    this->addChild(text);
}

void DisclaimerLayer::initButtons()
{
    auto buttonOptions = MenuItemSprite::create(
                                                Sprite::createWithSpriteFrameName("ButtonBack.png"),
                                                nullptr,
                                                Sprite::createWithSpriteFrameName("ButtonBack.png"),
                                                CC_CALLBACK_1(DisclaimerLayer::menuOptionsCallback, this));

    buttonOptions->setNormalizedPosition(Vec2(.1f, .85f));
    buttonOptions->setRotation(3.5f);

    auto menu = Menu::create(buttonOptions, nullptr);

    menu->setPosition(Vec2::ZERO);

    this->addChild(menu);
}

void DisclaimerLayer::menuOptionsCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playButtonGoSound();

    auto button = (MenuItemSprite*)pSender;

    auto popScene = CallFunc::create([&]() {
        Director::getInstance()->popScene();
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), popScene, nullptr);

    button->runAction(seq);
}
