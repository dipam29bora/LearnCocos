
#include "PhysicsScene.h"
#include "HelperFiles/SonarFrameworks.h"
#include "Definitions.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* PhysicsScene::createScene()
{
    
	auto scene = Scene::create();

	auto layer = PhysicsScene::create();

	scene->addChild(layer);

	return scene;

}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SplashScene.cpp\n");
}

// on "init" you need to initialize your instance
bool PhysicsScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
	//SonarCocosHelper::GooglePlayServices::signIn();

	
    return true;
}

void PhysicsScene::SwitchToMainMenu(float dt)
{
	Scene *scene = MainMenuScene::createScene();
	TransitionFade *transition = TransitionFade::create(SPLASHSCENE_TRANSITION_TIME, scene);
	Director::getInstance()->replaceScene(transition);
}
