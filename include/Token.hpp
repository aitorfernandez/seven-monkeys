//
//  Token.hpp
//  SevenMonkeys
//

#ifndef Token_hpp
#define Token_hpp

#include "SevenMonkeys.hpp"

class Token
{
public:

    Token();
    virtual ~Token();

    void cleanUp();

    CC_SYNTHESIZE_BOOL(mtCorrect, Correct);
    CC_SYNTHESIZE_BOOL(mtClicked, Clicked);

    CC_SYNTHESIZE(cocos2d::Vec2, mtPosition, Position);
};

#endif /* Token_hpp */
