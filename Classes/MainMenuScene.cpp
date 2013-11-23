//
//  MainMenuScene.cpp
//  EmojiCrush
//
//  Created by Nirvana on 13-11-23.
//
//

#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "GameDelegate.h"
using namespace CocosDenshion;

MainMenuScene::MainMenuScene()
{
    
}

MainMenuScene::~MainMenuScene()
{
    SimpleAudioEngine::sharedEngine()->end();
}

void MainMenuScene::onEnter()
{
    CCScene::onEnter();
    //Play the Background Music
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("MainMenu_BGM.mp3",true);
}

bool MainMenuScene::init(bool bInitFromGame)
{
    if (CCScene::init()) {
        //Create the MainMenuView and init it
        pMainMenuView = new MainMenuView();
        pMainMenuView->init(bInitFromGame);
        if (bInitFromGame)
        {
//            pMainMenuView->getStartButton()->setTarget(this, menu_selector(MainMenuScene::returnToGameCallback));
        }
        else
        {
            pMainMenuView->getStartButton()->setTarget(this, menu_selector(MainMenuScene::startGameCallback));
        }
        //Add MainMenuView to the Scene
        addChild(pMainMenuView);
        //Make the Reference Conting of pMainMenuView --
        pMainMenuView->release();
        //Preload the Background Music
        SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("MainMenu_BGM.mp3");
        return true;
    }
    return false;
}

void MainMenuScene::startGameCallback(CCObject *pSender)
{
    GameDelegate::sharedGameDelegate()->startGame();
}