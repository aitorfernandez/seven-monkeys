//
//  EndLayer.hpp
//  SevenMonkeys
//

#ifndef EndLayer_hpp
#define EndLayer_hpp

#include "SevenMonkeys.hpp"

#include "MainLayer.hpp"

class EndLayer : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();

    EndLayer();
    virtual ~EndLayer();

    virtual bool init();

    void onEnter();

    CREATE_FUNC(EndLayer);

private:

    void menuMainCallback(cocos2d::Ref* pSender);
};

#endif /* EndLayer_h */
