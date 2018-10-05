

#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"
#include "HelperFiles/SonarFrameworks.h"
#include "Definitions.h"
#include "GameScene.h"



Scene* MainMenuScene::createScene()
{
    
	auto scene = Scene::create();

	auto layer = MainMenuScene::create();

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
bool MainMenuScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
	
	SonarCocosHelper::UI::AddCentredBackground(MAINMENUSCENE_BACKGROUND_FILEPATH, this);

	Size screenSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//Title Sprite
	Sprite *title = Sprite::create(MAIN_MENU_TITLE_FILEPATH);
	title->setPosition(Vec2(screenSize.width / 2 + origin.x, screenSize.height * 0.75 + origin.y));
	this->addChild(title);

#pragma region Play Button

	Button *PlayButton = Button::create(MAIN_MENU_PLAY_BUTTON, MAIN_MENU_PLAY_BUTTON_PRESSED);
	PlayButton->setPosition(SonarCocosHelper::UI::GetScreenCenter());
	this->addChild(PlayButton);

	PlayButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::TouchEvent, this));
	PlayButton->setTag(TAG_MAIN_MENU_PLAY_BUTTON);

	Sprite *playButtonOuter = Sprite::create(MAIN_MENU_PLAY_BUTTON_OUTER);
	playButtonOuter->setPosition(SonarCocosHelper::UI::GetScreenCenter());
	this->addChild(playButtonOuter);

	//Adding extra buttons
	Button *PhysSceneButton = Button::create(X_WINNING_PIECE_FILEPATH, O_WINNING_PIECE_FILEPATH);
	PhysSceneButton->setPosition(SonarCocosHelper::UI::GetScreenCenter() + Vec2(0, -200));
	this->addChild(PhysSceneButton);

//	PhysSceneButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene));

#pragma endregion

#pragma region Audio Button
	SonarCocosHelper::UI ui;
	
	ui.AddAudioToggle(SOUND_ON_BUTTON, SOUND_ON_BUTTON_PRESSED, 
		SOUND_OFF_BUTTON, SOUND_OFF_BUTTON_PRESSED, this,
		SonarCocosHelper::UIButtonPosition::eBottomRight);

#pragma endregion

#pragma region Achievement Button

	Button *achievementsButton = Button::create(ACHIEVEMENTS_BUTTON, ACHIEVEMENTS_BUTTON_PRESSED);
	achievementsButton->setPosition(SonarCocosHelper::UI::GetScreenCorner(SonarCocosHelper::UIButtonPosition::eBottomLeft, achievementsButton));
	this->addChild(achievementsButton);

	achievementsButton->addTouchEventListener(CC_CALLBACK_2(MainMenuScene::TouchEvent, this));
	achievementsButton->setTag(TAG_ACHIEVEMENTS_BUTTON);

#pragma endregion



    return true;
}

void MainMenuScene::TouchEvent(Ref *sender, Widget::TouchEventType type)
{
	Node *node = (Node*)sender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		if (TAG_MAIN_MENU_PLAY_BUTTON == node->getTag())
		{
			Scene *scene = GameScene::createScene();
			TransitionFade *transition = TransitionFade::create(SPLASHSCENE_TRANSITION_TIME, scene);
			Director::getInstance()->replaceScene(scene);

		}
		else if(TAG_ACHIEVEMENTS_BUTTON == node->getTag())
		{
			SonarCocosHelper::GooglePlayServices::showAchievements();
		}
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
