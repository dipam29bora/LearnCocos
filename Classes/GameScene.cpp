

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "HelperFiles/SonarFrameworks.h"
#include "Definitions.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    
	auto scene = Scene::create();

	auto layer = GameScene::create();

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
bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	
	SonarCocosHelper::UI::AddCentredBackground(GAMESCENE_BACKGROUND_FILEPATH, this);
	gridSprite = Sprite::create(GRID_FILEPATH);
	gridSprite->setPosition(SonarCocosHelper::UI::GetScreenCenter());
	this->addChild(gridSprite);

	InitGridRects();
	InitGridPieces();

	for (int x=0; x<3; x++)
	{
		for (int y=0; y<3; y++)
		{
			gridArray[x][y] = EMPTY_PIECE;
		}
	}

	turn = X_PIECE;
	gameState = STATE_PLAYING;

	EventListenerTouchOneByOne *listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	return true;
}

void GameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void GameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	if (STATE_PLAYING == gameState)
	{
		CheckAndPlacePiece(touch);
	}
}

void GameScene::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event)
{

}

void GameScene::InitGridRects()
{
	gridSpaces[0][0] = Rect(
		gridSprite->getBoundingBox().getMinX(),
		gridSprite->getBoundingBox().getMinY(),
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3
	);

	gridSpaces[1][0] = Rect(
		gridSprite->getBoundingBox().getMinX() + gridSprite->getBoundingBox().size.width/3,
		gridSprite->getBoundingBox().getMinY(),
		gridSprite->getBoundingBox().size.width/3,
		gridSprite->getBoundingBox().size.height/3
	);

	gridSpaces[2][0] = Rect(
		gridSprite->getBoundingBox().getMinX() + ((gridSprite->getBoundingBox().size.width/3) * 2),
		gridSprite->getBoundingBox().getMinY(),
		gridSprite->getBoundingBox().size.width/3,
		gridSprite->getBoundingBox().size.height/3
	);


	gridSpaces[0][1] = Rect(
		gridSprite->getBoundingBox().getMinX(),
		gridSprite->getBoundingBox().getMinY() + gridSprite->getBoundingBox().size.height/3,
		gridSprite->getBoundingBox().size.width/3,
		gridSprite->getBoundingBox().size.height/3
	);

	gridSpaces[1][1] = Rect(
		gridSprite->getBoundingBox().getMinX() + ((gridSprite->getBoundingBox().size.width / 3)),
		gridSprite->getBoundingBox().getMinY() + ((gridSprite->getBoundingBox().size.height / 3)),
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height/ 3
	);

	gridSpaces[2][1] = Rect(
		gridSprite->getBoundingBox().getMinX() + ((gridSprite->getBoundingBox().size.width / 3) * 2),
		gridSprite->getBoundingBox().getMinY() + gridSprite->getBoundingBox().size.height/3,
		gridSprite->getBoundingBox().size.width/3,
		gridSprite->getBoundingBox().size.height/3
	);


	gridSpaces[0][2] = Rect(
		gridSprite->getBoundingBox().getMinX(),
		gridSprite->getBoundingBox().getMinY() + ((gridSprite->getBoundingBox().size.height / 3) * 2),
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3

	);



	gridSpaces[1][2] = Rect(
		gridSprite->getBoundingBox().getMinX() + gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().getMinY() + ((gridSprite->getBoundingBox().size.height / 3) * 2),
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3

	);



	gridSpaces[2][2] = Rect(
		gridSprite->getBoundingBox().getMinX() + ((gridSprite->getBoundingBox().size.width / 3) * 2),
		gridSprite->getBoundingBox().getMinY() + ((gridSprite->getBoundingBox().size.height / 3) * 2),
		gridSprite->getBoundingBox().size.width / 3,
		gridSprite->getBoundingBox().size.height / 3
	);
}

void GameScene::InitGridPieces()
{
	for (int x =0; x<3; x++)
	{
		for (int y=0; y<3; y++)
		{
			gridPieces[x][y] = Sprite::create(X_PIECE_FILEPATH);

			gridPieces[x][y]->setPosition(
				Vec2(
					gridSprite->getPositionX() + (gridPieces[x][y]->getContentSize().width *  (x - 1)),
					gridSprite->getPositionY() + (gridPieces[x][y]->getContentSize().height * (y - 1))
					)
			);


			gridPieces[x][y]->setVisible(false);
			gridPieces[x][y]->setOpacity(0);
			this->addChild(gridPieces[x][y]);
		}
	}
}

void GameScene::CheckAndPlacePiece(cocos2d::Touch *touch)
{
	Rect rect1 = gridSprite->getBoundingBox();
	Point touchPoint = touch->getLocation();

	for (int x = 0; x<3; x++)
	{
		for (int y=0; y<3; y++)
		{
			if (gridSpaces[x][y].containsPoint(touchPoint))
			{
				if (gridArray[x][y] == EMPTY_PIECE)
				{
					gameState = STATE_PLACING_PIECE;
					gridArray[x][y] = turn;

					if (X_PIECE == turn)
					{
						gridPieces[x][y]->setTexture(X_PIECE_FILEPATH);
					}
					else
					{
						gridPieces[x][y]->setTexture(O_PIECE_FILEPATH);
					}

					gridPieces[x][y]->setVisible(true);
					gridPieces[x][y]->runAction(Sequence::create(FadeIn::create(PIECE_FADE_IN_TIME), CallFunc::create(std::bind(&GameScene::CheckWin, this, x, y)), NULL));
				}
			}
		}
	}
}

void GameScene::CheckWin(int x, int y)
{
	Check3PiecedForMatch(0, 0, 1, 0, 2, 0);
	Check3PiecedForMatch(0, 1, 1, 1, 2, 1);
	Check3PiecedForMatch(0, 2, 1, 2, 2, 2);
	Check3PiecedForMatch(0, 0, 0, 1, 0, 2);
	Check3PiecedForMatch(1, 0, 1, 1, 1, 2);
	Check3PiecedForMatch(2, 0, 2, 1, 2, 2);
	Check3PiecedForMatch(0, 0, 1, 1, 2, 2);
	Check3PiecedForMatch(0, 2, 1, 1, 2, 0);

	if (X_PIECE == turn)
	{
		turn = O_PIECE;
	}
	else
	{
		turn = X_PIECE;
	}

	if (STATE_PLACING_PIECE == gameState)
	{
		gameState = STATE_PLAYING;
	}
}

void GameScene::Check3PiecedForMatch(int x1, int y1, int x2, int y2, int x3, int y3)
{
	if (turn == gridArray[x1][y1] && turn == gridArray[x2][y2] && turn == gridArray[x3][y3])
	{
		__String winningPieceStr;

		if (O_PIECE == turn)
		{
			winningPieceStr = O_WINNING_PIECE_FILEPATH;
		}
		else
		{
			winningPieceStr = X_WINNING_PIECE_FILEPATH;
		}

		Sprite *winningPieces[3];

		winningPieces[0] = Sprite::create(winningPieceStr.getCString());
		winningPieces[0]->setPosition(gridPieces[x1][y1]->getPosition());
		winningPieces[0]->setOpacity(0);
		this->addChild(winningPieces[0]);

		winningPieces[1] = Sprite::create(winningPieceStr.getCString());
		winningPieces[1]->setPosition(gridPieces[x2][y2]->getPosition());
		winningPieces[1]->setOpacity(0);
		this->addChild(winningPieces[1]);

		winningPieces[2] = Sprite::create(winningPieceStr.getCString());
		winningPieces[2]->setPosition(gridPieces[x3][y3]->getPosition());
		winningPieces[2]->setOpacity(0);
		this->addChild(winningPieces[2]);

		winningPieces[0]->runAction(FadeIn::create(PIECE_FADE_IN_TIME));
		winningPieces[1]->runAction(Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME *0.5), FadeIn::create(PIECE_FADE_IN_TIME), NULL));
		winningPieces[2]->runAction(Sequence::create(DelayTime::create(PIECE_FADE_IN_TIME *1.5), FadeIn::create(PIECE_FADE_IN_TIME), NULL));

		gameState = STATE_WON;
	}
}
