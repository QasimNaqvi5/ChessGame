#ifndef PEICE_H
#define PEICE_H

#include<iostream>
#include"Position.h"
#include<raylib.h>
class Board;
class Piece
{
protected:
	Position P;
	PColor C;
	Board* B;
	int col, row;
	Texture2D texture;





public:
	Piece(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex);
	void move(Position Des);
	//virtual void Draw() = 0;
	void Draw(int squareSize);
	virtual bool IsLegalMove(Position D) = 0;
	PColor getClr();
	bool IsVertical(Position D);
	bool IsHorizontal(Position D);
	bool IsDiagonal(Position D);
	

};



#endif 

