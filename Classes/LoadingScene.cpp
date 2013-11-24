//
//  LoadingScene.cpp
//  EmojiCrush
//
//  Created by Nirvana on 13-11-24.
//
//

#include "LoadingScene.h"
#include "GameDelegate.h"

LoadingScene::LoadingScene()
{
}

LoadingScene::~LoadingScene()
{
}

bool LoadingScene::initWithTargetScene(TargetScenes targetScene)
{
    if (CCScene::init()) {
        targetScene_ = targetScene;
        //Makeup the loading scene
        CCLabelTTF *lable = CCLabelTTF::create("Loading...", "fonts/Marker Felt.ttf", 68);
        lable->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
        this->addChild(lable);
        
        return true;
    }
    else
        return false;
}

void LoadingScene::update(CCTime dt)
{
    this->unscheduleAllSelectors();
    
    switch (targetScene_) {
        case TargetSceneMainMenu:
            CCLog("Switch from loading scene to MainMenu Scene");
            GameDelegate::sharedGameDelegate()->switchToMainMenuScene();
            break;
        case TargetSceneStartGame:
            break;
        case TargetSceneGoBackGame:
            break;
        
        default:
            CCLog("Unsupport TargetScene Enum ID:%i", targetScene_);
            break;
    }
}