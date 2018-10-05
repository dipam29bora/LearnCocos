#pragma once

#include "cocos2d.h"
#include <vector>
#include <array>

class AI
{
public:
	AI(int playerPiece);

	void PlacePiece(int(*gridArray)[3][3], cocos2d::Sprite* gridPieces[3][3], int *gameState);

private:
	void CheckSection(int X1, int Y1, int X2, int Y2, int X, int Y, int pieceToCheck, int(*gridArray)[3][3], cocos2d::Sprite *gridPieces[3][3]);

	void CheckIfPieceIsEmpty(int X, int Y, int(*gridArray)[3][3], cocos2d::Sprite* gridPieces[3][3]);

	int aiPiece;
	int playerPiece;

	std::vector<std::array<int, 6>> checkMatchVector;

};
