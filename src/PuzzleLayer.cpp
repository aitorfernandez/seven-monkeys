//
//  PuzzleLayer.cpp
//  SevenMonkeys
//

#include "PuzzleLayer.hpp"

USING_NS_CC;

PuzzleLayer::PuzzleLayer()
{
    CCLOG("// PuzzleLayer %x Constructor", (int)(long)this);

    setRunningPuzzle(false);
    setWaitingPuzzle(false);

    mvTouches = 0;
    mvRightTouches = 0;
}

PuzzleLayer::~PuzzleLayer()
{
    CCLOG("// PuzzleLayer %x Destructor", (int)(long)this);

    for (auto &player : mtpPlayers) {
        delete player;
    }

    for (auto &token : mtpTokens) {
        delete token;
    }

    mtpPlayers.clear();
    mtpPlayers.shrink_to_fit();

    mtpTokens.clear();
    mtpTokens.shrink_to_fit();
}

bool PuzzleLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    mvTickThresholdX = .0f;

    mvIsPause = false;

    // Touch events

    mvpEventTouch = EventListenerTouchOneByOne::create();
    mvpEventTouch->setSwallowTouches(true);
    mvpEventTouch->onTouchBegan = CC_CALLBACK_2(PuzzleLayer::onTouchBegan, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mvpEventTouch, this);

    return true;
}

void PuzzleLayer::pushPlayer(Player *player)
{
    mtpPlayers.push_back(player);
}

void PuzzleLayer::pushToken(Token *token)
{
    mtpTokens.push_back(token);
}

void PuzzleLayer::scheduleHelpPlayer()
{
    if (UserDefault::getInstance()->getIntegerForKey("mode") == EASY) {
        this->scheduleOnce(CC_SCHEDULE_SELECTOR(PuzzleLayer::helpPlayer), 4.0f);
    }
}

void PuzzleLayer::removeScheduleHelpPlayer()
{
    if (UserDefault::getInstance()->getIntegerForKey("mode") == EASY) {
        this->unschedule(CC_SCHEDULE_SELECTOR(PuzzleLayer::helpPlayer));
    }
}

void PuzzleLayer::helpPlayer(float dt)
{
    auto child = this->getChildByTag(mtRightAnswer);

    auto label = this->getChildByTag(kTagsPuzzle::labels + mtRightAnswer);

    if (child)
        child->runAction(Blink::create(1, 4));

    if (label)
        label->runAction(Blink::create(1, 4));
}

void PuzzleLayer::onEnter()
{
    Layer::onEnter();
    addCustomEvents();
}

void PuzzleLayer::onExit()
{
    Layer::onExit();
    removeEvents();
}

void PuzzleLayer::addCustomEvents()
{
    mvpEventExitCountDown = EventListenerCustom::create(ON_EXIT_COUNT_DOWN, [=](EventCustom* event) {
        start();
    });

    _eventDispatcher->addEventListenerWithFixedPriority(mvpEventExitCountDown, 1);

    mvpEventHUDFinish = EventListenerCustom::create(FINISH_HUD, [=](EventCustom* event) {
        finish();
    });

    _eventDispatcher->addEventListenerWithFixedPriority(mvpEventHUDFinish, 1);

    mvpEventTogglePause = EventListenerCustom::create(TOGGLE_PAUSE, [=](EventCustom* event) {
        mvIsPause = !mvIsPause;
    });

    _eventDispatcher->addEventListenerWithFixedPriority(mvpEventTogglePause, 1);
}

void PuzzleLayer::removeEvents()
{
    _eventDispatcher->removeEventListener(mvpEventExitCountDown);
    _eventDispatcher->removeEventListener(mvpEventHUDFinish);
    _eventDispatcher->removeEventListener(mvpEventTogglePause);

    _eventDispatcher->removeEventListener(mvpEventTouch);
}

void PuzzleLayer::start()
{
    switch (UserDefault::getInstance()->getIntegerForKey("currentLevel")) {
        case (0): {
            Game::instance().getSoundManager().playPokerHandsMusic();
        }
        break;

        case (1): {
            Game::instance().getSoundManager().playOrderMusic();
        }
        break;

        case (2): {
            Game::instance().getSoundManager().playBestHandMusic();
        }
        break;

        case (3): {
            Game::instance().getSoundManager().playOutsMusic();
        }
        break;

        case (4): {
            Game::instance().getSoundManager().playOddsMusic();
        }
        break;

        case (5): {
            Game::instance().getSoundManager().playFlopTextureMusic();
        }
        break;

        case (6): {
            Game::instance().getSoundManager().playPreFlopMusic();
        }
        break;
    }

    setRunningPuzzle(true);
}

void PuzzleLayer::finish()
{
    Game::instance().getSoundManager().stopMusic();

    setRunningPuzzle(false);

    removeScheduleHelpPlayer();

    Vector<Node *> children = this->getChildren();

    for (auto& child : children) {
        if (
            child->getLocalZOrder() == kZOrderPuzzle::communityCards ||
            child->getLocalZOrder() == kZOrderPuzzle::players ||
            child->getLocalZOrder() == kZOrderPuzzle::holeCards ||
            child->getLocalZOrder() == kZOrderPuzzle::btn ||
            child->getLocalZOrder() == kZOrderPuzzle::blinds ||
            child->getLocalZOrder() == kZOrderPuzzle::stack ||
            child->getLocalZOrder() == kZOrderPuzzle::pot ||
            child->getLocalZOrder() == kZOrderPuzzle::actions ||
            child->getLocalZOrder() == kZOrderPuzzle::tokens ||
            child->getLocalZOrder() == kZOrderPuzzle::ticks) {

            child->setOpacity(HALF_OPACITY);
        }
    }
}

void PuzzleLayer::addTickRight(int tag, Vec2 pos)
{
    auto tickRight = Sprite::createWithSpriteFrameName("TickRight.png");

    tickRight->setNormalizedPosition(Vec2(pos.x - mvTickThresholdX, pos.y - .03f));

    this->addChild(tickRight, kZOrderPuzzle::ticks);
}

void PuzzleLayer::addTickWrong(int tag, Vec2 pos)
{
    auto tickWrong = Sprite::createWithSpriteFrameName("TickWrong.png");

    tickWrong->setNormalizedPosition(Vec2(pos.x - mvTickThresholdX, pos.y - .03f));

    this->addChild(tickWrong, kZOrderPuzzle::ticks);
}


// Touch stuff...

bool PuzzleLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    return isRunningPuzzle() && !mvIsPause;
}

// PokerHands

void PuzzleLayer::setPokerHandsTouch()
{
    mvpEventTouch->onTouchEnded = CC_CALLBACK_2(PuzzleLayer::onPokerHandsTouchEnded, this);

    mvTickThresholdX = .065f;
}

void PuzzleLayer::onPokerHandsTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("// PokerHandsPuzzle::onPokerHandsTouchEnded...");
    checkTouch(touch, event);
}

// Order

void PuzzleLayer::setOrderTouch()
{
    mvpEventTouch->onTouchEnded = CC_CALLBACK_2(PuzzleLayer::onOrderTouchEnded, this);

    mvTickThresholdX = .05f;
}

void PuzzleLayer::onOrderTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("// PokerHandsPuzzle::onOrderTouchEnded...");
    checkTouch(touch, event);
}

// BestHand

void PuzzleLayer::setBestHandTouch()
{
    mvpEventTouch->onTouchEnded = CC_CALLBACK_2(PuzzleLayer::onBestHandTouchEnded, this);

    mvTickThresholdX = .045f;
}

void PuzzleLayer::onBestHandTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("// PokerHandsPuzzle::onBestHandTouchEnded...");

    Node *target = event->getCurrentTarget();
    Point touchPosition = target->convertTouchToNodeSpace(touch);

    Vector<Node *> children = this->getChildren();

    for (auto& child : children) {
        if (child->getLocalZOrder() == kZOrderPuzzle::players &&
            child->getBoundingBox().containsPoint(touchPosition)) {

            int tag = child->getTag();

            if (mtpPlayers[tag]->isWinner()) {
                addTickRight(tag, mtpPlayers[tag]->mPositions.sticker);

                dispatchRightEvent();
            }
            else {
                addTickWrong(tag, mtpPlayers[tag]->mPositions.sticker);

                dispatchWrongEvent();
            }

            resetAll();

            break;
        }
    }
}

// Outs

void PuzzleLayer::setOutsTouch()
{
    mvpEventTouch->onTouchEnded = CC_CALLBACK_2(PuzzleLayer::onOutsTouchEnded, this);

    mvTickThresholdX = .05f;
}

void PuzzleLayer::onOutsTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("// PokerHandsPuzzle::onOutsTouchEnded...");
    checkTouch(touch, event);
}

// Odds

void PuzzleLayer::setOddsTouch()
{
    mvpEventTouch->onTouchEnded = CC_CALLBACK_2(PuzzleLayer::onOddsTouchEnded, this);

    mvTickThresholdX = .05f;
}

void PuzzleLayer::onOddsTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("// PokerHandsPuzzle::onOddsTouchEnded...");
    checkTouch(touch, event);
}

// FlopTextue

void PuzzleLayer::setFlopTextureTouch()
{
    mvpEventTouch->onTouchEnded = CC_CALLBACK_2(PuzzleLayer::onFlopTextureTouchEnded, this);

    mvTickThresholdX = .055f;
}

void PuzzleLayer::onFlopTextureTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("// PokerHandsPuzzle::onFlopTextureTouchEnded...");

    Node *target = event->getCurrentTarget();
    Point touchPosition = target->convertTouchToNodeSpace(touch);

    Vector<Node *> children = this->getChildren();

    for (auto& child : children) {
        if (child->getLocalZOrder() == kZOrderPuzzle::tokens &&
            child->getBoundingBox().containsPoint(touchPosition)) {

            int tag = child->getTag();

            if (mtpTokens[tag]->isClicked()) {
                break;
            }

            mvTouches++;

            if (mtpTokens[tag]->isCorrect()) {

                mvRightTouches++;

                mtpTokens[tag]->setClicked(true);

                addTickRight(tag, mtpTokens[tag]->getPosition());

                child->setOpacity(HALF_OPACITY);
            }
            else {
                addTickWrong(tag, mtpTokens[tag]->getPosition());

                dispatchWrongEvent();

                resetAll();

                break;
            }

            if (mvTouches == UserDefault::getInstance()->getIntegerForKey("mode")) {

                if (mvRightTouches == UserDefault::getInstance()->getIntegerForKey("mode")) {
                    addTickRight(tag, mtpTokens[tag]->getPosition());

                    dispatchRightEvent();
                }
                else {
                    addTickWrong(tag, mtpTokens[tag]->getPosition());

                    dispatchWrongEvent();
                }

                resetAll();
            }

            break;
        }
    }
}

// PreFlop

void PuzzleLayer::setPreFlopTouch()
{
    mvpEventTouch->onTouchEnded = CC_CALLBACK_2(PuzzleLayer::onPreFlopTouchEnded, this);

    mvTickThresholdX = .06f;
}

void PuzzleLayer::onPreFlopTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("// PokerHandsPuzzle::onPreFlopTouchEnded...");
    checkTouch(touch, event);
}


void PuzzleLayer::checkTouch(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Node *target = event->getCurrentTarget();
    Point touchPosition = target->convertTouchToNodeSpace(touch);

    Vector<Node *> children = this->getChildren();

    for (auto& child : children) {
        if (child->getLocalZOrder() == kZOrderPuzzle::tokens &&
            child->getBoundingBox().containsPoint(touchPosition)) {

            int tag = child->getTag();

            if (mtpTokens[tag]->isCorrect()) {
                addTickRight(tag, mtpTokens[tag]->getPosition());

                dispatchRightEvent();
            } else {
                addTickWrong(tag, mtpTokens[tag]->getPosition());

                dispatchWrongEvent();
            }

            resetAll();

            break;
        }
    }
}

void PuzzleLayer::removeChildren()
{
    Vector<Node *> children = this->getChildren();

    for (auto& child : children) {
        if (
            child->getLocalZOrder() == kZOrderPuzzle::communityCards ||
            child->getLocalZOrder() == kZOrderPuzzle::players ||
            child->getLocalZOrder() == kZOrderPuzzle::holeCards ||
            child->getLocalZOrder() == kZOrderPuzzle::btn ||
            child->getLocalZOrder() == kZOrderPuzzle::blinds ||
            child->getLocalZOrder() == kZOrderPuzzle::stack ||
            child->getLocalZOrder() == kZOrderPuzzle::pot ||
            child->getLocalZOrder() == kZOrderPuzzle::actions ||
            child->getLocalZOrder() == kZOrderPuzzle::tokens ||
            child->getLocalZOrder() == kZOrderPuzzle::ticks) {

            auto seq = Sequence::create(FadeOut::create(.15f), RemoveSelf::create(true), nullptr);

            child->runAction(seq);
        }
    }
}

void PuzzleLayer::cleanUpPlayers()
{
    for(auto& player : mtpPlayers) {
        player->cleanUp();
    }
}

void PuzzleLayer::cleanUpTokens()
{
    for(auto& token : mtpTokens) {
        token->cleanUp();
    }
}

void PuzzleLayer::resetAll()
{
    removeScheduleHelpPlayer();

    auto clean = CallFunc::create([&]() {
        mvTouches = 0;
        mvRightTouches = 0;

        removeChildren();

        cleanUpPlayers();
        cleanUpTokens();

        setWaitingPuzzle(false);
    });

    // Keep the answer on screen before reset all
    auto seq = Sequence::create(DelayTime::create(.25f), clean, nullptr);

    this->runAction(seq);
}

void PuzzleLayer::dispatchRightEvent()
{
    EventCustom event(RIGHT_ANSWER);
    _eventDispatcher->dispatchEvent(&event);
}

void PuzzleLayer::dispatchWrongEvent()
{
    if (UserDefault::getInstance()->getIntegerForKey("vibrate") == 1)
        Device::vibrate(.1f);

    EventCustom event(WRONG_ANSWER);
    _eventDispatcher->dispatchEvent(&event);
}
