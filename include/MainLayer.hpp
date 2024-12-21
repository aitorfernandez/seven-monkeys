//
//  MainLayer.hpp
//  SevenMonkeys
//

#ifndef MainLayer_hpp
#define MainLayer_hpp

#include "SevenMonkeys.hpp"

#include "MapLayer.hpp"
#include "OptionsLayer.hpp"

class MainLayer : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    MainLayer();
    virtual ~MainLayer();

    virtual bool init();

    void initBackground();
    void initButtons();

    void onEnter();
    void onExit();

    CREATE_FUNC(MainLayer);

    void menuPlayCallback(cocos2d::Ref* pSender);
    void menuOptionsCallback(cocos2d::Ref* pSender);
};

#endif /* MainLayer_hpp */
