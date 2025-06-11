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
	bool IsVerticalPathClear(Position D);
	bool IsHorizontalPathClear(Position D);
	bool IsDiagonalPathClear(Position D);

	

};

class King :public Piece
{
public:
	King(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex);

	//void Draw(int squaresize);
	bool IsLegalMove(Position D)override;

};



class Queen : public Piece
{
public:
	Queen(int px, int py, PColor _c, Board * b, int c, int r, Texture2D tex);

	//void Draw(int squaresize);
	bool IsLegalMove(Position D) override;

};

class Bishop :public Piece
{
public:
	Bishop(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex);

	void Draw();
	bool IsLegalMove(Position D) override;

};

class Knight :public Piece
{
public:
	Knight(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex);

	void Draw();
	bool IsLegalMove(Position D)override;

};


class Pawn : public Piece
{
public:
	Pawn(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex);

	//void Draw()override;
	bool IsLegalMove(Position D)override;

};

class Rook :public Piece
{
public:
	Rook(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex);

	void Draw();
	bool IsLegalMove(Position D)override;

};













#endif 

