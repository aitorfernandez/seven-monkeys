//
//  MapLayer.hpp
//  SevenMonkeys
//

#ifndef MapLayer_hpp
#define MapLayer_hpp

#include "SevenMonkeys.hpp"

#include "MainLayer.hpp"
#include "FairyHouseLayer.hpp"

class MapLayer : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    MapLayer();
    virtual ~MapLayer();

    virtual bool init();

    void initBackground();
    void initFairyHouseAnim();
    void initMapAreas();
    void initMonkeyMarkers();
    void initFairyMarker();
    void initButtons();

    CREATE_FUNC(MapLayer);

    void onEnter();
    void onExit();

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:

    void menuExitMapCallback(cocos2d::Ref* pSender);

    void addEvents();
    void removeEvents();

    void runMarkerActions();

    cocos2d::EventListenerTouchOneByOne* mvpEventTouch;

    enum kZOrder
    {
        background,
        area,
        marker,
        animations
    };

    enum kTag
    {
        fairyHouse = 90
    };

    std::vector<cocos2d::Vec2> mvPositionAreas {
        cocos2d::Vec2(0.15, 0.37),
        cocos2d::Vec2(0.17, 0.73),
        cocos2d::Vec2(0.86, 0.38),
        cocos2d::Vec2(0.55, 0.49),
        cocos2d::Vec2(0.83, 0.73),
        cocos2d::Vec2(0.675, 0.49),
        cocos2d::Vec2(0.5, 0.83)
    };

    std::vector<cocos2d::Vec2> mvPositionMarkers {
        cocos2d::Vec2(0.17, 0.44),
        cocos2d::Vec2(0.2, 0.72),
        cocos2d::Vec2(0.875, 0.4),
        cocos2d::Vec2(0.555, 0.625),
        cocos2d::Vec2(0.83, 0.73),
        cocos2d::Vec2(0.675, 0.49),
        cocos2d::Vec2(0.5, 0.82)
    };

    // rapidjson::Document mvDocument;
};

#endif /* MapLayer_hpp */
