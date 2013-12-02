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
    Sprite_Santa, // = 6
    Sprite_Gift,
    Sprite_Xmas_Tree,
    //Special Sprite Tusiji whose image if from seperate png file
    Sprite_Tusiji,
    invalid_Type, // = 10
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
    
    CCSprite *m_pEmojiSprite;
    int m_slideDownCounter;
    EmojiType m_EmojiType;
    
protected:
private:
};

#endif /* defined(__EmojiCrush__EmojiSprite__) */