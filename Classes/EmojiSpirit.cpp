//
//  EmojiSpirit.cpp
//  EmojiCrush
//
//  Created by Nirvana on 13-11-30.
//
//

#include "EmojiSpirit.h"

EmojiSpirit::EmojiSpirit()
{
    
}

bool EmojiSpirit::initSpiritWithRandom()
{
    bool bRet = false;
    if(CCSprite::init())
    {
        //init the spirit with random
        bRet = true;
    }
    return bRet;
}

bool EmojiSpirit::initSpiritWithType(EmojiType emojiType)
{
    bool bRet = false;
    if(CCSprite::init())
    {
//        /*
//         ~~~~~~~~~~~~~~~~~Temple test code before gaming layer created
//         */
//        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Emoji_Image.plist");
//        /*
//         Test code here
//         */
//        EmojiSpirit *pEmojiSpirit = new EmojiSpirit();
//        pEmojiSpirit->autorelease();
//        pEmojiSpirit->initSpiritWithType(Spirit_Tutu);
//        pBackgroundLayer->addChild(pEmojiSpirit->m_pEmojiSpirit);
//        
        //init the spirit with Spirit Type
        switch (emojiType) {
            //init the basic spirit from texture packer image file
            case Spirit_Tutu:
                m_pEmojiSpirit = CCSprite::createWithSpriteFrameName("Tutu.png");
                break;
            case Spirit_Deyi:
                break;
            case Spirit_What:
                break;
            case Spirit_Zuohengheng:
                break;
            case Spirit_Se:
                break;
            case Spirit_Happy:
                break;
            //init the special spirit from texture packer image file
            case Spirit_Gift:
                break;
            case Spirit_Xmas_Tree:
                break;
            //init the special Tusiji spirit from seperate png file
            case Spirit_Tusiji:
                break;
            default:
                break;
        }
        bRet = true;
    }
    return bRet;
}

EmojiSpirit::~EmojiSpirit()
{
    
}

