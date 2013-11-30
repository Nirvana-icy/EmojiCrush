//
//  GamePlayingScene.cpp
//  EmojiCrush
//
//  Created by Nirvana on 13-11-25.
//
//
#include "GamePlayingScene.h"
#include "SimpleAudioEngine.h"

#include "EmojiSpirit.h"

using namespace CocosDenshion;

GamePlayingScene::GamePlayingScene()
{
    
}

void GamePlayingScene::onEnter()
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("Gaming_BGM.mp3", true);
}

bool GamePlayingScene::init()
{
    if (CCScene::init()) {
        CCLayer *pBackgroundLayer = CCLayer::create();
        //Load the Background Img and add it to the layer
        CCSprite    *pBackgroundImg = CCSprite::create();
        pBackgroundImg->initWithFile("Gaming_Background.png");
        pBackgroundImg->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
        pBackgroundLayer->addChild(pBackgroundImg);
        //Add Background Layer to the scene
        addChild(pBackgroundLayer, zOrder_BackgroundLayer);
        //init the Background Music
        SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("Gaming_BGM.mp3");
        SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.3);
        return true;
    }
    return false;
}

void GamePlayingScene::onExit()
{
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic(true);
}

GamePlayingScene::~GamePlayingScene()
{
    
}
