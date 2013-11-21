//
//  GameController.h
//  EmojiCrush
//
//  Created by Nirvana on 13-11-21.
//
//

#ifndef __EmojiCrush__GameController__
#define __EmojiCrush__GameController__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class GameController : public CCLayer
{
public:
    GameController();
    ~GameController();
    
    virtual bool init();
    virtual void showMainMenu();
    
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);

    
private:
    CCPoint m_tBeginPos;
    CCMenu* m_pItemMenu;
};

#endif /* defined(__EmojiCrush__GameController__) */





