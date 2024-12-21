//
//  Events.hpp
//  SevenMonkeys
//

#ifndef Events_hpp
#define Events_hpp

// Puzzle Events flow

//  ^
//  |   4. PlayerSpeed - onExit
//
//  |   3. Puzzle and HUD - Finish
//
//  |   2. CountDown - onExit
//
//  └─  1. Fairy - onExit

#define ON_EXIT_FAIRY      "OnExitFairy"
#define ON_EXIT_COUNT_DOWN "OnExitCountDown"

#define FINISH_HUD "FinishHUD"

#define ON_EXIT_PUZZLE "OnExitPlayerSpeed"

#define RIGHT_ANSWER "RightAnswer"
#define WRONG_ANSWER "WrongAnswer"

#define TOGGLE_PAUSE "TogglePause"

#endif /* Events_hpp */
