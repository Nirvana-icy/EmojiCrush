//
//  GamePlayingLayer.cpp
//  EmojiCrush
//
//  Created by Nirvana on 13-11-30.
//
//

#include "GamePlayingLayer.h"

GamePlayingLayer::GamePlayingLayer()
{
    //Set GamePlayingLayer touchable
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

GamePlayingLayer::~GamePlayingLayer()
{
    for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
        for (int j = 0; j < BLOCKS_IN_ROW; j++) {
            m_EmojiBlocks[i][j]->release();
        }
    }
}

bool GamePlayingLayer::init()
{
    bool bRet = true;
    //Loading the Texture Packer image file
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Emoji_Image.plist");
    //成员变量赋值
    m_fEmojiBlockCenter_X = CCDirector::sharedDirector()->getWinSize().width*0.5;
    m_fEmojiBlockCenter_Y = CCDirector::sharedDirector()->getWinSize().height*0.45;
    m_fEmojiWidth = EMOJI_IMAGE_WIDTH*(designResolutionSize.width/RESOURCE_IMG_WIDTH);
    m_beginBlockI = BLOCKS_IN_ROW;  //Set default value to this out of array boundry value to indicate invalid
    m_beginBlockJ = BLOCKS_IN_COLUMN;
    
    m_Blocks_0_0 = ccp(m_fEmojiBlockCenter_X - BLOCKS_IN_ROW*m_fEmojiWidth*0.5,m_fEmojiBlockCenter_Y - BLOCKS_IN_COLUMN*m_fEmojiWidth*0.5);
    m_Blocks_1_1 = ccp(m_fEmojiBlockCenter_X + BLOCKS_IN_ROW*m_fEmojiWidth*0.5,m_fEmojiBlockCenter_Y + BLOCKS_IN_COLUMN*m_fEmojiWidth*0.5);
    //init m_matchMark[BLOCKS_IN_ROW][BLOCKS_IN_COLUMN] with the value false
    resetMatchMarkArray();
   // m_EmojiBlocks
    CCLog("resetMatchMarkArray() is called in the GamePlayingLayer::init().");
    return bRet;
}


#pragma Game Logic Method

bool GamePlayingLayer::initTheGame()
{
    bool bRet = true;
    if (init()) {
        //在每一个block 填充随机生成的Emoji
        for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
            for (int j = 0; j < BLOCKS_IN_ROW; j++) {
                m_EmojiBlocks[i][j] = EmojiSprite::createEmojiWithRandom(Sprite_Tutu, Sprite_Happy);
                m_EmojiBlocks[i][j]->retain();
                m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccWHITE);
                CCAssert(m_EmojiBlocks[i][j], "createEmojiWithRandom should not generate NULL Emoji!");
            }
        }
        //if the first row contain Santa -> Switch the Santa Sprite block with the block which upside Santa
        for (int j = 0; j < BLOCKS_IN_ROW; j++) {
            if (Sprite_Santa == m_EmojiBlocks[0][j]->m_EmojiType) {
                EmojiSprite *temp_pEmojiSprite = m_EmojiBlocks[1][j];
                m_EmojiBlocks[1][j] = m_EmojiBlocks[0][j];
                m_EmojiBlocks[0][j] = temp_pEmojiSprite;
                temp_pEmojiSprite = NULL;
            }
        }
        //Check Match after random init..If match happens => Recreate the emoji till none matchs happen..
        bool bMatch = false;
        do{
            bMatch = false;
            for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
                for (int j = 0; j < BLOCKS_IN_ROW; j++) {
                    //bMatch = bMatch || checkMatch(i, j);
                    if(checkMatch(i, j)){
                        m_EmojiBlocks[i][j]->release();
                        m_EmojiBlocks[i][j] = EmojiSprite::createEmojiWithRandom(Sprite_Tutu, Sprite_Santa);
                        m_EmojiBlocks[i][j]->retain();
                        m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccWHITE);
                        bMatch = true;
                    }
                }
            }
            resetMatchMarkArray();
        }while(bMatch);
        //Till now all the sprites have been generated.Let's set the position of each sprite and add them to the layer
        for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
            for (int j = 0; j< BLOCKS_IN_ROW; j++) {
                //设置每个block Emoji 的位置
                m_EmojiBlocks[i][j]->m_pEmojiSprite->setPosition(getBlock_ij_AnchorPosition(i, j));
                //添加每一个 Emoji 到GamePlayingLayer
                addChild(m_EmojiBlocks[i][j]->m_pEmojiSprite);
            }
        }
    }
    else {
        bRet = false;
        CCLog("initTheGame() Fail");
    }
    return bRet;
}

bool GamePlayingLayer::checkMatch(int i, int j)
{
    bool bRet = false;
    int matchsInRow = 0;
    int matchsInColumn = 0;
    //Check matchs in row
    for (int delta = 1; j + delta < BLOCKS_IN_ROW; delta++) {
        if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
            matchsInRow++;
        else
            break;
    }
    for (int delta = -1; j + delta >= 0; delta--) {
        if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
            matchsInRow++;
        else
            break;
    }
    //Check matchs in column
    for (int delta = 1; i + delta < BLOCKS_IN_COLUMN; delta++) {
        if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
            matchsInColumn++;
        else
            break;
    }
    for (int delta = -1; i + delta >= 0; delta--) {
        if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
            matchsInColumn++;
        else
            break;
    }
    //Check Match Type
    if (matchsInRow >= 2 || matchsInColumn >= 2) {
        bRet = true;
        //matchs happen in row
        if (matchsInRow - matchsInColumn > 0) {
            //mark match block in row
            for (int delta = 1; j + delta < BLOCKS_IN_ROW; delta++) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i][j+delta] = true;
                }
                else
                    break;
            }
            for (int delta = -1; j + delta >= 0; --delta) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i][j+delta] = true;
                }
                else
                    break;
            }

        }
        //matchs happen in row and column L or T 5 matchs
        if (matchsInRow - matchsInColumn == 0) {
            //Mark match block in row
            for (int delta = 1; j + delta < BLOCKS_IN_ROW; delta++) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i][j+delta] = true;
                }
                else
                    break;
            }
            for (int delta = -1; j + delta >= 0; delta--) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i][j+delta]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i][j+delta] = true;
                }
                else
                    break;
            }
            //Mark match block in coloumn
            for (int delta = 1; i + delta < BLOCKS_IN_COLUMN; delta++) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i+delta][j] = true;
                }
                else
                    break;
            }
            for (int delta = -1; i + delta >= 0; delta--) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i+delta][j] = true;
                }
                else
                    break;
            }
        }
        //match happen in column
        else
        {
            //Mark match block in coloumn
            for (int delta = 1; i + delta < BLOCKS_IN_COLUMN; delta++) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i+delta][j] = true;
                }
                else
                    break;
            }
            for (int delta = -1; i + delta >= 0; delta--) {
                if(m_EmojiBlocks[i][j]->m_EmojiType == m_EmojiBlocks[i+delta][j]->m_EmojiType)
                {
                    m_matchMark[i][j] = true;
                    m_matchMark[i+delta][j] = true;
                }
                else
                    break;
            }
        }
    }
    return bRet;
}

void GamePlayingLayer::clearMatchsEmoji(){
    this->unschedule(schedule_selector(GamePlayingLayer::clearMatchsEmoji));
    for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
        for (int j = 0; j < BLOCKS_IN_ROW; j++) {
            if(m_matchMark[i][j]) {
                //消除match的Emoji
                m_EmojiBlocks[i][j]->m_pEmojiSprite->setOpacity(0);
                removeChild(m_EmojiBlocks[i][j]);
                m_EmojiBlocks[i][j]->release();
                m_EmojiBlocks[i][j] = NULL;
            }
        }
    } //End of the for loop 
        
    //计算 emptyBlocksInColumn & topEmptyBlock & createEmojiWithRandom
    int counter = 0;
    int emptyBlocksInColumn[BLOCKS_IN_ROW];
    int topEmptyBlock[BLOCKS_IN_ROW];
    
    for (int j = 0; j < BLOCKS_IN_ROW; j++) {
        emptyBlocksInColumn[j] = 0;
        topEmptyBlock[j] = BLOCKS_IN_COLUMN;
    }
    
    for (int j = 0; j < BLOCKS_IN_ROW; j++) {
        counter = 0;
        for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
            if(m_matchMark[i][j]) {
                topEmptyBlock[j] = i; //Mark top empty block's ID
                counter++;
                m_EmojiBlocks[i][j] = EmojiSprite::createEmojiWithRandom(Sprite_Tutu, Sprite_Happy);   //暂时借用消除的block 放置新生成的Emoji 现在m_matchMark[i][j]为True的block 表示新生成的Emoji
                m_EmojiBlocks[i][j]->retain();
                CCLog("Generate new emoji and put it in m_EmojiBlocks[%d][%d] temporarily.",i,j);
                addChild(m_EmojiBlocks[i][j]->m_pEmojiSprite);
            }
        }
        emptyBlocksInColumn[j] = counter;
    }
    //更新column emoji的次序 新产生的emoji依次放在column的上面

    for (int j = 0; j < BLOCKS_IN_ROW; j++) {
        if (emptyBlocksInColumn[j] != 0 ) {
            EmojiSprite* temp[emptyBlocksInColumn[j]];
            int tempArrayIndex = 0;
            for (int i = topEmptyBlock[j] + 1 - emptyBlocksInColumn[j]; i < BLOCKS_IN_COLUMN; i++){
                //Switch this new emoji to temp array
                if (m_matchMark[i][j]) {
                    temp[tempArrayIndex] = m_EmojiBlocks[i][j];
                    tempArrayIndex++;
                }
                //update the old emoji's(which is above the topMatchs emoji) position in the array
                else m_EmojiBlocks[i - emptyBlocksInColumn[j]][j] = m_EmojiBlocks[i][j];
            }
            //将tempArray中的Emoji放到column顶部
            for (int p = 0; p < tempArrayIndex; p++) {
                m_EmojiBlocks[BLOCKS_IN_COLUMN - emptyBlocksInColumn[j] + p][j] = temp[p];
                //设置新产生emoji的位置
                m_EmojiBlocks[BLOCKS_IN_COLUMN - emptyBlocksInColumn[j] + p][j]->m_pEmojiSprite->setPosition(getBlock_ij_AnchorPosition(BLOCKS_IN_COLUMN + p, j));
            }
        }
    }
    //Move down被消除Emoji上面的Emoji
    for (int j = 0; j < BLOCKS_IN_ROW; j++) {
        for (int i = topEmptyBlock[j] + 1 - emptyBlocksInColumn[j]; i < BLOCKS_IN_COLUMN; i++) {
            CCActionInterval* moveDown = CCMoveBy::create(EMOJI_MOVE_DOWN_TIME*emptyBlocksInColumn[j], ccp(0, -emptyBlocksInColumn[j]*m_fEmojiWidth));
            CCLog("m_EmojiBlocks[%d][%d] is trying to run move down action",i,j);
            m_EmojiBlocks[i][j]->m_pEmojiSprite->runAction(moveDown);
        }
    }
    //calculate the emoji change area

    //重置Matchs标志位矩阵
    resetMatchMarkArray();
    
    //检测当前阵列是否有matchs的情况..
    int moveDownStep = BLOCKS_IN_COLUMN;
    bool bMatch = false;
    for (int i = BLOCKS_IN_COLUMN -1; i >=0 ; i--) {
        for (int j = BLOCKS_IN_ROW - 1; j >= 0; j--) {
            bMatch = bMatch || checkMatch(i, j);
        }
        if (bMatch) {
            for (int i = BLOCKS_IN_COLUMN - 1; i >= 0; i--) {
                for (int j = BLOCKS_IN_ROW - 1; j >= 0; j--) {
                    if (m_matchMark[i][j]) {
                        if(i < moveDownStep) moveDownStep = i;
                        CCLog("m_matchMark[%d][%d] is true",i,j);
                        m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
                    }
                }
            }
            //新生成的emoji落到位置 后消除Matchs的Emoji
            //Set one schedule to run the update function which will set up the next scene
            CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GamePlayingLayer::clearMatchsEmoji),this,(BLOCKS_IN_COLUMN - moveDownStep)*EMOJI_MOVE_DOWN_TIME,false);
        }
    }
}

//Utility Method
void GamePlayingLayer::resetMatchMarkArray()
{
    for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
        for (int j = 0; j < BLOCKS_IN_ROW; j++) {
            m_matchMark[i][j] = false;
        }
    }
}

CCPoint GamePlayingLayer::getBlock_ij_AnchorPosition(int i, int j)
{
    float offset = 0;
    if(0 == BLOCKS_IN_ROW%2)
        offset = BLOCKS_IN_ROW*0.5 - 0.5;   //8 Blocks [][][][]|[][][][] = 3.5 10mod2 = 0
    
    else
        offset = BLOCKS_IN_ROW*0.5;   //9 Blocks [][][][]-[][][][] = 4.5
    return CCPoint(m_fEmojiBlockCenter_X + (j-offset)*m_fEmojiWidth, m_fEmojiBlockCenter_Y + (i-offset)*m_fEmojiWidth);
}

//Touch Event Processing Method
bool GamePlayingLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //The touch is in the blocks
    if (pTouch->getLocation().x > m_Blocks_0_0.x && pTouch->getLocation().x < m_Blocks_1_1.x && pTouch->getLocation().y > m_Blocks_0_0.y && pTouch->getLocation().y < m_Blocks_1_1.y) {
        //Calculate which block is touched and mark it with yellow background color
        int i = (int)(pTouch->getLocation().y - m_Blocks_0_0.y)/(int)m_fEmojiWidth;
        int j = (int)(pTouch->getLocation().x - m_Blocks_0_0.x)/(int)m_fEmojiWidth;
        m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
        //Mark begin block
        m_beginBlockI = i;
        m_beginBlockJ = j;
        CCLog("m_beginBlockI:%d, m_beginBlockJ:%d", i,j);
    }
    return true;
}

void GamePlayingLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    m_EmojiBlocks[m_beginBlockI][m_beginBlockJ]->m_pEmojiSprite->setColor(ccWHITE);
    //The touch is in the blocks
    if (pTouch->getLocation().x > m_Blocks_0_0.x && pTouch->getLocation().x < m_Blocks_1_1.x && pTouch->getLocation().y > m_Blocks_0_0.y && pTouch->getLocation().y < m_Blocks_1_1.y) {
        //Calculate which block is touched and mark it with yellow background color
        int i = (int)(pTouch->getLocation().y - m_Blocks_0_0.y)/(int)m_fEmojiWidth;
        int j = (int)(pTouch->getLocation().x - m_Blocks_0_0.x)/(int)m_fEmojiWidth;
        //Touch End的点在上下左右 四个block
        if (1 == (i-m_beginBlockI)*(i-m_beginBlockI) + (j-m_beginBlockJ)*(j-m_beginBlockJ)){
            EmojiSprite* tempSwitch = m_EmojiBlocks[m_beginBlockI][m_beginBlockJ];
            m_EmojiBlocks[m_beginBlockI][m_beginBlockJ] = m_EmojiBlocks[i][j];
            m_EmojiBlocks[i][j] = tempSwitch;
            tempSwitch = NULL;
            //Match happens
            if(checkMatch(i, j) || checkMatch(m_beginBlockI, m_beginBlockJ))
            {
                //If match happens => Swap the touch begin and touch end emoji
                CCActionInterval* moveTouchEndSpriteAction = CCMoveTo::create(EMOJI_SWAP_TIME, getBlock_ij_AnchorPosition(i, j));
                CCActionInterval* moveTouchBeginSpriteAction = CCMoveTo::create(EMOJI_SWAP_TIME, getBlock_ij_AnchorPosition(m_beginBlockI, m_beginBlockJ));

                m_EmojiBlocks[i][j]->m_pEmojiSprite->runAction(moveTouchEndSpriteAction);
                m_EmojiBlocks[m_beginBlockI][m_beginBlockJ]->m_pEmojiSprite->runAction(moveTouchBeginSpriteAction);
                //将Matchs的Emoji背景设置为黄色
                for (int i = 0; i < BLOCKS_IN_COLUMN; i++) {
                    for (int j = 0; j< BLOCKS_IN_ROW; j++) {
                            if (m_matchMark[i][j]) {
                                CCLog("m_matchMark[%d][%d] is true",i,j);
                                m_EmojiBlocks[i][j]->m_pEmojiSprite->setColor(ccYELLOW);
                            }
                        }
                    }
                //1s后消除Matchs的Emoji
                //Set one schedule to run the update function which will set up the next scene
                CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(GamePlayingLayer::clearMatchsEmoji),this,MATCHS_KEEP_TIME,false);
            }
            else {
                EmojiSprite* tempSpriteSwitchBack = m_EmojiBlocks[m_beginBlockI][m_beginBlockJ];
                CCLog("touchEnd i:%d, touchEnd j:%d", i,j);
                m_EmojiBlocks[m_beginBlockI][m_beginBlockJ] = m_EmojiBlocks[i][j];
                m_EmojiBlocks[i][j] = tempSpriteSwitchBack;
                tempSpriteSwitchBack = NULL;
            }
        }
    }
}

void GamePlayingLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    ccTouchEnded(pTouch, pEvent);
}
