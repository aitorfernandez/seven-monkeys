//
//  FairyLayer.cpp
//  SevenMonkeys
//

#include "FairyLayer.hpp"

USING_NS_CC;

FairyLayer::FairyLayer()
{
    CCLOG("// FairyLayer %x Constructor", (int)(long)this);
}

FairyLayer::~FairyLayer()
{
    CCLOG("// FairyLayer %x Destructor", (int)(long)this);

    mvMessages.clear();
    mvMessages.shrink_to_fit();

    if (mvpMessage) {
        this->mvpMessage->removeFromParentAndCleanup(true);
        mvpMessage = nullptr;
    }
}

bool FairyLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    auto parchment = Sprite::createWithSpriteFrameName("Parchment.png");
    parchment->setNormalizedPosition(Vec2(.5f, .5f));

    this->addChild(parchment);

    // Fairy

    auto fairySprite = Sprite::createWithSpriteFrameName("Fairy01.png");
    fairySprite->setNormalizedPosition(Vec2(.1f, .8f));

    this->addChild(fairySprite);

    fairySprite->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("Fairy"))));

    // Messages

    auto visibleSize = Director::getInstance()->getVisibleSize();

    mvCurrentMessage = 0;

    mvpMessage = Label::createWithTTF("",
                                      "fonts/OpenSans-Semibold.ttf",
                                      10,
                                      Size(visibleSize.width / 1.7f, 0),
                                      TextHAlignment::CENTER);

    mvpMessage->setNormalizedPosition(Vec2(.5f, .525f));
    mvpMessage->setLineHeight(27.5f);

    this->addChild(mvpMessage);

    // UI Buttons

    auto buttonClose = MenuItemSprite::create(
                                              Sprite::createWithSpriteFrameName("NavClose.png"),
                                              nullptr,
                                              Sprite::createWithSpriteFrameName("NavClose.png"),
                                              CC_CALLBACK_1(FairyLayer::menuCloseCallback, this));

    buttonClose->setNormalizedPosition(Vec2(.75f, .64f));

    mvpButtonLeft = MenuItemSprite::create(
                                           Sprite::createWithSpriteFrameName("NavPrev.png"),
                                           nullptr,
                                           Sprite::createWithSpriteFrameName("NavPrev.png"),
                                           CC_CALLBACK_1(FairyLayer::menuLeftCallback, this));

    mvpButtonLeft->setNormalizedPosition(Vec2(.47f, .38f));

    mvpButtonRight = MenuItemSprite::create(
                                            Sprite::createWithSpriteFrameName("NavNext.png"),
                                            nullptr,
                                            Sprite::createWithSpriteFrameName("NavNext.png"),
                                            CC_CALLBACK_1(FairyLayer::menuRightCallback, this));

    mvpButtonRight->setNormalizedPosition(Vec2(.53f, .38f));

    // create menu, it's an autorelease object
    auto menu = Menu::create(buttonClose, mvpButtonLeft, mvpButtonRight, nullptr);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu);

    return true;
}

void FairyLayer::addMessage(const std::string& message)
{
    mvMessages.push_back(message);
}

void FairyLayer::onEnter()
{
    Layer::onEnter();

    mvpMessage->setString(mvMessages[mvCurrentMessage]);

    if (mvCurrentMessage == 0) {
        mvpButtonLeft->setOpacity(55);
        mvpButtonLeft->setEnabled(false);
    }
}

void FairyLayer::onExit()
{
    Layer::onExit();

    EventCustom event(ON_EXIT_FAIRY);
    _eventDispatcher->dispatchEvent(&event);
}

void FairyLayer::menuCloseCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playNavCloseSound();
    
    auto button = (MenuItemSprite*)pSender;

    auto remove = CallFunc::create([&]() {
        this->removeFromParentAndCleanup(true);
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), remove, nullptr);

    button->runAction(seq);
}

void FairyLayer::menuLeftCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playNavPrevSound();

    auto button = (MenuItemSprite*)pSender;

    auto setButtonValues = CallFunc::create([&]() {
        enabledButtons();

        mvCurrentMessage--;

        if (mvCurrentMessage <= 0) {
            mvCurrentMessage = 0;

            mvpButtonLeft->setOpacity(HALF_OPACITY);
            mvpButtonLeft->setEnabled(false);
        }

        mvpMessage->setString(mvMessages[mvCurrentMessage]);
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), setButtonValues, nullptr);

    button->runAction(seq);
}

void FairyLayer::menuRightCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playNavNextSound();

    auto button = (MenuItemSprite*)pSender;

    auto setButtonValues = CallFunc::create([&]() {
        enabledButtons();

        mvCurrentMessage++;

        if (mvCurrentMessage >= mvMessages.size() - 1) {
            mvCurrentMessage = (int)mvMessages.size() - 1;

            mvpButtonRight->setOpacity(HALF_OPACITY);
            mvpButtonRight->setEnabled(false);
        }

        mvpMessage->setString(mvMessages[mvCurrentMessage]);
    });

    auto scaleBy = ScaleBy::create(.1f, .95f);
    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), setButtonValues, nullptr);

    button->runAction(seq);
}

void FairyLayer::enabledButtons()
{
    mvpButtonLeft->setOpacity(FULL_OPACITY);
    mvpButtonRight->setOpacity(FULL_OPACITY);

    mvpButtonLeft->setEnabled(true);
    mvpButtonRight->setEnabled(true);
}
