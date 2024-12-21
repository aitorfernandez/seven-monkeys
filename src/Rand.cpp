//
//  Rand.cpp
//  SevenMonkeys
//

#include "Rand.hpp"

NS_SM_BEGIN

std::random_device rd;
std::mt19937 Rand::svRnd(rd());

std::uniform_int_distribution<int> Rand::svIntDist;
std::uniform_real_distribution<float> Rand::svRealDist;

bool Rand::randBool()
{
    // random number into binary
    return svRnd() & 1;
}

int32_t Rand::randInt()
{
    return svIntDist(svRnd);
}

int32_t Rand::randInt(int32_t v)
{
    if (v < 1) {
        return 0;
    } else {
        return svRnd() % v;
    }
}

int32_t Rand::randInt(int32_t a, int32_t b)
{
    return randInt(b - a) + a;
}

// Random float in the range 0.0f at 1.0f
float Rand::randFloat()
{
    return svRealDist(svRnd);
}

void Rand::shuffle(std::vector<int>& v)
{
    // http://en.cppreference.com/w/cpp/algorithm/random_shuffle
    std::mt19937 g(rd());

    std::shuffle(v.begin(), v.end(), g);
}

NS_SM_END
