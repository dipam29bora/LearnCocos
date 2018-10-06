
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


	Button *btnSpawnCube = Button::create();
	btnSpawnCube->setTitleText("Spawn a Cube");
	btnSpawnCube->setTitleFontSize(36);
	btnSpawnCube->setTitleColor(Color3B::GREEN);
	btnSpawnCube->setTitleAlignment(TextHAlignment::LEFT);
	btnSpawnCube->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 50));
	this->addChild(btnSpawnCube);

	btnSpawnCube->addTouchEventListener(CC_CALLBACK_2(PhysicsScene::TouchEvent, this));
	btnSpawnCube->setTag(TAG_RELEASE_CUBE_BUTTON);
	
	Button *btnOther = Button::create();
	btnOther->setTitleText("The Other Button");
	btnOther->setTitleFontSize(36);
	btnOther->setTitleAlignment(TextHAlignment::LEFT);
	btnOther->setTitleColor(Color3B::GREEN);
	btnOther->setPosition(Vec2(visibleSize.width - 150, visibleSize.height - 150));
	this->addChild(btnOther);

	btnOther->addTouchEventListener(CC_CALLBACK_2(PhysicsScene::TouchEvent, this));
	btnOther->setTag(TAG_OTHER_BUTTON);
	
	
	{
		auto physSpriteA = Sprite::create(X_WINNING_PIECE_FILEPATH);
		physSpriteA->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y+250));


		auto spriteBody = PhysicsBody::createBox(physSpriteA->getContentSize(), PhysicsMaterial(0, 1, 0));
		spriteBody->setCollisionBitmask(1);
		spriteBody->setContactTestBitmask(true);
		physSpriteA->setPhysicsBody(spriteBody);

		this->addChild(physSpriteA);
	}

	{
		auto physSpriteB = Sprite::create(O_WINNING_PIECE_FILEPATH);
		physSpriteB->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));


		auto spriteBody = PhysicsBody::createBox(physSpriteB->getContentSize(), PhysicsMaterial(0, 1, 0));
		spriteBody->setCollisionBitmask(2);
		spriteBody->setContactTestBitmask(true);
		physSpriteB->setPhysicsBody(spriteBody);

		this->addChild(physSpriteB);
	}

	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(PhysicsScene::onBeginCollision, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool PhysicsScene::onBeginCollision(PhysicsContact &contact)
{
	PhysicsBody *A = contact.getShapeA()->getBody();
	PhysicsBody *B = contact.getShapeB()->getBody();

	if ((A->getCollisionBitmask() == 1 && B->getCollisionBitmask() == 2) || A->getCollisionBitmask() == 2 && B->getCollisionBitmask() == 1)
	{
		CCLOG("Collision is happening");
	}
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
	
	//create a sprite
	auto sprite = Sprite::create(X_WINNING_PIECE_FILEPATH);
	sprite->setPosition(SonarCocosHelper::UI::GetScreenCenter() + Vec2(0, 0));

	this->addChild(sprite);

}

void PhysicsScene::OtherButton()
{
	Scene* mainmenu = MainMenuScene::createScene();
	TransitionFade *tansition = TransitionFade::create(SPLASHSCENE_TRANSITION_TIME, mainmenu);
	Director::getInstance()->replaceScene(mainmenu);
}
