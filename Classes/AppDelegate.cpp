#include "AppDelegate.h"
#include "AppMacros.h"
#include "SimpleAudioEngine.h"
#include "SimpleAudioEngine.h"
#include "GameDelegate.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
    //Set the design resolution
    
    pEGLView->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, kResolutionFixedWidth);
    
    pDirector->setContentScaleFactor(RESOURCE_IMG_WIDTH/designResolutionSize.width);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    bool bRet = true;
    // create the Game Controller and put it in the aulto release pool.
//    pGameController = new GameController();
//    pGameController->autorelease();
//    if(!pGameController->init())
//    {
//        bRet = false;
//    }
//    pGameController->showMainMenu();
    GameDelegate::sharedGameDelegate()->showMainMenu();


    return bRet;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

AppDelegate::~AppDelegate()
{
    CocosDenshion::SimpleAudioEngine::sharedEngine()->end();
}
