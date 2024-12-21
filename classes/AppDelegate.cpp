#include "AppDelegate.h"

#include "LoadingLayer.hpp"

USING_NS_CC;

typedef struct resource_t
{
    cocos2d::Size size;
    std::string directory;
} Resource;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);

static Resource smalliPhoneResolution = {
    cocos2d::Size(1136, 640), "Assets/iPhoneHD"
};

static Resource largeiPhoneResolution = {
    cocos2d::Size(1920, 1080), "Assets/iPhoneHDR"
};

/*
    static Resource smalliPadResolution = {
        cocos2d::Size(2048, 1536), "iPadHD"
    };

    static Resource largeiPadResolution = {
        cocos2d::Size(2732, 2048), "iPadHDR"
    };
*/

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red, green, blue, alpha, depth, stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,
// don't modify or remove this function
static int register_all_packages()
{
    // flag for packages manager
    return 0;
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();

    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("SevenMonkeys", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("SevenMonkeys");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
#if COCOS2D_DEBUG
    director->setDisplayStats(true);
#else
    director->setDisplayStats(false);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width,
                                    designResolutionSize.height,
                                    ResolutionPolicy::FIXED_WIDTH);

    auto frameSize = glview->getFrameSize();

    CCLOG("// frameSize %f by %f", frameSize.width, frameSize.height);

    std::vector<std::string> searchPaths;

    // if the frame's width is larger than the width of small size.
    if (frameSize.width > smalliPhoneResolution.size.width)
    {
        CCLOG("// LargeResource scaleFactor %f / %f", largeiPhoneResolution.size.width, designResolutionSize.width);
        searchPaths.push_back(largeiPhoneResolution.directory);

        director->setContentScaleFactor(largeiPhoneResolution.size.width / designResolutionSize.width);

        Game::instance().HDR = true;
    }
    else
    {
        CCLOG("// SmallResource scaleFactor %f / %f", smalliPhoneResolution.size.width, designResolutionSize.width);
        searchPaths.push_back(smalliPhoneResolution.directory);

        director->setContentScaleFactor(smalliPhoneResolution.size.width / designResolutionSize.width);

        Game::instance().HDR = false;
    }

    FileUtils::getInstance()->setSearchPaths(searchPaths);

    register_all_packages();

    // initialize scripting

    // preload sprites

    // services

    // shaders

    // ...

    // ...


    // create a scene. it's an autorelease object
    auto scene = LoadingLayer::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
