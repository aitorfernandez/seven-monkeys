//
//  OptionsLayer.hpp
//  SevenMonkeys
//

#ifndef OptionsLayer_hpp
#define OptionsLayer_hpp

#include "SevenMonkeys.hpp"

#include "Game.hpp"

#include "MainLayer.hpp"
#include "CreditsLayer.hpp"
#include "DisclaimerLayer.hpp"

class OptionsLayer : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    OptionsLayer();
    virtual ~OptionsLayer();

    virtual bool init();

    void initBackground();
    void initLabels();
    void initButtons();

    void onEnter();
    void onExit();

    CREATE_FUNC(OptionsLayer);

private:

    cocos2d::ui::CheckBox *mvpSound;
    cocos2d::ui::CheckBox *mvpMusic;
    cocos2d::ui::CheckBox *mvpVibrate;

    cocos2d::MenuItemSprite *mvpModeEasy;
    cocos2d::MenuItemSprite *mvpModeNormal;
    cocos2d::MenuItemSprite *mvpModeHard;

    void menuSoundCallback(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
    void menuMusicCallback(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);
    void menuVibrateCallback(cocos2d::Ref* pSender, cocos2d::ui::CheckBox::EventType type);

    void menuModeEasyCallback(cocos2d::Ref* pSender);
    void menuModeNormalCallback(cocos2d::Ref* pSender);
    void menuModeHardCallback(cocos2d::Ref* pSender);

    void menuMainCallback(cocos2d::Ref* pSender);

    void menuCreditsCallback(cocos2d::Ref* pSender);
    void menuResetCallback(cocos2d::Ref* pSender);
    void menuDisclaimerCallback(cocos2d::Ref* pSender);

    void selectDefaultOptions();

    cocos2d::ui::CheckBox* checkBoxCreate();
};

#endif /* OptionsLayer_hpp */
