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
    //Loading the Texture Packer image file
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Emoji_Image.plist");
    //成员变量赋值
    m_fEmojiBlockCenter_X = CCDirector::sharedDirector()->getWinSize().width*0.5;
    m_fEmojiBlockCenter_Y = CCDirector::sharedDirector()->getWinSize().height*0.45;
    m_fEmojiWidth = EMOJI_IMAGE_WIDTH*(designResolutionSize.width/RESOURCE_IMG_WIDTH);
    //init m_matchMark[BLOCKS_IN_ROW][BLOCKS_IN_COLUMN] with the value false
    resetMatchMarkArray();
}

GamePlayingLayer::~GamePlayingLayer()
{
    
}

bool GamePlayingLayer::init()
{
    bool bRet = true;
    //Set GamePlayingLayer touchable
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
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
                //设置每个block Emoji 的位置
                m_EmojiBlocks[i][j]->m_pEmojiSprite->setPosition(getBlock_ij_AnchorPosition(i, j));
                //添加每一个 Emoji 到GamePlayingLayer
                addChild(m_EmojiBlocks[i][j]->m_pEmojiSprite);
            }
        }
        //Check Match after random init..
        bool bMatch = false;
        for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
            for (int j = 0; j < BLOCKS_IN_ROW; j++) {
                bMatch = bMatch || checkMatch(i, j);
                if(checkMatch(i, j))
                {
                    CCLog("Match happen in x:%d, y:%d", i,j);
                }
            }
        }
        if (bMatch) {
            //delete the Match Emoji and Generate the new Emoji
        }
        //if the first row contain Santa -> Get the point and move down the Santa
        //Then generate the new Emoji
    }
    else
        bRet = false;
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
    for (int delta = -1; j + delta > 0; delta--) {
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
    for (int delta = -1; i + delta > 0; delta--) {
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
                }
                else
                    break;
            }
            for (int delta = -1; j + delta > 0; --delta) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i][j+delta] = true;
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
                }
                else
                    break;
            }
            for (int delta = -1; j + delta > 0; delta--) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i][j+delta] = true;
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
                }
                else
                    break;
            }
            for (int delta = -1; i + delta > 0; delta--) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i+delta][j] = true;
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
                }
                else
                    break;
            }
            for (int delta = -1; i + delta > 0; delta--) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i+delta][j] = true;
                }
                else
                    break;
            }
        }
    }
    return bRet;
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
    bool bRet = true;
    return bRet;
}

void GamePlayingLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
}

void GamePlayingLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
}

void GamePlayingLayer::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
}


