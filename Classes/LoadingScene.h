//
//  LoadingScene.h
//  EmojiCrush
//
//  Created by Nirvana on 13-11-24.
//
//

#ifndef __EmojiCrush__LoadingScene__
#define __EmojiCrush__LoadingScene__

#include <iostream>
#include "cocos2d.h"

using namespace cocos2d;

typedef enum
{
    TargetSceneINVALID = 0,
    TargetSceneMainMenu,
    TargetSceneStartGame,
    TargetSceneGoBackGame,
    TargetSceneMAX,
} TargetScenes;

class LoadingScene: public CCScene
{
public:
    LoadingScene();
    ~LoadingScene();
    
    bool initWithTargetScene(TargetScenes targetScene);
    virtual void update(CCTime dt);
    
protected:
    
private:
    TargetScenes targetScene_;
};
#endif /* defined(__EmojiCrush__LoadingScene__) */
