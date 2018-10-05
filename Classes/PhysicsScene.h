#pragma once

#include "cocos2d.h"

class PhysicsScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(PhysicsScene);

private:
	void SwitchToMainMenu(float dt);
};

