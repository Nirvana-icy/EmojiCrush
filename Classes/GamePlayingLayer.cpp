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
}

bool GamePlayingLayer::initTheGame()
{
    bool bRet = true;
    float f_Scale = (designResolutionSize.width/RESOURCE_IMG_WIDTH)*16; //性能优化 提取公因子 避免循环中重复计算 16*f_Scale + 32*f_Scale*j
    int offset_X = (CCEGLView::sharedOpenGLView()->getFrameSize().width - 32*BLOCKS_IN_COLUMN)*0.25;
    int offset_Y = (CCEGLView::sharedOpenGLView()->getFrameSize().height- 32*BLOCKS_IN_ROW)*0.25;

    //在每一个block 填充随机生成的Emoji
    for (int i = 0; i < BLOCKS_IN_ROW; i++) {
        for (int j = 0; j < BLOCKS_IN_COLUMN; j++) {
            m_EmojiBlocks[i][j] = EmojiSprite::createEmojiWithRandom();
            //设置每个block Emoji 的位置
            //16*f_Scale == 移动Anchor Point到原点/32*i*f_Scale == 两个Emoji Anchor Point间距为Sprite的宽度
            m_EmojiBlocks[i][j]->getEmojiSprite()->setPosition(ccp(f_Scale*(1 + 2*j) + offset_X, f_Scale*(1 + 2*i) + offset_Y));
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
