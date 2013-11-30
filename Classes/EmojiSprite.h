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

class EmojiSprite: public CCSprite
{
public:
    EmojiSprite();
    ~EmojiSprite();
    
    bool initSpriteWithType(int emojiType);
    bool initSpriteWithRandom();
    
    CCSprite *m_pEmojiSprite;
    int slideDownCounter;
    
protected:
private:
};

#endif /* defined(__EmojiCrush__EmojiSprite__) */
