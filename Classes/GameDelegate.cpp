//
//  GameDelegate.cpp
//  EmojiCrush
//
//  Created by Nirvana on 13-11-21.
//
//

#include "GameDelegate.h"
#include "MainMenuScene.h"
#include "LoadingScene.h"
#include "GamePlayingScene.h"

GameDelegate* GameDelegate::s_SharedGameDelegate = NULL;

GameDelegate::GameDelegate()
{
    
}

GameDelegate* GameDelegate::sharedGameDelegate()
{
    if ( !s_SharedGameDelegate )
    {
        s_SharedGameDelegate = new GameDelegate();
        s_SharedGameDelegate->init();
    }
    
    return s_SharedGameDelegate;
}

void GameDelegate::init()
{
    
}

void GameDelegate::startGame()
{
    GamePlayingScene *pGamePlayignScene = new GamePlayingScene();
    pGamePlayignScene->autorelease();
    pGamePlayignScene->init();
    
    CCDirector::sharedDirector()->replaceScene( CCTransitionProgressRadialCW::create(0.8f, pGamePlayignScene) );
}

void GameDelegate::showMainMenu()
{
    LoadingScene* pLoadingScene = new LoadingScene();
    pLoadingScene->autorelease();
    if(!pLoadingScene->initWithTargetScene(TargetSceneMainMenu))
        CCLOG("Init LoadingScene(from loadingScene to MainMenu Scene) failed");
    //run the loadingScene
    CCDirector::sharedDirector()->runWithScene(pLoadingScene);
    //Set one schedule to run the update function which will set up the next scene
    CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(LoadingScene::update),pLoadingScene,1,false);
}

void GameDelegate::switchFromLoadingSceneToMainMenuScene()
{
    
    MainMenuScene *p_MainMenuScene = new MainMenuScene();
    p_MainMenuScene->init();
    
    CCDirector::sharedDirector()->replaceScene(p_MainMenuScene);
    p_MainMenuScene->release();
}

void GameDelegate::returnToMainMenu()
{
//    MainMenuScene* mmscene = new MainMenuScene();
//    mmscene->init(true);
//    
//    CCDirector::sharedDirector()->replaceScene(CCTransitionFadeBL::create(0.8f, mmscene));
//    mmscene->release();
}

void GameDelegate::returnToGame()
{
//    CCDirector::sharedDirector()->popScene();
}

GameDelegate::~GameDelegate()
{
    
}