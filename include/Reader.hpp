//
//  Reader.hpp
//  SevenMonkeys
//

#ifndef Reader_hpp
#define Reader_hpp

#include "SevenMonkeys.hpp"

#include "Builder.hpp"

// The Reader encapsulates the parsing of the common input
class Reader
{
public:

    void setBuilder(Builder *b)
    {
        mvpBuilder = b;
    }

    void create(const short puzzle)
    {
        mvpBuilder->addBackground();

        mvpBuilder->addPuzzle(puzzle);

        mvpBuilder->addFairy();

        mvpBuilder->addHUD();

        mvpBuilder->addCountDown();
    }

private:

    Builder *mvpBuilder;
};

#endif /* Reader_hpp */
