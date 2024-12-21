//
//  CloudsLayer.cpp
//  SevenMonkeys
//

#include "CloudsLayer.hpp"

USING_NS_CC;
USING_NS_SM;

CloudsLayer::CloudsLayer()
{
    CCLOG("// CloudsLayer %x Constructor", (int)(long)this);

    std::string fullPath = FileUtils::getInstance()->fullPathForFilename("data/CloudsLayer.json");
    std::string json = FileUtils::getInstance()->getStringFromFile(fullPath);

    mvDocument.Parse<rapidjson::ParseFlag::kParseDefaultFlags>(json.c_str());
}

CloudsLayer::~CloudsLayer()
{
    CCLOG("// CloudsLayer %x Destructor", (int)(long)this);
}

bool CloudsLayer::init(const char* color)
{
    if (!Layer::init()) {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    const rapidjson::Value& clouds = mvDocument[color];

    char cloudFrame[20] = { 0 };

    for (rapidjson::SizeType i = 0; i < clouds.Size(); i++) {

        if (strcmp(color, "white") != 0)
            sprintf(cloudFrame, "BlackCloud%02d.png", i + 1);
        else
            sprintf(cloudFrame, "WhiteCloud%02d.png", i + 1);

        auto cloudSprite = Sprite::createWithSpriteFrameName(cloudFrame);

        cloudSprite->setPosition(Vec2(origin.x + (((visibleSize.width / 2) * clouds[i][0].GetDouble()) / .5f),
                                      origin.y + (((visibleSize.height / 2) * clouds[i][1].GetDouble()) / .5f)));

        this->addChild(cloudSprite, i);

        auto delay = DelayTime::create(randFloat());

        Vec2 to = Vec2(origin.x + (i < 3 ? (visibleSize.width + 20) : ((visibleSize.width * -1) - 20)), 0);

        auto move = MoveBy::create(randInt(150, 450), to);
        auto sequence = Sequence::create(move, delay, move->reverse(), delay, nullptr);

        cloudSprite->runAction(RepeatForever::create(sequence));
    }

    return true;
}
