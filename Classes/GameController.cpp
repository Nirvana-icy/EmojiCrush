//
//  GameController.cpp
//  EmojiCrush
//
//  Created by Nirvana on 13-11-21.
//
//

#include "GameController.h"
#include "GameDelegate.h"

GameController::GameController()
{
}

GameController::~GameController()
{
}

bool GameController::init()
{
    return CCLayer::init();
}

void GameController::showMainMenu()
{
    setTouchEnabled(true);
    GameDelegate::sharedGameDelegate()->showMainMenu();
}

void GameController::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    m_tBeginPos = touch->getLocation();
}

void GameController::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    /*CCSetIterator it = pTouches->begin();
     CCTouch* touch = (CCTouch*)(*it);
     
     CCPoint touchLocation = touch->getLocation();
     float nMoveY = touchLocation.y - m_tBeginPos.y;
     
     CCPoint curPos  = m_pItemMenu->getPosition();
     CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
     
     if (nextPos.y < 0.0f)
     {
     m_pItemMenu->setPosition(CCPointZero);
     return;
     }
     
     if (nextPos.y > ((TESTS_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
     {
     m_pItemMenu->setPosition(ccp(0, ((TESTS_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
     return;
     }
     
     m_pItemMenu->setPosition(nextPos);
     m_tBeginPos = touchLocation;
     s_tCurPos   = nextPos;*/
}