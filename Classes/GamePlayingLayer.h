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
    
protected:
private:
    EmojiSprite* m_EmojiBlocks[BLOCKS_IN_ROW][BLOCKS_IN_COLUMN] = {NULL};
    bool m_matchMark[BLOCKS_IN_ROW][BLOCKS_IN_COLUMN] = {false};
};

#endif /* defined(__EmojiCrush__GamePlayingLayer__) */
