//
//  Builder.hpp
//  SevenMonkeys
//

#ifndef Builder_hpp
#define Builder_hpp

#include "SevenMonkeys.hpp"

#include "PuzzleScene.hpp"

// The Builder hierarchy makes possible the polymorphic creation of many peculiar representations or targets
class Builder
{
public:

    Builder()
    {
        CCLOG("// Builder %x Constructor", (int)(long)this);

        mtpPuzzleScene = PuzzleScene::create();
    }

    virtual ~Builder()
    {
        CCLOG("// Builder %x Destructor", (int)(long)this);
    }

    // Pure virtual methods "if you inherit from me you HAVE TO implement those by yourself"

    virtual void addBackground() = 0;

    virtual void addPuzzle(const short puzzle) = 0;

    virtual void addFairy() = 0;

    virtual void addHUD() = 0;

    virtual void addCountDown() = 0;

    PuzzleScene *getPuzzleScene()
    {
        return mtpPuzzleScene;
    }

protected:

    PuzzleScene *mtpPuzzleScene;
};

#endif /* Builder_hpp */
