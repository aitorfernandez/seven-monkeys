//
//  DisclaimerLayer.hpp
//  SevenMonkeys
//

#ifndef DisclaimerLayer_hpp
#define DisclaimerLayer_hpp

#include "SevenMonkeys.hpp"

#include "OptionsLayer.hpp"

class DisclaimerLayer : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    DisclaimerLayer();
    virtual ~DisclaimerLayer();

    virtual bool init();

    void initBackground();
    void initLabelAndText();
    void initButtons();

    CREATE_FUNC(DisclaimerLayer);

private:

    void menuOptionsCallback(cocos2d::Ref* pSender);
};

#endif /* Credits_hpp */
