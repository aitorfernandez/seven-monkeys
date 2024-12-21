//
//  CreditsLayer.hpp
//  SevenMonkeys
//

#ifndef CreditsLayer_hpp
#define CreditsLayer_hpp

#include "SevenMonkeys.hpp"

#include "OptionsLayer.hpp"

class CreditsLayer : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    CreditsLayer();
    virtual ~CreditsLayer();

    virtual bool init();

    void initBackground();
    void initLabels();
    void initButtons();

    CREATE_FUNC(CreditsLayer);

private:

    void menuNextCallback(cocos2d::Ref* pSender);
    void menuOptionsCallback(cocos2d::Ref* pSender);

    void runCreditActions();

    cocos2d::MenuItemSprite* mvButtonNext;

    cocos2d::Label* mvpCreditLabel;
    cocos2d::Label* mvpCreditContentLabel;

    std::vector<std::string> mvCredits;
    std::vector<std::string> mvCreditsContent;

    int mvCurrentCredit;
};

#endif /* CreditsLayer_hpp */
