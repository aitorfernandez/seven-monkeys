//
//  PuzzleScene.cpp
//  SevenMonkeys
//

#include "PuzzleScene.hpp"

USING_NS_CC;

PuzzleScene::PuzzleScene()
{
    CCLOG("// PuzzleScene %x Constructor", (int)(long)this);
}

PuzzleScene::~PuzzleScene()
{
    CCLOG("// PuzzleScene %x Destructor", (int)(long)this);
}

bool PuzzleScene::init()
{
    if (!Scene::init()) {
        return false;
    }

    auto eventCustom = EventListenerCustom::create(ON_EXIT_PUZZLE, [=](EventCustom* event) {
        auto scene = MapLayer::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create(.9f, scene, Color3B::BLACK));
    });

    _eventDispatcher->addEventListenerWithFixedPriority(eventCustom, 1);

    return true;
}

void PuzzleScene::pushScene()
{
    Director::getInstance()->replaceScene(TransitionFade::create(.9f, this, Color3B::BLACK));
}

void PuzzleScene::addLayer(cocos2d::Layer *layer)
{
    this->addChild(layer);
}
