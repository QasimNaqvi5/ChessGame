#pragma once
#include "Position.h"
#include <iostream>
#include"raylib.h"



using namespace std;
const int tileSize = 100;

class Board;
class Piece
{
protected:
	Position P;
	COLOUR clr;
	Board* B;
	Texture2D textureW;
	Texture2D textureB;


	static bool isVertical(Position S, Position D);
	static bool isHorizontal(Position S, Position D);
	static bool isDiagonal(Position S, Position D);

	bool isVerticalPathClear(Board* b, Position S, Position D);
	bool isHorizonatalPathClear(Board* b, Position S, Position D);
	bool isDiagonalPathClear(Board* b, Position S, Position D);
public:
	Piece(int _r, int _c, Board* _b, COLOUR _clr);
	Piece(const Piece& other);

	virtual void _loadTexture() = 0;
	void setPos(Position p);
	Position getPos()const;

	virtual void Draw() = 0;
	virtual bool isLegal(Position P) = 0;

	void Move(Position P);
	COLOUR getColour() const;

	void color(int k);

};




class Rook : virtual public Piece
{
public:
	Rook(int _ri, int _ci, Board* B, COLOUR _clr);
	void Draw() override;
	bool isLegal(Position P) override;
	void _loadTexture() override;

};

class Bishop :virtual public Piece
{
public:
	Bishop(int _ri, int _ci, Board* B, COLOUR _clr);
	void Draw() override;
	bool isLegal(Position P) override;
	void _loadTexture() override;

};

class Queen : public Rook, public Bishop
{
public:
	Queen(int _ri, int _ci, Board* B, COLOUR _clr);
	void Draw() override;

	bool isLegal(Position D) override;
	void _loadTexture() override;

};


class King : public Piece
{
public:
	King(int _ri, int _ci, Board* B, COLOUR _clr);
	void Draw() override;
	bool isLegal(Position D) override;
	void _loadTexture() override;
};

class Knight : public Piece
{
public:
	Knight(int _ri, int _ci, Board* B, COLOUR _clr);
	void Draw() override;
	bool isLegal(Position P) override;
	void _loadTexture() override;

};


class Pawn : public Piece
{
public:
	Pawn(int _ri, int _ci, Board* B, COLOUR _clr);
	void Draw() override;
	bool isLegal(Position P) override;
	void _loadTexture() override;

};

