//
//  GamePlayingLayer.h
//  EmojiCrush
//
//  Created by Nirvana on 13-11-30.
//
//

#ifndef __EmojiCrush__GamePlayingLayer__
#define __EmojiCrush__GamePlayingLayer__

#include <iostream>
#include "cocos2d.h"
#include "EmojiSprite.h"

using namespace cocos2d;

#define BLOCKS_IN_ROW 8
#define BLOCKS_IN_COLUMN 8

class GamePlayingLayer: public CCLayer
{
public:
    GamePlayingLayer();
    ~GamePlayingLayer();
    
    bool initTheGame();
    void resetMatchMarkArray();
    CCPoint getBlock_ij_AnchorPosition(int i,int j);
    
protected:
private:
    EmojiSprite* m_EmojiBlocks[BLOCKS_IN_ROW][BLOCKS_IN_COLUMN];
    bool m_matchMark[BLOCKS_IN_ROW][BLOCKS_IN_COLUMN];
    float m_fScale;
    float m_fCenter_X;
    float m_fCenter_Y;
};

#endif /* defined(__EmojiCrush__GamePlayingLayer__) */
