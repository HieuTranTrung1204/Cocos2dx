#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui\CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;

using namespace ui;

class MainMenuScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
   
	CREATE_FUNC(MainMenuScene);

private:
	void touchEvent(Ref* sender, Widget::TouchEventType type);
};

#endif // __MAINMENU_SCENE_H__
