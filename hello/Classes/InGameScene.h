#ifndef __InGameScene_SCENE_H__
#define __InGameScene_SCENE_H__

#include "cocos2d.h"
#include "Player.h"

class InGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(InGameScene);
private:
	// Add Event Touch 
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	// called when the user moves their finger
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	// called when the user lifts their finger
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	// called when the device goes to another application such as a phone call
	void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
	// Add Event Touch End

	Player *player;
};

#endif // __InGameScene_SCENE_H__
