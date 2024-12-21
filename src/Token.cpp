//
//  Token.cpp
//  SevenMonkeys
//

#include "Token.hpp"

Token::Token()
{
    CCLOG("// Token %x Constructor", (int)(long)this);

    setCorrect(false);
    setClicked(false);
}

Token::~Token()
{
    CCLOG("// Token %x Destructor", (int)(long)this);
}

void Token::cleanUp()
{
    setCorrect(false);
    setClicked(false);
}
