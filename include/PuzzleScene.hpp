//
//  PuzzleScene.hpp
//  SevenMonkeys
//

#ifndef PuzzleScene_hpp
#define PuzzleScene_hpp

#include "SevenMonkeys.hpp"

#include "MapLayer.hpp"

class PuzzleScene : public cocos2d::Scene
{
public:

    PuzzleScene();
    virtual ~PuzzleScene();

    virtual bool init();

    CREATE_FUNC(PuzzleScene);

    void pushScene();

    void addLayer(cocos2d::Layer *layer);
};

#endif /* PuzzleScene_hpp */
