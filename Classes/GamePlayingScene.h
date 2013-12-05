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
#include "GamePlayingLayer.h"

using namespace cocos2d;

class GamePlayingScene : public cocos2d::CCScene
{
public:
    GamePlayingScene();
    virtual ~GamePlayingScene();
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool init();
protected:
private:
    GamePlayingLayer *m_pGamePlayingLayer;
};

#endif /* defined(__EmojiCrush__GamePlayingScene__) */
