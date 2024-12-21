//
//  FairyLayer.hpp
//  SevenMonkeys
//

#ifndef FairyLayer_hpp
#define FairyLayer_hpp

#include "SevenMonkeys.hpp"

#include "FairyHouseLayer.hpp"

class FairyLayer : public cocos2d::Layer
{
public:

    FairyLayer();
    virtual ~FairyLayer();

    virtual bool init();

    CREATE_FUNC(FairyLayer);

    void onEnter();
    void onExit();

    void addMessage(const std::string& message);

private:

    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuLeftCallback(cocos2d::Ref* pSender);
    void menuRightCallback(cocos2d::Ref* pSender);

    void enabledButtons();

    cocos2d::MenuItemSprite* mvpButtonLeft;
    cocos2d::MenuItemSprite* mvpButtonRight;

    cocos2d::Label* mvpMessage;

    std::vector<std::string> mvMessages;

    int mvCurrentMessage;
};

#endif /* FairyLayer_hpp */
