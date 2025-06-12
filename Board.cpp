#include"Peice.h"
#include<iostream>
#include"Board.h"
using namespace std;

Texture2D queenW, queenB, kingW, kingB, pawnW, pawnB, rookW, rookB, bishopW, bishopB, knightW, knightB;
void Board::LoadTextures()
{
	queenW = LoadTexture("queen-W.png");
	queenB = LoadTexture("queen-B.png");
	kingW = LoadTexture("king-W.png");
	kingB = LoadTexture("king-B.png");
	pawnW = LoadTexture("pawn-W.png");
	pawnB = LoadTexture("pawn-B.png");
	rookW = LoadTexture("rook-W.png");
	rookB = LoadTexture("rook-B.png");
	bishopW = LoadTexture("bishop-W.png");
	bishopB = LoadTexture("bishop-B.png");
	knightW = LoadTexture("knight-W.png");
	knightB = LoadTexture("knight-B.png");

}

Board::Board()
{
	LoadTextures();
	selected = false;
	selectedPos = { -1, -1 };
	for (int ri = 0;ri < 8;ri++)
	{
		for (int ci = 0;ci < 8;ci++)
		{
			if (ri == 1)
			{
				Ps[ri][ci] = new Pawn(ri, ci, PBLACK, this, ci, ri, pawnB);
			}
			else if (ri == 6)
			{
				Ps[ri][ci] = new Pawn(ri, ci, PWHITE, this, ci, ri, pawnW);
			}
			else
			{
				Ps[ri][ci] = nullptr;
			}
		}

	}
	Ps[0][0] = new Rook(0, 0, PBLACK, this, 0, 0, rookB);
	Ps[0][7] = new Rook(0, 7, PBLACK, this, 7, 0, rookB);
	Ps[0][1] = new Knight(0, 1, PBLACK, this, 1, 0, knightB);
	Ps[0][6] = new Knight(0, 6, PBLACK, this, 6, 0, knightB);
	Ps[0][2] = new Bishop(0, 2, PBLACK, this, 2, 0, bishopB);
	Ps[0][5] = new Bishop(0, 5, PBLACK, this, 5, 0, bishopB);
	Ps[0][3] = new Queen(0, 3, PBLACK, this, 3, 0, queenB);
	Ps[0][4] = new King(0, 4, PBLACK, this, 4, 0, kingB);

	Ps[7][0] = new Rook(7, 0, PWHITE, this, 0, 7, rookW);
	Ps[7][7] = new Rook(7, 7, PWHITE, this, 7, 7, rookW);
	Ps[7][1] = new Knight(7, 1, PWHITE, this, 1, 7, knightW);
	Ps[7][6] = new Knight(7, 6, PWHITE, this, 6, 7, knightW);
	Ps[7][2] = new Bishop(7, 2, PWHITE, this, 2, 7, bishopW);
	Ps[7][5] = new Bishop(7, 5, PWHITE, this, 5, 7, bishopW);
	Ps[7][3] = new Queen(7, 3, PWHITE, this, 3, 7, queenW);
	Ps[7][4] = new King(7, 4, PWHITE, this, 4, 7, kingW);

	Turn = PWHITE;
}
Board::~Board()
{
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j)
			delete Ps[i][j];
}


void Board::TakeCoordinates(Position& P)
{
	cin >> P.x >> P.y;

}

bool Board::IsValidSource(Position S)
{
	if (Ps[S.x][S.y] == nullptr) { return false; }

	return Ps[S.x][S.y]->getClr() == Turn;
}


bool Board::IsValidDestination(Position P)
{
	if (P.x < 0 || P.x >7 || P.y < 0 || P.y >7) { return false; }

	if (Ps[P.x][P.y] != nullptr){

		if (Ps[P.x][P.y]->getClr() == Turn) { return false; }
}
	return true;
}
