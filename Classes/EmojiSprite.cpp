//
//  EmojiSprite.cpp
//  EmojiCrush
//
//  Created by Nirvana on 13-11-30.
//
//

#include "EmojiSprite.h"

EmojiSprite::EmojiSprite()
{
    slideDownCounter = 0;
}

bool EmojiSprite::initSpriteWithType(int emojiType)
{
    bool bRet = true;
    if(CCSprite::init())
    {
        //init the Sprite with Sprite Type
        switch (emojiType) {
            //init the basic Sprite from texture packer image file
            case Sprite_Tutu:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Tutu.png");
                break;
            case Sprite_Deyi:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Deyi.png");
                break;
            case Sprite_What:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("What.png");
                break;
            case Sprite_Zuohengheng:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Zuohengheng.png");
                break;
            case Sprite_Se:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Se.png");
                break;
            case Sprite_Happy:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Happy.png");
                break;
            //init the special Sprite from texture packer image file
            case Sprite_Gift:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Gift.png");
                break;
            case Sprite_Xmas_Tree:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Xmas_Tree.png");
                break;
            //init the special Tusiji Sprite from seperate png file
            case Sprite_Tusiji:
                m_pEmojiSprite = CCSprite::create();
                m_pEmojiSprite->initWithFile("Tusiji.png");
                break;
            default:
                CCLog("EmojiSprite::initSpriteWithType initWith one unknow Type:%i", emojiType);
                bRet = false;
                break;
        }
    }
    else
    {
        bRet = false;
    }
    return bRet;
}

bool EmojiSprite::initSpriteWithRandom()
{
    bool bRet = true;
    if(CCSprite::init())
    {
        //init the Sprite with random
        float f_Random = CCRANDOM_0_1()*6;
        if (6.0f == f_Random) {
            f_Random = 5.0;
        }
        this->initSpriteWithType((int)f_Random);
    }
    else
    {
        bRet = false;
    }
    return bRet;
}

EmojiSprite::~EmojiSprite()
{
    
}

