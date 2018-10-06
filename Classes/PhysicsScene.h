#pragma once

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class PhysicsScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(PhysicsScene);
	
	void SpawnCube();
	void OtherButton();


private:
	void SwitchToMainMenu(float dt);
	void TouchEvent(Ref *sender, Widget::TouchEventType type);

	cocos2d::PhysicsWorld *m_PhysWorld;
	void setPhysicsWorld(cocos2d::PhysicsWorld *physworld) { m_PhysWorld = physworld; }
	
};

