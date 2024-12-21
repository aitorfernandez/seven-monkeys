//
//  BackgroundLayer.hpp
//  SevenMonkeys
//

#ifndef BackgroundLayer_hpp
#define BackgroundLayer_hpp

#include "SevenMonkeys.hpp"

class BackgroundLayer : public cocos2d::Layer
{
public:

    BackgroundLayer();
    virtual ~BackgroundLayer();

    virtual bool init(const std::string& filename);

    CREATE_FUNC_1(BackgroundLayer, const std::string &);
};

#endif /* BackgroundLayer_hpp */
