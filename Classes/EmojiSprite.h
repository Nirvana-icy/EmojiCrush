//
//  EmojiSprite.h
//  EmojiCrush
//
//  Created by Nirvana on 13-11-30.
//
//

#ifndef __EmojiCrush__EmojiSprite__
#define __EmojiCrush__EmojiSprite__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

typedef enum
{
    //Basic Sprite
    Sprite_Tutu = 0,
    Sprite_Deyi,
    Sprite_What,
    Sprite_Zuohengheng,
    Sprite_Se,
    Sprite_Happy,
    //Special Sprite
    Sprite_Gift,
    Sprite_Xmas_Tree,
    Sprite_Santa0,
    //Special Sprite Tusiji whose image if from seperate png file
    Sprite_Tusiji,
} EmojiType;

class EmojiSprite: public CCNode
{
public:
    EmojiSprite();
    ~EmojiSprite();
    
    static EmojiSprite* createEmojiWithType(int emojiType);
    static EmojiSprite* createEmojiWithRandom();
    
    bool initSpriteWithType(int emojiType);
    bool initSpriteWithRandom();
    
    void setSlideDownConter(int conter);
    int getSlideDownConter();
    CCSprite* getEmojiSprite();
    
protected:
private:
    int m_slideDownCounter;
    CCSprite *m_pEmojiSprite;
};

#endif /* defined(__EmojiCrush__EmojiSprite__) */
