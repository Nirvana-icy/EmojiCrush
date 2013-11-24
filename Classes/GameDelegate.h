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
public:
    
    GameDelegate();
    ~GameDelegate();
    
    void                    startGame();
    void                    switchToMainMenuScene();
    void                    returnToMainMenu();
    void                    returnToGame();
    void                    showMainMenu();
    
    static GameDelegate*    sharedGameDelegate();
    
private:
    static GameDelegate*    s_SharedGameDelegate;
    void                    init();
};

#endif /* defined(__EmojiCrush__GameDelegate__) */
