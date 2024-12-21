//
//  MapScene.cpp
//  SevenMonkeys
//

#include "MapLayer.hpp"

#include "PuzzleBuilder.hpp"
#include "Reader.hpp"

#include "CloudsLayer.hpp"

USING_NS_CC;

Scene* MapLayer::createScene()
{
    auto scene = Scene::create();

    auto mapLayerForeground = Sprite::createWithSpriteFrameName("MapLayerForeground.png");
    mapLayerForeground->setNormalizedPosition(Vec2(.5f, .805f));

    auto blackCloudsLayer = CloudsLayer::create("black");
    auto mapLayer = MapLayer::create();
    auto whiteCloudsLayer = CloudsLayer::create("white");

    scene->addChild(mapLayerForeground, 1);
    scene->addChild(blackCloudsLayer, 2);
    scene->addChild(mapLayer, 3);
    scene->addChild(whiteCloudsLayer, 4);

    return scene;
}

MapLayer::MapLayer()
{
    CCLOG("// MapLayer %x Constructor", (int)(long)this);

    // std::string fullPath = FileUtils::getInstance()->fullPathForFilename("data/MapLayer.json");
    // std::string json = FileUtils::getInstance()->getStringFromFile(fullPath);

    // mvDocument.Parse<rapidjson::ParseFlag::kParseDefaultFlags>(json.c_str());
}

MapLayer::~MapLayer()
{
    CCLOG("// MapLayer %x Destructor", (int)(long)this);

    mvPositionAreas.clear();
    mvPositionAreas.shrink_to_fit();

    mvPositionMarkers.clear();
    mvPositionMarkers.shrink_to_fit();

}

bool MapLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    initBackground();

    initFairyHouseAnim();

    initMapAreas();

    initMonkeyMarkers();

    initFairyMarker();

    initButtons();

    runMarkerActions();

    return true;
}

void MapLayer::initBackground()
{
    auto background = Sprite::createWithSpriteFrameName("MapLayerBackground.png");
    background->setNormalizedPosition(Vec2(.5f, .435f));

    this->addChild(background, kZOrder::background);
}

void MapLayer::initFairyHouseAnim()
{
    auto fairyHouseSmokeSprite = Sprite::createWithSpriteFrameName("FairyHouseSmoke0001.png");
    fairyHouseSmokeSprite->setNormalizedPosition(Vec2(.3f, .49f));

    this->addChild(fairyHouseSmokeSprite, kZOrder::animations);

    fairyHouseSmokeSprite->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("FairyHouseSmoke"))));
}

void MapLayer::initMapAreas()
{
    // const rapidjson::Value& areas = mvDocument["areas"];

    char levelKey[20];

    for (rapidjson::SizeType i = 0; i < mvPositionAreas.size(); i++) {
        auto areaFrameName = "MapLayerArea" + gPuzzles[i] + ".png";
        auto area = Sprite::createWithSpriteFrameName(areaFrameName);

        area->setNormalizedPosition(mvPositionAreas[i]);

        sprintf(levelKey, "%d-level%d", UserDefault::getInstance()->getIntegerForKey("mode"), i);

        if (UserDefault::getInstance()->getIntegerForKey(levelKey) == 0) {
            area->setColor(Color3B::ORANGE);
            area->setOpacity(HALF_OPACITY);
        }

        this->addChild(area, kZOrder::area);
    }
}

void MapLayer::initMonkeyMarkers()
{
    // const rapidjson::Value& markers = mvDocument["markers"];

    char levelKey[20];
    char speedMarkerKey[20];

    // for (rapidjson::SizeType i = 0; i < markers.Size(); i++) {
    for (rapidjson::SizeType i = 0; i < mvPositionMarkers.size(); i++) {

        sprintf(levelKey, "%d-level%d", UserDefault::getInstance()->getIntegerForKey("mode"), i);

        if ((UserDefault::getInstance()->getIntegerForKey(levelKey) != 0)) {

            sprintf(speedMarkerKey, "%d-%d-StarsMarker", UserDefault::getInstance()->getIntegerForKey("mode"), i);

            int speedMarker = UserDefault::getInstance()->getIntegerForKey(speedMarkerKey);

            std::string markerFrameName;

            if (speedMarker == 0) {
                markerFrameName = "StarsMarker003.png";
            }
            else {
                markerFrameName = "StarsMarker" +
                std::to_string(UserDefault::getInstance()->getIntegerForKey("mode")) +
                std::to_string(speedMarker) +
                ".png";
            }

            auto marker = Sprite::createWithSpriteFrameName(markerFrameName);

            marker->setNormalizedPosition(mvPositionMarkers[i]);

            this->addChild(marker, kZOrder::marker, i);
        }
    }
}

void MapLayer::initFairyMarker()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto fairyMarker = Sprite::createWithSpriteFrameName("FairyHouseMarker.png");

    fairyMarker->setPosition(Vec2(origin.x + (((visibleSize.width / 2) * .345f) / .5f),
                                  origin.y + (((visibleSize.height / 2) * .5f) / .5f)));

    this->addChild(fairyMarker, kZOrder::marker, kTag::fairyHouse);
}

void MapLayer::initButtons()
{
    auto buttonExitMap = MenuItemSprite::create(
                                                Sprite::createWithSpriteFrameName("ButtonExit.png"),
                                                nullptr,
                                                Sprite::createWithSpriteFrameName("ButtonExit.png"),
                                                CC_CALLBACK_1(MapLayer::menuExitMapCallback, this));

    buttonExitMap->setNormalizedPosition(Vec2(.1f, .125f));
    buttonExitMap->setRotation(5.5f);

    auto menu = Menu::create(buttonExitMap, nullptr);

    menu->setPosition(Vec2::ZERO);

    this->addChild(menu, (int)mvPositionAreas.size() + 1);
}

void MapLayer::runMarkerActions()
{
    auto delay = DelayTime::create(.25f);

    char levelKey[20];
    char speedMarkerKey[20];

    bool isNewArea = false;

    int mode = UserDefault::getInstance()->getIntegerForKey("mode");

    for (int i = 0; i < 7; ++i) {

        sprintf(levelKey, "%d-level%d", mode, i);
        sprintf(speedMarkerKey, "%d-%d-StarsMarker", mode, i);

        int level = UserDefault::getInstance()->getIntegerForKey(levelKey, gUserDefaultIntValue);
        int speedMarker = UserDefault::getInstance()->getIntegerForKey(speedMarkerKey, gUserDefaultIntValue);

        if (level == gUserDefaultIntValue) {
            break;
        }

        // Anim marker for new areas

        if (speedMarker == gUserDefaultIntValue) {

            auto marker = this->getChildByTag(i);

            auto seq = Sequence::create(
                                        delay,
                                        Animate::create(AnimationCache::getInstance()->getAnimation("StarsMarker0")),
                                        delay->clone(), nullptr);

            marker->runAction(RepeatForever::create(seq));

            isNewArea = true;
        }
        // No animation if there are 4 stars in that area
        else if (speedMarker != 4) {

            // Bounce random Markers for discovered areas...

            auto move = MoveBy::create(1.5, Vec2(0, 15));
            auto moveEaseIn = EaseBounceIn::create(move->clone());

            auto seq = Sequence::create(
                                        DelayTime::create(sevenmonkeys::randInt(sevenmonkeys::randInt(8), 16)),
                                        moveEaseIn,
                                        moveEaseIn->reverse(),
                                        DelayTime::create(sevenmonkeys::randInt(sevenmonkeys::randInt(8), 16)),
                                        nullptr);

            auto marker = this->getChildByTag(i);

            marker->runAction(RepeatForever::create(seq));
        }
    }


    // Anim marker for Fairy house if new area or if no areas

    sprintf(levelKey, "%d-level0", UserDefault::getInstance()->getIntegerForKey("mode"));

    if (
        UserDefault::getInstance()->getIntegerForKey(levelKey, gUserDefaultIntValue) == gUserDefaultIntValue ||
        isNewArea) {

        auto fairyMarker = this->getChildByTag(kTag::fairyHouse);

        auto move = MoveBy::create(1.5, Vec2(0, 15));
        auto moveEaseIn = EaseBounceIn::create(move->clone());

        auto seq = Sequence::create(delay, moveEaseIn, moveEaseIn->reverse(), DelayTime::create(4.f), nullptr);

        fairyMarker->runAction(RepeatForever::create(seq));
    }
}

void MapLayer::menuExitMapCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playButtonGoSound();

    auto button = (MenuItemSprite*)pSender;

    auto scaleBy = ScaleBy::create(.1f, .95f);

    auto replaceScene = CallFunc::create([&]() {
        auto scene = MainLayer::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(.9f, scene, Color3B::BLACK));
    });

    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), replaceScene, nullptr);

    button->runAction(seq);

//    this->schedule([&](float dt){
//        auto scene = MainLayer::createScene();
//        Director::getInstance()->replaceScene(TransitionFade::create(.9f, scene, Color3B::BLACK));
//    }, 0.f, 0, .4f, "schedulerKey");
}

void MapLayer::onEnter()
{
    Layer::onEnter();
    addEvents();

    Game::instance().getSoundManager().playMapMusic();
}

void MapLayer::onExit()
{
    Layer::onExit();
    removeEvents();
}

bool MapLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    return true;
}

void MapLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("// MapLayer::onTouchEnded...");

    Node *target = event->getCurrentTarget();
    Point touchPosition = target->convertTouchToNodeSpace(touch);

    Vector<Node *> children = this->getChildren();

    for (auto& child : children) {
        if (child->getLocalZOrder() == kZOrder::marker &&
            child->getBoundingBox().containsPoint(touchPosition)) {

            int tag = child->getTag();

            if (tag == kTag::fairyHouse) {

                Game::instance().getSoundManager().playFairyHouseMarkerSound();

                auto scene = FairyHouseLayer::createScene();
                Director::getInstance()->replaceScene(TransitionFade::create(.9f, scene, Color3B::BLACK));

            } else {

                Game::instance().getSoundManager().stopMusic();

                Game::instance().getSoundManager().playMapMarkerSound();

                Game::instance().setLevel(tag);

                UserDefault::getInstance()->setIntegerForKey("currentLevel", tag);

                auto builder = new PuzzleBuilder("data/puzzles/" + gPuzzles[tag] + ".json");

                Reader reader;

                reader.setBuilder(builder);
                reader.create(tag);

                auto scene = builder->getPuzzleScene();

                if (scene) {
                    scene->pushScene();

                    delete builder;
                    builder = nullptr;
                }
            }
        }
    }
}

void MapLayer::addEvents()
{
    mvpEventTouch = EventListenerTouchOneByOne::create();

    mvpEventTouch->setSwallowTouches(true);

    mvpEventTouch->onTouchBegan = CC_CALLBACK_2(MapLayer::onTouchBegan, this);
    mvpEventTouch->onTouchEnded = CC_CALLBACK_2(MapLayer::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mvpEventTouch, this);
}

void MapLayer::removeEvents()
{
    _eventDispatcher->removeEventListener(mvpEventTouch);
}
