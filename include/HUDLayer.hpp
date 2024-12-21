//
//  HUDLayer.hpp
//  SevenMonkeys
//

#ifndef HUDLayer_hpp
#define HUDLayer_hpp

#include "SevenMonkeys.hpp"

#include "Rand.hpp"

#include "MapLayer.hpp"
#include "EndLayer.hpp"

class HUDLayer : public cocos2d::Layer
{
public:

    HUDLayer();
    virtual ~HUDLayer();

    virtual bool init(const float puzzleTime, const int firstLevel, const int lastLevel, const float penalty);

    void initLevelUp(const int &firstLevel, const int &lastLevel);
    void initClock();
    void initStars();
    void initButtons();
    void initPlayerSpeed();
    void initPause();

    static HUDLayer* create(const float puzzleTime, const int firstLevel, const int lastLevel, const float penalty);

    void onEnter();
    void onExit();

    void rightAnswer();
    void wrongAnswer();

    void start();
    void finish();

    void update(float dt);

    void menuPauseCallback(cocos2d::Ref* pSender);
    void menuExitCallback(cocos2d::Ref* pSender);

private:

    bool mvIsPause;
    bool mvIsAlarmRinging;

    int mvAnswersCounter;
    int mvCurrentStar;

    void addEvents();
    void removeEvents();

    void setStarsProgress();

    void showPlayerSpeed();

    float mvTime;
    float mvPuzzleTime;

    float mvPenalty;

    cocos2d::Label *mvpClockCounter;

    // cocos2d::Label *tempCounter;

    cocos2d::EventListenerCustom *mvpEventExitCountDown;
    cocos2d::EventListenerCustom *mvpEventRightAnswer;
    cocos2d::EventListenerCustom *mvpEventWrongAnswer;

    cocos2d::Vector<cocos2d::Sprite*> mvpPlayerSpeed;
    cocos2d::Vector<cocos2d::ProgressTimer*> mvpStars;

    cocos2d::Menu* mvpMenu;

    std::vector<int> mvLevelUp;

    int mvPercentCounter;

    enum kZOrder
    {
        menu = 9,
        playerSpeed,
        exit,
        stars,
        pause
    };

    enum kTag
    {
        backgroundPause,
        clock,
        starsProgressContent,
        counterLabel
    };
};

#endif /* HUDLayer_hpp */
