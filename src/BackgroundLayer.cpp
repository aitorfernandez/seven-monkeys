//
//  BackgroundLayer.cpp
//  SevenMonkeys
//

#include "BackgroundLayer.hpp"

USING_NS_CC;

BackgroundLayer::BackgroundLayer()
{
    CCLOG("// BackgroundLayer %x Constructor", (int)(long)this);
}

BackgroundLayer::~BackgroundLayer()
{
    CCLOG("// BackgroundLayer %x Destructor", (int)(long)this);
}

bool BackgroundLayer::init(const std::string &filename)
{
    if (!Layer::init()) {
        return false;
    }

    auto background = Sprite::createWithSpriteFrameName(filename);
    background->setNormalizedPosition(Vec2(.5f, .5f));

    this->addChild(background);

    return true;
}
