
#include "PhysicsScene.h"
#include "HelperFiles/SonarFrameworks.h"
#include "Definitions.h"
#include "MainMenuScene.h"
#include "physics/CCPhysicsBody.h"

USING_NS_CC_EXT;

Scene* PhysicsScene::createScene()
{
    
	//To enable physics we have to create the scene with createWithPhysics method()
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = PhysicsScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());


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
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//creating the physics edge box around the screen
	auto edgeBox = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	
	auto edgeBoxNode = Node::create();
	edgeBoxNode->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
	edgeBoxNode->setPhysicsBody(edgeBox);

	this->addChild(edgeBoxNode);


	SonarCocosHelper::UI::AddCentredBackground(MAINMENUSCENE_BACKGROUND_FILEPATH, this);

	auto SimpleLabel = Label::createWithSystemFont("Something is written here!", "Arial", 16);
	SimpleLabel->setPosition(SonarCocosHelper::UI::GetScreenCenter());
	this->addChild(SimpleLabel);

	Button *btnSpawnCube = Button::create("", "");
	btnSpawnCube->setTitleText("Spawn a Cube");
	btnSpawnCube->setTitleFontSize(36);
	btnSpawnCube->setTitleColor(Color3B::GREEN);
	btnSpawnCube->setPosition(SonarCocosHelper::UI::GetScreenCenter()+Vec2(0,250));
	this->addChild(btnSpawnCube);

	btnSpawnCube->addTouchEventListener(CC_CALLBACK_2(PhysicsScene::TouchEvent, this));
	btnSpawnCube->setTag(TAG_RELEASE_CUBE_BUTTON);
	
	Button *btnOther = Button::create("", "");
	btnOther->setTitleText("The Other Button");
	btnOther->setTitleFontSize(36);
	btnOther->setTitleColor(Color3B::GREEN);
	btnOther->setPosition(SonarCocosHelper::UI::GetScreenCenter()+Vec2(0,150));
	this->addChild(btnOther);

	btnOther->addTouchEventListener(CC_CALLBACK_2(PhysicsScene::TouchEvent, this));
	btnOther->setTag(TAG_OTHER_BUTTON);
	
	


    return true;
}

void PhysicsScene::SwitchToMainMenu(float dt)
{
	Scene *scene = MainMenuScene::createScene();
	TransitionFade *transition = TransitionFade::create(SPLASHSCENE_TRANSITION_TIME, scene);
	Director::getInstance()->replaceScene(transition);
}

void PhysicsScene::TouchEvent(Ref *sender, Widget::TouchEventType type)
{
	Node *node = (Node*)sender;

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:

		if (TAG_RELEASE_CUBE_BUTTON == node->getTag())
		{
			SpawnCube();
		}
		else if (TAG_OTHER_BUTTON == node->getTag())
		{
			OtherButton();
		}


		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

void PhysicsScene::SpawnCube()
{
	//create physicsBody
	auto physicsBody = PhysicsBody::createBox(Size(65.0f, 81.0f), PhysicsMaterial(0.1f, 1.0f, 0.0f));
	physicsBody->setDynamic(false);

	//create a sprite
	auto sprite = Sprite::create(X_WINNING_PIECE_FILEPATH);
	sprite->setPosition(SonarCocosHelper::UI::GetScreenCenter() + Vec2(0, 0));

	//sprite will use physicxbody
	sprite->addComponent(physicsBody);

	//set initial velocity of physicsBody
	physicsBody->setVelocity(
				Vec2(
					cocos2d::random(-500, 500),
					cocos2d::random(-500, 500)
					)
					);


	//add contact event listner
	//auto contactListner = EventListenerPhysicsContact::create();
	//contactListner->onContactBegin = CC_CALLBACK_1(onContac);

}

void PhysicsScene::OtherButton()
{
	Scene* mainmenu = MainMenuScene::createScene();
	TransitionFade *tansition = TransitionFade::create(SPLASHSCENE_TRANSITION_TIME, mainmenu);
	Director::getInstance()->replaceScene(mainmenu);
}
