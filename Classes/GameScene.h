#pragma once

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(GameScene);

private:
	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);

	void InitGridRects();
	void InitGridPieces();
	 
	void CheckAndPlacePiece(cocos2d::Touch *touch);
	void CheckWin(int x, int y);
	void Check3PiecedForMatch(int x1, int y1, int x2, int y2, int x3, int y3);

	cocos2d::Sprite *gridSprite; //Background
	cocos2d::Rect gridSpaces[3][3]; //Track the current clicked tile
	cocos2d::Sprite *gridPieces[3][3]; //Draw the pieces on every grid cell

	int gridArray[3][3];
	int turn;
	int gameState;
};

