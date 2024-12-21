//
//  CloudsLayer.hpp
//  SevenMonkeys
//

#ifndef CloudsLayer_hpp
#define CloudsLayer_hpp

#include "SevenMonkeys.hpp"

#include "Rand.hpp"

class CloudsLayer : public cocos2d::Layer
{
public:

    CloudsLayer();
    virtual ~CloudsLayer();

    virtual bool init(const char* color);

    CREATE_FUNC_1(CloudsLayer, const char *);

private:

    rapidjson::Document mvDocument;
};

#endif /* CloudsLayer_hpp */
