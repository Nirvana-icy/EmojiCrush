//
//  GamePlayingScene.cpp
//  EmojiCrush
//
//  Created by Nirvana on 13-11-25.
//
//
#include "GamePlayingScene.h"
#include "SimpleAudioEngine.h"
#include "GamePlayingLayer.h"

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
        //Add Background Layer to the scene with the zOrder zOrder_BackgroundLayer
        addChild(pBackgroundLayer);
        //init the GamePlayingLayer
        m_pGamePlayingLayer = new GamePlayingLayer();
        if (m_pGamePlayingLayer && m_pGamePlayingLayer->initTheGame()) {
            m_pGamePlayingLayer->autorelease();
        }
        addChild(m_pGamePlayingLayer);
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
