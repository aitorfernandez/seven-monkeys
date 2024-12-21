//
//  CountDownLayer.cpp
//  SevenMonkeys
//

#include "CountDownLayer.hpp"

USING_NS_CC;

CountDownLayer::CountDownLayer()
{
    CCLOG("// CountDownLayer %x Constructor", (int)(long)this);
}

CountDownLayer::~CountDownLayer()
{
    CCLOG("// CountDownLayer %x Destructor", (int)(long)this);
}

bool CountDownLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    return true;
}

void CountDownLayer::onEnter()
{
    Layer::onEnter();
    addEvents();
}

void CountDownLayer::onExit()
{
    Layer::onExit();
    removeEvents();

    EventCustom event(ON_EXIT_COUNT_DOWN);
    _eventDispatcher->dispatchEvent(&event);
}

void CountDownLayer::addEvents()
{
    mvpEvent = EventListenerCustom::create(ON_EXIT_FAIRY, [=](EventCustom* event) {
        start();
    });

    _eventDispatcher->addEventListenerWithFixedPriority(mvpEvent, 1);
}

void CountDownLayer::removeEvents()
{
    _eventDispatcher->removeEventListener(mvpEvent);
}

void CountDownLayer::start()
{
    Game::instance().getSoundManager().playCountDownSound();

    auto countDownSprite = Sprite::createWithSpriteFrameName("CountDown01.png");
    countDownSprite->setNormalizedPosition(Vec2(.5f, .5f));

    this->addChild(countDownSprite);

    countDownSprite->runAction(Sequence::create(
                                                Animate::create(AnimationCache::getInstance()->getAnimation("CountDown")),
                                                RemoveSelf::create(true),
                                                CallFunc::create(CC_CALLBACK_0(CountDownLayer::onCountdownFinish, this)),
                                                nullptr));
}

void CountDownLayer::onCountdownFinish()
{
    this->removeFromParentAndCleanup(true);
}
