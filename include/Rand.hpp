//
//  Rand.hpp
//  SevenMonkeys
//

#ifndef Rand_hpp
#define Rand_hpp

#include "SevenMonkeys.hpp"

NS_SM_BEGIN

class Rand
{
public:

    // Rand();
    // ~Rand() = default;

    static bool randBool();

    static int32_t randInt();
    static int32_t randInt(int32_t v);
    static int32_t randInt(int32_t a, int32_t b);

    static float randFloat();

    static void shuffle(std::vector<int>& v);

private:

    static std::mt19937 svRnd;

    static std::uniform_int_distribution<int> svIntDist;
    static std::uniform_real_distribution<float> svRealDist;
};


// Rand shortcuts

inline bool randBool() {
    return Rand::randBool();
}

inline int32_t randInt()
{
    return Rand::randInt();
}

inline int32_t randInt(int32_t v)
{
    return Rand::randInt(v);
}

inline int32_t randInt(int32_t a, int32_t b)
{
    return Rand::randInt(a, b);
}

inline float randFloat()
{
    return Rand::randFloat();
}

NS_SM_END

#endif /* Rand_hpp */
