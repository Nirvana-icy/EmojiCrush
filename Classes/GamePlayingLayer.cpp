//
//  GamePlayingLayer.cpp
//  EmojiCrush
//
//  Created by Nirvana on 13-11-30.
//
//

#include "GamePlayingLayer.h"

GamePlayingLayer::GamePlayingLayer()
{
    //Set GamePlayingLayer touchable
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

GamePlayingLayer::~GamePlayingLayer()
{
    for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
        for (int j = 0; j < BLOCKS_IN_ROW; j++) {
            m_EmojiBlocks[i][j]->release();
        }
    }
}

bool GamePlayingLayer::init()
{
    bool bRet = true;
    //Loading the Texture Packer image file
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Emoji_Image.plist");
    //成员变量赋值
    m_fEmojiBlockCenter_X = CCDirector::sharedDirector()->getWinSize().width*0.5;
    m_fEmojiBlockCenter_Y = CCDirector::sharedDirector()->getWinSize().height*0.45;
    m_fEmojiWidth = EMOJI_IMAGE_WIDTH*(designResolutionSize.width/RESOURCE_IMG_WIDTH);
    m_beginBlockI = BLOCKS_IN_ROW;  //Set default value to this out of array boundry value to indicate invalid
    m_beginBlockJ = BLOCKS_IN_COLUMN;
    
    m_Blocks_0_0 = ccp(m_fEmojiBlockCenter_X - BLOCKS_IN_ROW*m_fEmojiWidth*0.5,m_fEmojiBlockCenter_Y - BLOCKS_IN_COLUMN*m_fEmojiWidth*0.5);
    m_Blocks_1_1 = ccp(m_fEmojiBlockCenter_X + BLOCKS_IN_ROW*m_fEmojiWidth*0.5,m_fEmojiBlockCenter_Y + BLOCKS_IN_COLUMN*m_fEmojiWidth*0.5);
    //init m_matchMark[BLOCKS_IN_ROW][BLOCKS_IN_COLUMN] with the value false
    resetMatchMarkArray();
   // m_EmojiBlocks
    CCLog("resetMatchMarkArray() is called in the GamePlayingLayer::init().");
    return bRet;
}

#pragma Game Logic Method

bool GamePlayingLayer::initTheGame()
{
    bool bRet = true;
    if (init()) {
        //在每一个block 填充随机生成的Emoji
        for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
            for (int j = 0; j < BLOCKS_IN_ROW; j++) {
                m_EmojiBlocks[i][j] = EmojiSprite::createEmojiWithRandom();
                m_EmojiBlocks[i][j]->retain();
                CCAssert(m_EmojiBlocks[i][j], "createEmojiWithRandom should not generate NULL Emoji!");
            }
        }
        //if the first row contain Santa -> Switch the Santa Sprite block with the block which upside Santa
        for (int j = 0; j < BLOCKS_IN_ROW; j++) {
            if (Sprite_Santa == m_EmojiBlocks[0][j]->m_EmojiType) {
                EmojiSprite *temp_pEmojiSprite = m_EmojiBlocks[1][j];
                m_EmojiBlocks[1][j] = m_EmojiBlocks[0][j];
                m_EmojiBlocks[0][j] = temp_pEmojiSprite;
                temp_pEmojiSprite = NULL;
            }
        }
        //Check Match after random init..If match happens => Recreate the emoji till none matchs happen..
        bool bMatch = false;
        do{
            bMatch = false;
            for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
                for (int j = 0; j < BLOCKS_IN_ROW; j++) {
                    //bMatch = bMatch || checkMatch(i, j);
                    if(checkMatch(i, j)){
                        m_EmojiBlocks[i][j]->release();
                        m_EmojiBlocks[i][j] = EmojiSprite::createEmojiWithRandom();
                        m_EmojiBlocks[i][j]->retain();
                        bMatch = true;
                    }
                }
            }
            resetMatchMarkArray();
        }while(bMatch);
        //Till now all the sprites have been generated.Let's set the position of each sprite and add them to the layer
        for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
            for (int j = 0; j< BLOCKS_IN_ROW; j++) {
                //设置每个block Emoji 的位置
                m_EmojiBlocks[i][j]->m_pEmojiSprite->setPosition(getBlock_ij_AnchorPosition(i, j));
                m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccWHITE);
                //添加每一个 Emoji 到GamePlayingLayer
                addChild(m_EmojiBlocks[i][j]->m_pEmojiSprite);
            }
        }
    }
    else {
        bRet = false;
        CCLog("initTheGame() Fail");
    }
    return bRet;
}

bool GamePlayingLayer::checkMatch(int i, int j)
{
    bool bRet = false;
    int matchsInRow = 0;
    int matchsInColumn = 0;
    //Check matchs in row
    for (int delta = 1; j + delta < BLOCKS_IN_ROW; delta++) {
        if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
            matchsInRow++;
        else
            break;
    }
    for (int delta = -1; j + delta >= 0; delta--) {
        if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
            matchsInRow++;
        else
            break;
    }
    //Check matchs in column
    for (int delta = 1; i + delta < BLOCKS_IN_COLUMN; delta++) {
        if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
            matchsInColumn++;
        else
            break;
    }
    for (int delta = -1; i + delta >= 0; delta--) {
        if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
            matchsInColumn++;
        else
            break;
    }
    //Check Match Type
    if (matchsInRow >= 2 || matchsInColumn >= 2) {
        bRet = true;
        //matchs happen in row
        if (matchsInRow - matchsInColumn > 0) {
            //mark match block in row
            for (int delta = 1; j + delta < BLOCKS_IN_ROW; delta++) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i][j+delta] = true;
                    m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
                    m_EmojiBlocks[i][j+delta]->m_pEmojiSprite->setColor(ccYELLOW);
                }
                else
                    break;
            }
            for (int delta = -1; j + delta >= 0; --delta) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i][j+delta] = true;
                    m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
                    m_EmojiBlocks[i][j+delta]->m_pEmojiSprite->setColor(ccYELLOW);
                }
                else
                    break;
            }

        }
        //matchs happen in row and column L or T 5 matchs
        if (matchsInRow - matchsInColumn == 0) {
            //Mark match block in row
            for (int delta = 1; j + delta < BLOCKS_IN_ROW; delta++) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i][j+delta] = true;
                    m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
                    m_EmojiBlocks[i][j+delta]->m_pEmojiSprite->setColor(ccYELLOW);
                }
                else
                    break;
            }
            for (int delta = -1; j + delta >= 0; delta--) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i][j+delta] = true;
                    m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
                    m_EmojiBlocks[i][j+delta]->m_pEmojiSprite->setColor(ccYELLOW);
                }
                else
                    break;
            }
            //Mark match block in coloumn
            for (int delta = 1; i + delta < BLOCKS_IN_COLUMN; delta++) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i+delta][j] = true;
                    m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
                    m_EmojiBlocks[i+delta][j]->m_pEmojiSprite->setColor(ccYELLOW);
                }
                else
                    break;
            }
            for (int delta = -1; i + delta >= 0; delta--) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i+delta][j] = true;
                    m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
                    m_EmojiBlocks[i+delta][j]->m_pEmojiSprite->setColor(ccYELLOW);

                }
                else
                    break;
            }
        }
        //match happen in column
        else
        {
            //Mark match block in coloumn
            for (int delta = 1; i + delta < BLOCKS_IN_COLUMN; delta++) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i+delta][j] = true;
                    m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
                    m_EmojiBlocks[i+delta][j]->m_pEmojiSprite->setColor(ccYELLOW);
                }
                else
                    break;
            }
            for (int delta = -1; i + delta >= 0; delta--) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i+delta][j] = true;
                    m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
                    m_EmojiBlocks[i+delta][j]->m_pEmojiSprite->setColor(ccYELLOW);
                }
                else
                    break;
            }
        }
    }
    return bRet;
}

void GamePlayingLayer::clearMatchsEmoji(){
    this->unscheduleAllSelectors();
    for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
        for (int j = 0; j < BLOCKS_IN_ROW; j++) {
            if(m_matchMark[i][j]) {
                removeChild(m_EmojiBlocks[i][j]);
            }
        }
    } //End of the outside for 
    
    //计算每一个m_EmojiBlocks[i][j]的 slideDownCounter
     for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
        for (int j = 0; j < BLOCKS_IN_ROW; j++) {
            if(!m_matchMark[i][j]) {
                int slideDownCounter = 0;
                for(int p = 0; p < j; p++){
                    if(!m_matchMark[i][p])  slideDownCounter++;
                }
                m_EmojiBlocks[i][j]->m_slideDownCounter = slideDownCounter;
            }
        }
    } //End of the outside for 
    
    //计算 slideDownCounterInColumn 
    int slideDownCounterInColumn[BLOCKS_IN_ROW] = {0};
    int counter = 0;
    for (int j = 0; j < BLOCKS_IN_ROW; j++) {
        for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
            if(m_matchMark[i][j]) counter++;
        }
        slideDownCounterInColumn[j] = counter;
    }
    //依据slideDownCounterInColumn[j]生成新的Emoji
    //更新每一个Emoji的位置
    
    //重置Matchs标志位矩阵
    resetMatchMarkArray();
}

//Utility Method
void GamePlayingLayer::resetMatchMarkArray()
{
    for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
        for (int j = 0; j < BLOCKS_IN_ROW; j++) {
            m_matchMark[i][j] = false;
        }
    }
}

CCPoint GamePlayingLayer::getBlock_ij_AnchorPosition(int i, int j)
{
    float offset = 0;
    if(0 == BLOCKS_IN_ROW%2)
        offset = BLOCKS_IN_ROW*0.5 - 0.5;   //8 Blocks [][][][]|[][][][] = 3.5 10mod2 = 0
    
    else
        offset = BLOCKS_IN_ROW*0.5;   //9 Blocks [][][][]-[][][][] = 4.5
    return CCPoint(m_fEmojiBlockCenter_X + (j-offset)*m_fEmojiWidth, m_fEmojiBlockCenter_Y + (i-offset)*m_fEmojiWidth);
}

//Touch Event Processing Method
bool GamePlayingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //The touch is in the blocks
    if (pTouch->getLocation().x > m_Blocks_0_0.x && pTouch->getLocation().x < m_Blocks_1_1.x && pTouch->getLocation().y > m_Blocks_0_0.y && pTouch->getLocation().y < m_Blocks_1_1.y) {
        //Calculate which block is touched and mark it with yellow background color
        int i = (int)(pTouch->getLocation().y - m_Blocks_0_0.y)/(int)m_fEmojiWidth;
        int j = (int)(pTouch->getLocation().x - m_Blocks_0_0.x)/(int)m_fEmojiWidth;
        m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
        //Mark begin block
        m_beginBlockI = i;
        m_beginBlockJ = j;
        CCLog("m_beginBlockI:%d, m_beginBlockJ:%d", i,j);
    }
    return true;
}

void GamePlayingLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    //The touch is in the blocks
    if (pTouch->getLocation().x > m_Blocks_0_0.x && pTouch->getLocation().x < m_Blocks_1_1.x && pTouch->getLocation().y > m_Blocks_0_0.y && pTouch->getLocation().y < m_Blocks_1_1.y) {
        //Calculate which block is touched and mark it with yellow background color
        int i = (int)(pTouch->getLocation().y - m_Blocks_0_0.y)/(int)m_fEmojiWidth;
        int j = (int)(pTouch->getLocation().x - m_Blocks_0_0.x)/(int)m_fEmojiWidth;
        //Touch End的点在上下左右 四个block
        if (1 == (i-m_beginBlockI)*(i-m_beginBlockI) + (j-m_beginBlockJ)*(j-m_beginBlockJ)){
            EmojiSprite* tempSwitch = m_EmojiBlocks[m_beginBlockI][m_beginBlockJ];
            m_EmojiBlocks[m_beginBlockI][m_beginBlockJ] = m_EmojiBlocks[i][j];
            m_EmojiBlocks[i][j] = tempSwitch;
            tempSwitch = NULL;
            //Match happens
            if(checkMatch(i, j) || checkMatch(m_beginBlockI, m_beginBlockJ))
            {
                for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
                    for (int j = 0; j < BLOCKS_IN_ROW; j++) {
                        //设置每个block Emoji 的位置
                        CCAssert(m_EmojiBlocks[i][j], "m_EmojiBlocks[i][j] != NULL");
                        m_EmojiBlocks[i][j]->m_pEmojiSprite->setPosition(getBlock_ij_AnchorPosition(i, j));
                    }
                }
                //将Matchs的Emoji背景设置为黄色
                for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
                    for (int j = 0; j< BLOCKS_IN_ROW; j++) {
                            if (m_matchMark[i][j]) {
                                CCLog("m_matchMark[%d][%d] is true",i,j);
                                m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
                            }
                        }
                    }
                //1s后消除Matchs的Emoji
                //Set one schedule to run the update function which will set up the next scene
                CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GamePlayingLayer::clearMatchsEmoji),this,1,false);
            }
            else {
                EmojiSprite* tempSpriteSwitchBack = m_EmojiBlocks[m_beginBlockI][m_beginBlockJ];
                CCLog("touchEnd i:%d, touchEnd j:%d", i,j);
                m_EmojiBlocks[m_beginBlockI][m_beginBlockJ] = m_EmojiBlocks[i][j];
                m_EmojiBlocks[i][j] = tempSpriteSwitchBack;
                tempSpriteSwitchBack = NULL;
            }
        }
    }
    //复原Touch began block背景颜色
    m_EmojiBlocks[m_beginBlockI][m_beginBlockJ]->m_pEmojiSprite->setColor(ccWHITE);
}

void GamePlayingLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    //ccTouchEnded(pTouch, pEvent);
}
