#pragma once
#include "cocos2d.h"

USING_NS_CC;

#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC_EXT;
using namespace ui;

class MainMenuScene :public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MainMenuScene);
private:
	void TouchEvent(Ref *sender, Widget::TouchEventType type);
};