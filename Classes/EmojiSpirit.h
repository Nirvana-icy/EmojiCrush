//
//  EmojiSpirit.h
//  EmojiCrush
//
//  Created by Nirvana on 13-11-30.
//
//

#ifndef __EmojiCrush__EmojiSpirit__
#define __EmojiCrush__EmojiSpirit__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

typedef enum
{
    Spirit_Invalid = 0,
    //Basic Spirit
    Spirit_Tutu,
    Spirit_Deyi,
    Spirit_What,
    Spirit_Zuohengheng,
    Spirit_Se,
    Spirit_Happy,
    //Special Spirit
    Spirit_Gift,
    Spirit_Xmas_Tree,
    Spirit_Santa,
    //Special Spirit Tusiji whose image if from seperate png file
    Spirit_Tusiji,
    Spirit_Max,
} EmojiType;

class EmojiSpirit: public CCSprite
{
public:
    EmojiSpirit();
    ~EmojiSpirit();
    
    bool initSpiritWithRandom();
    bool initSpiritWithType(EmojiType emojiType);
    
    CCSprite *m_pEmojiSpirit;
    int slideDownCounter;

protected:
private:
};

#endif /* defined(__EmojiCrush__EmojiSpirit__) */
