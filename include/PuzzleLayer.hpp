//
//  PuzzleLayer.hpp
//  SevenMonkeys
//
//

#ifndef PuzzleLayer_h
#define PuzzleLayer_h

#include "SevenMonkeys.hpp"

#include "Game.hpp"

#include "Player.hpp"
#include "Token.hpp"

class PuzzleLayer : public cocos2d::Layer
{
public:

    PuzzleLayer();
    virtual ~PuzzleLayer();

    virtual bool init();

    void onEnter();
    void onExit();

    void start();
    void finish();

    CC_SYNTHESIZE_BOOL(mtRunningPuzzle, RunningPuzzle);
    CC_SYNTHESIZE_BOOL(mtWaitingPuzzle, WaitingPuzzle);

    // Touch stuff...

    void setPokerHandsTouch();
    void onPokerHandsTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void setOrderTouch();
    void onOrderTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void setBestHandTouch();
    void onBestHandTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void setOutsTouch();
    void onOutsTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void setFlopTextureTouch();
    void onFlopTextureTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void setOddsTouch();
    void onOddsTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void setPreFlopTouch();
    void onPreFlopTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);


    void pushPlayer(Player *player);
    void pushToken(Token *token);

    void scheduleHelpPlayer();

protected:

    std::vector<Player*> mtpPlayers;
    std::vector<Token*> mtpTokens;

    int mtRightAnswer;

private:

    float mvTickThresholdX;

    bool mvIsPause;

    int mvTouches;
    int mvRightTouches;

    void checkTouch(cocos2d::Touch* touch, cocos2d::Event* event);

    void addTickRight(int tag, cocos2d::Vec2 pos);
    void addTickWrong(int tag, cocos2d::Vec2 pos);

    void helpPlayer(float dt);

    void cleanUpPlayers();
    void cleanUpTokens();

    void removeChildren();

    void resetAll();

    void addCustomEvents();
    void removeEvents();

    void removeScheduleHelpPlayer();

    void dispatchRightEvent();
    void dispatchWrongEvent();

    cocos2d::EventListenerCustom *mvpEventExitCountDown;
    cocos2d::EventListenerCustom *mvpEventHUDFinish;
    cocos2d::EventListenerCustom *mvpEventTogglePause;

    cocos2d::EventListenerTouchOneByOne* mvpEventTouch;
};

#endif /* PuzzleLayer_hpp */
