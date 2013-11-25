//
//  MainMenuScene.h
//  EmojiCrush
//
//  Created by Nirvana on 13-11-23.
//
//

#ifndef __EmojiCrush__MainMenuScene__
#define __EmojiCrush__MainMenuScene__

#include <iostream>
#include "cocos2d.h"
#include "MainMenuView.h"

using namespace cocos2d;

class MainMenuScene : public cocos2d::CCScene
{
public:
    MainMenuScene();
    virtual ~MainMenuScene();
    
    virtual void onEnter();
    virtual void onExitTransitionDidStart();
    bool    init(bool bInitFromGame = false);
    
    void    startGameCallback(CCObject * pSender);

private:
    MainMenuView *pMainMenuView;
};
#endif /* defined(__EmojiCrush__MainMenuScene__) */
