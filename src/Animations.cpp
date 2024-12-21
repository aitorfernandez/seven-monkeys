//
//  Animations.cpp
//  SevenMonkeys
//

#include "Animations.hpp"

USING_NS_CC;

void Animations::initFairy()
{
    AnimationCache::getInstance()->addAnimation(createAnimation("Fairy%02d.png", 1, 28, .075f), "Fairy");
    AnimationCache::getInstance()->addAnimation(createAnimation("FairyHouseSmoke%04d.png", 1, 80, .075f), "FairyHouseSmoke");
}

void Animations::initCountDown()
{
     AnimationCache::getInstance()->addAnimation(createAnimation("CountDown%02d.png", 1, 96, .025f), "CountDown");
}

void Animations::initStarsMarkers()
{
    AnimationCache::getInstance()->addAnimation(createAnimation("StarsMarker0%02d.png", 1, 14, .1f), "StarsMarker0");
}

Animation* Animations::createAnimation(const char* prefixName, int start, int end, float delay)
{
    Vector<SpriteFrame*> animFrames;

    for (short i = start; i <= end; ++i)
    {
        auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format(prefixName, i));

        if (spriteFrame)
            animFrames.pushBack(spriteFrame);
    }

    return Animation::createWithSpriteFrames(animFrames, delay);
}
