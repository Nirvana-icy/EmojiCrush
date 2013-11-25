#include "MainMenuView.h"

MainMenuView::MainMenuView()
{
}

bool MainMenuView::init(bool fromGame)
{
    CCLayer::init();

	CCSprite    *pBackground = CCSprite::create();
    pBackground->initWithFile("MainMenu_Background_Img.png");
    pBackground->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2));
	addChild(pBackground);

    m_pMainMenu = CCMenu::create();

    CCString caption = "Start Game.";
    if (fromGame)
        caption = "Resume Game.";

    CCLabelTTF* label = CCLabelTTF::create(caption.getCString(), "fonts/Marker Felt.ttf", 68);
    m_pStartButton = CCMenuItemLabel::create(label);
    m_pStartButton->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width/2, CCDirector::sharedDirector()->getWinSize().height/2) );

    m_pMainMenu->setPosition(0.f, 0.f);
    m_pMainMenu->addChild(m_pStartButton);

    addChild(m_pMainMenu);

    setTouchEnabled(true);

    return true;
}

CCMenuItemLabel* MainMenuView::getStartButton() const
{
    return m_pStartButton;
}

MainMenuView::~MainMenuView()
{
}