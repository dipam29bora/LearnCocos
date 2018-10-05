

#include "SplashScene.h"
#include "SimpleAudioEngine.h"
#include "HelperFiles/SonarFrameworks.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "PhysicsScene.h"

USING_NS_CC;

Scene* SplashScene::createScene()
{
    
	auto scene = Scene::create();

	auto layer = SplashScene::create();

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
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	
	//SonarCocosHelper::GooglePlayServices::signIn();

	SonarCocosHelper::UI::AddCentredBackground(SPLASHSCENE_BACKGROUND_FILEPATH, this);
	//scheduleOnce(schedule_selector(SplashScene::SwitchToMainMenu), SPLASHSCENE_TIME);
	scheduleOnce(schedule_selector(SplashScene::SwitchToPhysicsScene), SPLASHSCENE_TIME);
	
    return true;
}

void SplashScene::SwitchToMainMenu(float dt)
{
	Scene *scene = MainMenuScene::createScene();
	TransitionFade *transition = TransitionFade::create(SPLASHSCENE_TRANSITION_TIME, scene);
	Director::getInstance()->replaceScene(transition);
}

void SplashScene::SwitchToPhysicsScene(float dt)
{
	Scene *scene = PhysicsScene::createScene();
	TransitionFade *transition = TransitionFade::create(SPLASHSCENE_TRANSITION_TIME, scene);
	Director::getInstance()->replaceScene(transition);
}
