#include "cocos2d.h"

using namespace cocos2d;

class MainMenuView: public CCLayer
{
public:
    MainMenuView();
    ~MainMenuView();

    bool                init(bool fromGame = false);

    CCMenuItemLabel     *getStartButton() const;
    
protected:

private:
    CCMenu              *m_pMainMenu;
    CCMenuItemLabel     *m_pStartButton;


};