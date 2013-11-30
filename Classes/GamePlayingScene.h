//
//  GamePlayingScene.h
//  EmojiCrush
//
//  Created by Nirvana on 13-11-25.
//
//

#ifndef __EmojiCrush__GamePlayingScene__
#define __EmojiCrush__GamePlayingScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

typedef enum {
    zOrder_BackgroundLayer = 0,
    zOrder_GamingLayer,
    zOrder_GameDashBoardLayer,
    zOrder_Max,
}GamingScene_zOrder;

class GamePlayingScene : public cocos2d::CCScene
{
public:
    GamePlayingScene();
    virtual ~GamePlayingScene();
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
    
};

#endif /* defined(__EmojiCrush__GamePlayingScene__) */
