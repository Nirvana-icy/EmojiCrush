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
    m_slideDownCounter = 0;
    m_EmojiType = invalid_Type;
    m_pEmojiSprite = NULL;
}

EmojiSprite* EmojiSprite::createEmojiWithType(int emojiType)
{
    EmojiSprite *p_EmojiSprite = new EmojiSprite();
    if(p_EmojiSprite && p_EmojiSprite->initSpriteWithType(emojiType)) {
        p_EmojiSprite->autorelease();
        return p_EmojiSprite;
    }
    else {
        CC_SAFE_DELETE(p_EmojiSprite);
        CCLog("EmojiSprite::createEmojiWithType() failed to create new EmojiSprite");
        return NULL;
    }
}

EmojiSprite* EmojiSprite::createEmojiWithRandom()
{
    EmojiSprite *p_EmojiSprite = new EmojiSprite();
    if(p_EmojiSprite && p_EmojiSprite->initSpriteWithRandom()) {
        p_EmojiSprite->autorelease();
        return p_EmojiSprite;
    }
    else {
        CC_SAFE_DELETE(p_EmojiSprite);
        CCLog("EmojiSprite::createEmojiWithRandom() failed to create new EmojiSprite");
        return NULL;
    }
}

bool EmojiSprite::initSpriteWithType(int emojiType)
{
    bool bRet = true;
    if(CCNode::init())
    {
        //init the Sprite with Sprite Type
        switch (emojiType) {
            //init the basic Sprite from texture packer image file
            case Sprite_Tutu:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Tutu.png");
                m_EmojiType = Sprite_Tutu;
                break;
            case Sprite_Deyi:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Deyi.png");
                m_EmojiType = Sprite_Deyi;
                break;
            case Sprite_What:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("What.png");
                m_EmojiType = Sprite_What;
                break;
            case Sprite_Zuohengheng:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Zuohengheng.png");
                m_EmojiType = Sprite_Zuohengheng;
                break;
            case Sprite_Se:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Se.png");
                m_EmojiType = Sprite_Se;
                break;
            case Sprite_Happy:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Happy.png");
                m_EmojiType = Sprite_Happy;
                break;
            //init the special Sprite from texture packer image file
            case Sprite_Santa:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Santa.png");
                m_EmojiType = Sprite_Gift;
                break;
            case Sprite_Gift:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Gift.png");
                m_EmojiType = Sprite_Gift;
                break;
            case Sprite_Xmas_Tree:
                m_pEmojiSprite = CCSprite::createWithSpriteFrameName("Xmas_Tree.png");
                m_EmojiType = Sprite_Xmas_Tree;
                break;
            //init the special Tusiji Sprite from seperate png file
            case Sprite_Tusiji:
                m_pEmojiSprite = CCSprite::create();
                m_pEmojiSprite->initWithFile("Tusiji.png");
                m_EmojiType = Sprite_Tusiji;
                break;
            default:
                CCLog("EmojiSprite::initSpriteWithType initWith one unknow Type:%i", emojiType);
                bRet = false;
                break;
        }
    }
    else {
        bRet = false;
        CCLog("CCNode::init() in initSpriteWithType fail");
    }
    return bRet;
}

bool EmojiSprite::initSpriteWithRandom()
{
    bool bRet = true;
    if(CCNode::init())
    {
        //init the Sprite with random
        float f_Random = CCRANDOM_0_1()*6; // if f_Random == 6 -> init one Santa Emoji
        this->initSpriteWithType((int)f_Random);
    }
    else {
        bRet = false;
        CCLog("CCNode::init() in initSpriteWithRandom fail");
    }
    return bRet;
}

EmojiSprite::~EmojiSprite()
{
    
}

