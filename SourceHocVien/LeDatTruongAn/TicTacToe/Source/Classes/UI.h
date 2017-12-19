#pragma once

#include "cocos2d.h"

class UI
{
public:
	UI(cocos2d::Layer* layer);

	void ShowGameOver(cocos2d::Layer* layer);

private:
	void Retry(cocos2d::Ref* pSender);
	void GoToMainMenu(cocos2d::Ref* pSender);
};
