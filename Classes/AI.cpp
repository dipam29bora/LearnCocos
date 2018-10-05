#include "AI.h"
#include "Definitions.h"
#include <iostream>
using namespace std; 

AI::AI(int playerPiece)
{
	this->playerPiece = playerPiece;

	if (O_PIECE == playerPiece)
	{
		aiPiece = X_PIECE;
	}
	else
	{
		aiPiece = O_PIECE;
	}

	checkMatchVector.push_back({ 0, 2, 1, 2, 2, 2 });

	checkMatchVector.push_back({ 0, 2, 0, 1, 0, 0 });

	checkMatchVector.push_back({ 0, 2, 1, 1, 2, 0 });

	checkMatchVector.push_back({ 2, 2, 1, 2, 0, 2 });

	checkMatchVector.push_back({ 2, 2, 2, 1, 2, 0 });

	checkMatchVector.push_back({ 2, 2, 1, 1, 0, 0 });

	checkMatchVector.push_back({ 0, 0, 0, 1, 0, 2 });

	checkMatchVector.push_back({ 0, 0, 1, 0, 2, 0 });

	checkMatchVector.push_back({ 0, 0, 1, 1, 2, 2 });

	checkMatchVector.push_back({ 2, 0, 2, 1, 2, 2 });

	checkMatchVector.push_back({ 2, 0, 1, 0, 0, 0 });

	checkMatchVector.push_back({ 2, 0, 1, 1, 0, 2 });

	checkMatchVector.push_back({ 0, 1, 1, 1, 2, 1 });

	checkMatchVector.push_back({ 1, 2, 1, 1, 1, 0 });

	checkMatchVector.push_back({ 2, 1, 1, 1, 0, 1 });

	checkMatchVector.push_back({ 1, 0, 1, 1, 1, 2 });

	checkMatchVector.push_back({ 0, 1, 2, 1, 1, 1 });

	checkMatchVector.push_back({ 1, 2, 1, 0, 1, 1 });

	checkMatchVector.push_back({ 0, 2, 2, 0, 1, 1 });

	checkMatchVector.push_back({ 2, 2, 0, 0, 1, 1 });

	checkMatchVector.push_back({ 0, 2, 2, 2, 1, 2 });

	checkMatchVector.push_back({ 0, 0, 2, 0, 1, 0 });

	checkMatchVector.push_back({ 0, 2, 0, 0, 0, 1 });

	checkMatchVector.push_back({ 2, 2, 2, 0, 2, 1 });
}

void AI::PlacePiece(int(*gridArray)[3][3], cocos2d::Sprite* gridPieces[3][3], int *gameState)
{
	try
	{
		for (int i =0;i<checkMatchVector.size(); i++)
		{
			CheckSection(checkMatchVector[i][0],
				checkMatchVector[i][1], checkMatchVector[i][2],
				checkMatchVector[i][3], checkMatchVector[i][4],
				checkMatchVector[i][5], AI_PIECE, gridArray, gridPieces	);
		}

		for (int i = 0; i < checkMatchVector.size(); i++)
		{
			CheckSection(checkMatchVector[i][0],
				checkMatchVector[i][1], checkMatchVector[i][2],
				checkMatchVector[i][3], checkMatchVector[i][4],
				checkMatchVector[i][5], PLAYER_PIECE, gridArray, gridPieces);
		}

		//center is empty
		CheckIfPieceIsEmpty(1, 1, gridArray, gridPieces);

		//corners are empty
		CheckIfPieceIsEmpty(0, 2, gridArray, gridPieces); 
		CheckIfPieceIsEmpty(2, 2, gridArray, gridPieces);
		CheckIfPieceIsEmpty(0, 0, gridArray, gridPieces);
		CheckIfPieceIsEmpty(2, 0, gridArray, gridPieces);

		//check for any other space
		CheckIfPieceIsEmpty(1, 2, gridArray, gridPieces);
		CheckIfPieceIsEmpty(0, 1, gridArray, gridPieces);
		CheckIfPieceIsEmpty(2, 1, gridArray, gridPieces);
		CheckIfPieceIsEmpty(1, 0, gridArray, gridPieces);
	}
	catch (const std::exception&)
	{

	}

	*gameState = STATE_PLAYING;
}

void AI::CheckSection(int X1, int Y1, int X2, int Y2, int X, int Y, int pieceToCheck, int(*gridArray)[3][3], cocos2d::Sprite *gridPieces[3][3])
{
	if ((*gridArray[X1][Y1]) == pieceToCheck && (*gridArray[X2][Y2]) == pieceToCheck)
	{
		if (EMPTY_PIECE == (*gridArray)[X][Y])
		{
			(*gridArray)[X][Y] == AI_PIECE;
			gridPieces[X][Y]->setTexture(O_PIECE_FILEPATH);
			gridPieces[X][Y]->setVisible(true);
			gridPieces[X][Y]->runAction(cocos2d::FadeIn::create(PIECE_FADE_IN_TIME));

			throw -1;
		}
	}
}
void AI::CheckIfPieceIsEmpty(int X, int Y, int(*gridArray)[3][3], cocos2d::Sprite* gridPieces[3][3])
{

}


