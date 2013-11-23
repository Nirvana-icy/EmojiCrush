//
//  GameDelegate.cpp
//  EmojiCrush
//
//  Created by Nirvana on 13-11-21.
//
//

#include "GameDelegate.h"
#include "MainMenuScene.h"

GameDelegate* GameDelegate::s_SharedGameDelegate = NULL;

GameDelegate::GameDelegate()
{
    
}

GameDelegate::~GameDelegate()
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
//    MainScene* scene = new MainScene();
//    scene->init();
//    
//    CCDirector::sharedDirector()->replaceScene( CCTransitionFadeTR::create(0.8f, scene) );
//    scene->release();
}

void GameDelegate::openMainMenu()
{
    MainMenuScene *p_MainMenuScene = new MainMenuScene();
    p_MainMenuScene->init();
    
    CCDirector::sharedDirector()->runWithScene(p_MainMenuScene);
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
