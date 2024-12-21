//
//  LoadingLayer.hpp
//  SevenMonkeys
//

#ifndef LoadingLayer_hpp
#define LoadingLayer_hpp

#include "SevenMonkeys.hpp"

#include "Game.hpp"

#include "MainLayer.hpp"

class LoadingLayer : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    LoadingLayer();
    virtual ~LoadingLayer();

    virtual bool init();

    CREATE_FUNC(LoadingLayer);

    void update(float dt);

private:

    void loadResources();

    cocos2d::ProgressTimer *mvpProgressBar;

    int mvNumberOfResources;
};

#endif /* LoadingLayer_hpp */
