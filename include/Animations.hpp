//
//  Animations.hpp
//  SevenMonkeys
//

#ifndef Animations_hpp
#define Animations_hpp

#include "SevenMonkeys.hpp"

class Animations
{
public:

    ~Animations() = default;

    void initFairy();
    void initCountDown();
    void initStarsMarkers();

private:

    cocos2d::Animation* createAnimation(const char* prefixName, int start, int end, float delay);
};

#endif /* Animations_hpp */
