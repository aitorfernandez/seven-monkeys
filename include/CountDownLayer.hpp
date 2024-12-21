//
//  CountDownLayer.hpp
//  SevenMonkeys
//

#ifndef CountDownLayer_hpp
#define CountDownLayer_hpp

#include "SevenMonkeys.hpp"

#include "Game.hpp"

class CountDownLayer : public cocos2d::Layer
{
public:

    CountDownLayer();
    virtual ~CountDownLayer();

    virtual bool init();

    CREATE_FUNC(CountDownLayer);

    void onEnter();
    void onExit();

    void start();

    void onCountdownFinish();

private:

    void addEvents();
    void removeEvents();

    cocos2d::EventListenerCustom* mvpEvent;
};

#endif /* CountDownLayer_hpp */
