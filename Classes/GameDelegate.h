//
//  GameDelegate.h
//  EmojiCrush
//
//  Created by Nirvana on 13-11-21.
//
//

#ifndef __EmojiCrush__GameDelegate__
#define __EmojiCrush__GameDelegate__

#include <iostream>
#include "cocos2d.h"

class GameDelegate
{
private:
    static GameDelegate*    s_SharedGameDelegate;
    void                    init();
public:
    
    GameDelegate();
    ~GameDelegate();
    
    void                    startGame();
    void                    openMainMenu();
    void                    returnToMainMenu();
    void                    returnToGame();
    
    static GameDelegate*    sharedGameDelegate();
};

#endif /* defined(__EmojiCrush__GameDelegate__) */
