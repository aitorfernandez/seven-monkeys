
//
//  FairyHouseLayer.hpp
//  SevenMonkeys
//

#ifndef FairyHouseLayer_hpp
#define FairyHouseLayer_hpp

#include "SevenMonkeys.hpp"

#include "MapLayer.hpp"

class FairyHouseLayer : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    FairyHouseLayer();
    virtual ~FairyHouseLayer();

    virtual bool init();

    void initBackground();
    void initTutorials();
    void initListView();
    void initButtons();

    CREATE_FUNC(FairyHouseLayer);

    void onEnter();
    void onExit();

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:

    void addEvents();
    void removeEvents();

    void menuGoBackCallback(cocos2d::Ref* pSender);

    void menuLeftCallback(cocos2d::Ref* pSender);
    void menuRightCallback(cocos2d::Ref* pSender);

    void enabledButtons();

    cocos2d::EventListenerTouchOneByOne* mvpEventTouch;

    cocos2d::MenuItemSprite* mvpButtonLeft;
    cocos2d::MenuItemSprite* mvpButtonRight;

    void setMessage();

    int mvCurrentMessage;

    std::vector<std::string> mvMessages;

    rapidjson::Document mvFairyHouseDocument;

    enum kZOrder
    {
        messages = 80,
        picture,
        menu
    };

    enum kTag
    {
        listView = 90
    };
};

#endif /* FairyHouseLayer_hpp */
