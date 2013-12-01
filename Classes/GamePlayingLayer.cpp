//
//  GamePlayingLayer.cpp
//  EmojiCrush
//
//  Created by Nirvana on 13-11-30.
//
//

#include "GamePlayingLayer.h"
#include "AppMacros.h"

GamePlayingLayer::GamePlayingLayer()
{
    //Loading the Texture Packer image file
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Emoji_Image.plist");
    //成员变量赋值
    m_fCenter_X = CCDirector::sharedDirector()->getWinSize().width*0.5;
    m_fCenter_Y = CCDirector::sharedDirector()->getWinSize().height*0.45;
    m_fScale = designResolutionSize.width/RESOURCE_IMG_WIDTH;
}

CCPoint GamePlayingLayer::getBlock_ij_AnchorPosition(int i, int j)
{
    return CCPoint(m_fCenter_X + (j-3.5)*32*m_fScale, m_fCenter_Y + (i-3.5)*32*m_fScale);
}

bool GamePlayingLayer::initTheGame()
{
    bool bRet = true;
    //在每一个block 填充随机生成的Emoji
    for (int i = 0; i < BLOCKS_IN_ROW; i++) {
        for (int j = 0; j < BLOCKS_IN_COLUMN; j++) {
            m_EmojiBlocks[i][j] = EmojiSprite::createEmojiWithRandom();
            //设置每个block Emoji 的位置
            m_EmojiBlocks[i][j]->getEmojiSprite()->setPosition(getBlock_ij_AnchorPosition(i, j));
            //添加每一个 Emoji 到GamePlayingLayer
            addChild(m_EmojiBlocks[i][j]->getEmojiSprite());
        }
    }
    return bRet;
}

void GamePlayingLayer::resetMatchMarkArray()
{
    for (int i = 0; i < BLOCKS_IN_ROW; i++) {
        for (int j = 0; j < BLOCKS_IN_COLUMN; j++) {
            m_matchMark[i][j] = false;
        }
    }
}

GamePlayingLayer::~GamePlayingLayer()
{
    
}
