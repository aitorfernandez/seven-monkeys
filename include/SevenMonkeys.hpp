//
//  SevenMonkeys.hpp
//  SevenMonkeys
//

#ifndef SevenMonkeys_hpp
#define SevenMonkeys_hpp

// Cocos2dx
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

#include "external/json/document.h"
#include "external/json/rapidjson.h"

// C++ Standard Library
#include <array>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include <random>
#include <stdio.h>
#include <string>
#include <vector>

// Seven Monkeys settings, utils...
#include "Macros.hpp"
#include "Constants.hpp"
#include "Events.hpp"
#include "Util.hpp"

// SEVEN_MONKEYS / 1000     Major
// SEVEN_MONKEYS / 100 % 10 Minor
// SEVEN_MONKEYS % 10       Micro

#define SEVEN_MONKEYS     501
#define SEVEN_MONKEYS_STR "0.5.1dev"

#endif /* SevenMonkeys_hpp */
