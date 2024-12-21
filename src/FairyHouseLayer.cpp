//
//  FairyHouseLayer.cpp
//  SevenMonkeys
//

#include "FairyHouseLayer.hpp"

USING_NS_CC;

Scene* FairyHouseLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = FairyHouseLayer::create();

    scene->addChild(layer);

    return scene;
}

FairyHouseLayer::FairyHouseLayer()
{
    CCLOG("// FairyHouseLayer %x Constructor", (int)(long)this);

    std::string fullPath = FileUtils::getInstance()->fullPathForFilename("data/FairyHouseLayer.json");
    std::string json = FileUtils::getInstance()->getStringFromFile(fullPath);

    mvFairyHouseDocument.Parse<rapidjson::ParseFlag::kParseDefaultFlags>(json.c_str());
}

FairyHouseLayer::~FairyHouseLayer()
{
    CCLOG("// FairyHouseLayer %x Destructor", (int)(long)this);

    mvMessages.clear();
    mvMessages.shrink_to_fit();
}

bool FairyHouseLayer::init()
{
    if (!Layer::init()) {
        return false;
    }

    mvCurrentMessage = 0;

    initBackground();

    initTutorials();

    initListView();

    initButtons();

    // Activate level 0 if not level 0

    char levelKey[20];

    sprintf(levelKey, "%d-level0", UserDefault::getInstance()->getIntegerForKey("mode"));

    if (UserDefault::getInstance()->getIntegerForKey(levelKey, gUserDefaultIntValue) == gUserDefaultIntValue) {

        UserDefault::getInstance()->setIntegerForKey(levelKey, 1);

        // UserDefault::getInstance()->flush();
    }

    return true;
}

void FairyHouseLayer::initBackground()
{
    auto background = Sprite::createWithSpriteFrameName("FairyHouseLayer.png");
    background->setNormalizedPosition(Vec2(.5f, .5f));

    this->addChild(background);
}

void FairyHouseLayer::initTutorials()
{
    std::string fullPath;
    std::string json;

    rapidjson::Document document;

    const rapidjson::Value& pictures = mvFairyHouseDocument["pictures"];

    for (short i = 0; i < pictures.Size(); ++i) {
        char levelKey[20];

        sprintf(levelKey, "%d-level%d", UserDefault::getInstance()->getIntegerForKey("mode"), i);

        auto pictureFrameName = "Picture" + gPuzzles[i] + ".png";
        auto picture = Sprite::createWithSpriteFrameName(pictureFrameName);

        picture->setNormalizedPosition(Vec2(
                                            pictures[i][0].GetDouble(),
                                            pictures[i][1].GetDouble()));

        int level = UserDefault::getInstance()->getIntegerForKey(levelKey, gUserDefaultIntValue);

        if (level == gUserDefaultIntValue) {
            picture->setColor(Color3B::ORANGE);
            picture->setOpacity(HALF_OPACITY);
        }

        this->addChild(picture, kZOrder::picture, i);
    }

    int pictureTutorial = UserDefault::getInstance()->getIntegerForKey("pictureTutorial", gUserDefaultIntValue);

    if (pictureTutorial == gUserDefaultIntValue) {
        fullPath = FileUtils::getInstance()->fullPathForFilename("data/tutorials/welcome.json");
    }
    else
        fullPath = FileUtils::getInstance()->fullPathForFilename("data/tutorials/" + gPuzzles[pictureTutorial] + ".json");


    json = FileUtils::getInstance()->getStringFromFile(fullPath);

    document.Parse<rapidjson::ParseFlag::kParseDefaultFlags>(json.c_str());

    const rapidjson::Value& messages = document["messages"];

    for (rapidjson::SizeType i = 0; i < messages.Size(); i++) {
        mvMessages.push_back(messages[i].GetString());
    }
}

void FairyHouseLayer::initListView()
{
    auto listView = cocos2d::ui::ListView::create();

    this->addChild(listView, kZOrder::messages, kTag::listView);
}

void FairyHouseLayer::initButtons()
{
    auto buttonBack = MenuItemSprite::create(
                                             Sprite::createWithSpriteFrameName("ButtonBack.png"),
                                             nullptr,
                                             Sprite::createWithSpriteFrameName("ButtonBack.png"),
                                             CC_CALLBACK_1(FairyHouseLayer::menuGoBackCallback, this));

    buttonBack->setNormalizedPosition(Vec2(.1f, .9f));
    buttonBack->setRotation(-3.5f);

    mvpButtonLeft = MenuItemSprite::create(
                                           Sprite::createWithSpriteFrameName("NavPrev.png"),
                                           nullptr,
                                           Sprite::createWithSpriteFrameName("NavPrev.png"),
                                           CC_CALLBACK_1(FairyHouseLayer::menuLeftCallback, this));

    mvpButtonLeft->setNormalizedPosition(Vec2(.47f, .075f));

    mvpButtonRight = MenuItemSprite::create(
                                            Sprite::createWithSpriteFrameName("NavNext.png"),
                                            nullptr,
                                            Sprite::createWithSpriteFrameName("NavNext.png"),
                                            CC_CALLBACK_1(FairyHouseLayer::menuRightCallback, this));

    mvpButtonRight->setNormalizedPosition(Vec2(.53f, .075f));

    auto menu = Menu::create(buttonBack, mvpButtonLeft, mvpButtonRight, nullptr);

    menu->setPosition(Vec2::ZERO);

    this->addChild(menu, kZOrder::menu);
}

void FairyHouseLayer::onEnter()
{
    Layer::onEnter();
    addEvents();

    setMessage();

    if (mvCurrentMessage == 0) {
        mvpButtonLeft->setOpacity(HALF_OPACITY);
        mvpButtonLeft->setEnabled(false);
    }

    int pictureTutorial = UserDefault::getInstance()->getIntegerForKey("pictureTutorial", gUserDefaultIntValue);

    if (pictureTutorial == gUserDefaultIntValue) {
        Game::instance().getSoundManager().playFairyHouseMusic();
    }
}

void FairyHouseLayer::onExit()
{
    Layer::onExit();
    removeEvents();
}

void FairyHouseLayer::addEvents()
{
    mvpEventTouch = EventListenerTouchOneByOne::create();

    mvpEventTouch->setSwallowTouches(true);

    mvpEventTouch->onTouchBegan = CC_CALLBACK_2(FairyHouseLayer::onTouchBegan, this);
    mvpEventTouch->onTouchEnded = CC_CALLBACK_2(FairyHouseLayer::onTouchEnded, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(mvpEventTouch, this);
}

void FairyHouseLayer::removeEvents()
{
    _eventDispatcher->removeEventListener(mvpEventTouch);
}

bool FairyHouseLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    return true;
}

void FairyHouseLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
    CCLOG("// FairyHouseLayer::onTouchEnded...");

    Node *target = event->getCurrentTarget();
    Point touchPosition = target->convertTouchToNodeSpace(touch);

    Vector<Node *> children = this->getChildren();

    for (auto& child : children) {
        if (
            child->getLocalZOrder() == kZOrder::picture &&
            child->getBoundingBox().containsPoint(touchPosition) &&
            child->getOpacity() != HALF_OPACITY) {

            int tag = child->getTag();

            // Avoid reload the same tutorial
            if (tag == UserDefault::getInstance()->getIntegerForKey("pictureTutorial", gUserDefaultIntValue)) {
                break;
            }

            UserDefault::getInstance()->setIntegerForKey("pictureTutorial", tag);
            // UserDefault::getInstance()->flush();

            Game::instance().getSoundManager().playFairyHousePictureSound();

            // Reload scene with the picture tutorial

            auto scaleBy = ScaleBy::create(.1f, .95f);

            auto replaceScene = CallFunc::create([&]() {
                auto scene = FairyHouseLayer::createScene();
                Director::getInstance()->replaceScene(scene);
            });

            auto seq = Sequence::create(scaleBy, scaleBy->reverse(), replaceScene, nullptr);

            child->runAction(seq);

            break;
        }
    }
}

void FairyHouseLayer::menuGoBackCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playButtonGoSound();

    UserDefault::getInstance()->deleteValueForKey("pictureTutorial");

    auto button = (MenuItemSprite*)pSender;

    auto scaleBy = ScaleBy::create(.1f, .95f);

    auto replaceScene = CallFunc::create([&]() {
        auto scene = MapLayer::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(.9f, scene, Color3B::BLACK));
    });

    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), replaceScene, nullptr);

    button->runAction(seq);
}

void FairyHouseLayer::menuLeftCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playNavPrevSound();

    auto button = (MenuItemSprite*)pSender;

    auto scaleBy = ScaleBy::create(.1f, .95f);

    auto setButtonValues = CallFunc::create([&]() {
        enabledButtons();

        mvCurrentMessage--;

        if (mvCurrentMessage <= 0) {
            mvCurrentMessage = 0;

            mvpButtonLeft->setOpacity(HALF_OPACITY);
            mvpButtonLeft->setEnabled(false);
        }
        
        setMessage();
    });

    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), setButtonValues, nullptr);

    button->runAction(seq);
}

void FairyHouseLayer::menuRightCallback(cocos2d::Ref* pSender)
{
    Game::instance().getSoundManager().playNavNextSound();
    
    auto button = (MenuItemSprite*)pSender;

    auto scaleBy = ScaleBy::create(.1f, .95f);

    auto setButtonValues = CallFunc::create([&]() {
        enabledButtons();

        mvCurrentMessage++;

        if (mvCurrentMessage >= mvMessages.size() - 1) {
            mvCurrentMessage = (int)mvMessages.size() - 1;

            mvpButtonRight->setOpacity(HALF_OPACITY);
            mvpButtonRight->setEnabled(false);
        }
        
        setMessage();
    });

    auto seq = Sequence::create(scaleBy, scaleBy->reverse(), setButtonValues, nullptr);

    button->runAction(seq);
}

void FairyHouseLayer::enabledButtons()
{
    mvpButtonLeft->setOpacity(FULL_OPACITY);
    mvpButtonRight->setOpacity(FULL_OPACITY);

    mvpButtonLeft->setEnabled(true);
    mvpButtonRight->setEnabled(true);
}

void FairyHouseLayer::setMessage()
{
    this->getChildByTag(kTag::listView)->removeFromParentAndCleanup(true);

    auto visibleSize = Director::getInstance()->getVisibleSize();

    // Create the list view

    auto listView = cocos2d::ui::ListView::create();

    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setTouchEnabled(true);
    listView->setBounceEnabled(true);
    listView->setContentSize(Size(visibleSize.width / 1.4f, visibleSize.height / 3.5f));
    listView->setNormalizedPosition(Vec2(.15f, .085f));
    listView->setScrollBarPositionFromCorner(Vec2(2, 2));

    this->addChild(listView, kZOrder::messages, kTag::listView);

    auto message = cocos2d::ui::Text::create(mvMessages[mvCurrentMessage], "fonts/OpenSans-Semibold.ttf", 10);

    message->setTextAreaSize(Size(listView->getContentSize().width, 0));
    message->setAnchorPoint(Vec2(0, .5f));
    message->setPosition(Vec2(0, 0));
    message->setTextHorizontalAlignment(TextHAlignment::LEFT);

    listView->addChild(message);
}
