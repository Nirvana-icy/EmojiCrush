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
#include "AppMacros.h"

using namespace cocos2d;

class GamePlayingLayer: public CCLayer
{
public:
    GamePlayingLayer();
    ~GamePlayingLayer();
    bool init();
    //Game Logic Method
    bool initTheGame();
    bool checkMatch(int i, int j);
    //Utility Method
    void resetMatchMarkArray();
    CCPoint getBlock_ij_AnchorPosition(int i,int j);
    //Touch Event Processing Method
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    //Scheduler Update Method
    void clearMatchsEmoji();
protected:
private:
    float m_fEmojiWidth; //适配不同屏幕分辨率后Emoji的宽度
    //所有Emoji Blocks的中心
    float m_fEmojiBlockCenter_X;
    float m_fEmojiBlockCenter_Y;
    //Emoji Block Array & matchMark Array
    EmojiSprite* m_EmojiBlocks[BLOCKS_IN_COLUMN][BLOCKS_IN_ROW];
    bool m_matchMark[BLOCKS_IN_COLUMN][BLOCKS_IN_ROW];
    int m_beginBlockI;
    int m_beginBlockJ;
};

#endif /* defined(__EmojiCrush__GamePlayingLayer__) */
