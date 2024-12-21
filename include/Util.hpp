//
//  Util.hpp
//  SevenMonkeys
//

#ifndef Util_hpp
#define Util_hpp

NS_SM_BEGIN

namespace util {

    struct Positions
    {
        cocos2d::Vec2 sticker;
        cocos2d::Vec2 btn;
        cocos2d::Vec2 blinds;
        cocos2d::Vec2 stack;
    };

    struct sortDescendingOrder
    {
        template<class T>
        bool operator() (T const &a, T const &b) const {
            return a > b;
        }
    };

} // util

NS_SM_END

#endif /* Util_hpp */
