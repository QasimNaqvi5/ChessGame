#include "Peice.h"
#include "Board.h"
using namespace std;

Piece::Piece(int _r, int _c, Board* _b, COLOUR _clr) :
	P{ _r,_c }, B(_b), clr(_clr)
{

}
Piece::Piece(const Piece& other)
{
	P = other.P;
	clr = other.clr;
	B = other.B;
}
void Piece::Draw()
{

}
void Piece::setPos(Position p)
{
	P = p;
}



Position Piece::getPos()const
{
	return P;
}
void Piece::Move(Position D)
{
	this->P = D;
}
COLOUR Piece::getColour() const
{
	return clr;
}
bool Piece::isLegal(Position P)
{
	return true;
}
bool Piece::isVertical(Position S, Position D)
{
	return S.ci == D.ci;
}
bool Piece::isHorizontal(Position S, Position D)
{
	return S.ri == D.ri;
}
bool Piece::isDiagonal(Position S, Position D)
{
	int dr = abs(S.ri - D.ri);
	int dc = abs(S.ci - D.ci);
	return dr == dc;
}

bool Piece::isVerticalPathClear(Board* b, Position S, Position D)
{
	if (S.ri < D.ri)
	{
		for (int r = S.ri + 1; r < D.ri; r++)          //change in one loop
		{
			if (b->pieceAt({ r,S.ci }) != nullptr)
			{
				return false;
			}
		}
	}
	else
	{
		for (int r = S.ri - 1; r > D.ri; r--)  //int r = D.ri + 1; r < S.ri; r++
		{
			if (b->pieceAt({ r,S.ci }) != nullptr)
			{
				return false;
			}
		}
	}
	return true;
}

bool Piece::isHorizonatalPathClear(Board* b, Position S, Position D)
{
	if (S.ri != D.ri) return false;

	if (S.ci < D.ci)
	{
		for (int c = S.ci + 1; c < D.ci; c++)
		{
			if (b->pieceAt({ S.ri, c }) != nullptr)
				return false;
		}
	}
	else
	{
		for (int c = S.ci - 1; c > D.ci; c--)
		{
			if (b->pieceAt({ S.ri, c }) != nullptr)
				return false;
		}
	}
	return true;
}

bool Piece::isDiagonalPathClear(Board* b, Position S, Position D)
{
	int dr = S.ri - D.ri;
	int dc = S.ci - D.ci;
	if (dr > 0 && dc > 0)
	{
		int d = abs(D.ri - S.ri) - 1;
		for (int i = 1; i <= d; i++)
		{
			if (b->pieceAt({ S.ri - i , S.ci - i }) != nullptr)
			{
				return false;
			}
		}
	}
	else if (dr < 0 && dc < 0)
	{
		int d = abs(D.ri - S.ri) - 1;
		for (int i = 1; i <= d; i++)
		{
			if (b->pieceAt({ S.ri + i , S.ci + i }) != nullptr)
			{
				return false;
			}
		}
	}
	else if (dr > 0 && dc < 0)
	{
		int d = abs(D.ri - S.ri) - 1;
		for (int i = 1; i <= d; i++)
		{
			if (b->pieceAt({ S.ri - i , S.ci + i }) != nullptr)
			{
				return false;
			}
		}
	}
	else
	{
		int d = abs(D.ri - S.ri) - 1;
		for (int i = 1; i <= d; i++)
		{
			if (b->pieceAt({ S.ri + i , S.ci - i }) != nullptr)
			{
				return false;
			}
		}
	}
	return true;
}



King::King(int _ri, int _ci, Board* _b, COLOUR _clr)
	:Piece(_ri, _ci, _b, _clr)
{
}

void King::Draw()
{
	int x = static_cast<int>(P.ri * tileSize + (tileSize / 4));
	int y = static_cast<int>(P.ci * tileSize + (tileSize / 4));

	if (clr == PBLACK)
	{
		DrawTexture(textureB, y, x, RAYWHITE);
	}
	else
	{
		DrawTexture(textureW, y, x, RAYWHITE);
	}
}

void King::_loadTexture()
{
	if (clr == PBLACK)
	{
		textureB = LoadTexture("king-B.png");
		textureB.height = 70;
		textureB.width = 60;
	}
	else
	{
		textureW = LoadTexture("king-W.png");
		textureW.height = 70;
		textureW.width = 60;
	}
}

bool King::isLegal(Position D)
{
	int dr = abs(this->P.ri - D.ri);
	int dc = abs(this->P.ci - D.ci);

	// Normal king move (one square in any direction)
	if ((dr <= 1 && dc <= 1) && !(dr == 0 && dc == 0))
	{
		return true;
	}

	// Castling move (king moves two squares horizontally)
	if (dr == 0 && abs(dc) == 2)
	{
		return true; // Actual castling validation is handled in Board::handleCastling
	}

	return false;
}

Knight::Knight(int _ri, int _ci, Board* _b, COLOUR _clr)
	:Piece(_ri, _ci, _b, _clr)
{
}
void Knight::Draw()
{

	int x = P.ri * tileSize + (tileSize / 4);
	int y = P.ci * tileSize + (tileSize / 4);

	if (clr == PBLACK)
	{
		DrawTexture(textureB, y, x, RAYWHITE);
	}
	else
	{
		DrawTexture(textureW, y, x, RAYWHITE);
	}

}

bool Knight::isLegal(Position D)
{
	int dr = abs(this->P.ri - D.ri);
	int dc = abs(this->P.ci - D.ci);
	return (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
}

void Knight::_loadTexture()
{
	if (clr == PBLACK)
	{
		textureB = LoadTexture("knight-B.png");
		textureB.height = 70;
		textureB.width = 60;
	}
	else
	{
		textureW = LoadTexture("knight-W.png");
		textureW.height = 70;
		textureW.width = 60;
	}
}



Pawn::Pawn(int _ri, int _ci, Board* _b, COLOUR _clr)
	:Piece(_ri, _ci, _b, _clr)
{
}

void Pawn::Draw()
{
	int x = P.ri * tileSize + (tileSize / 4);
	int y = P.ci * tileSize + (tileSize / 4);

	if (clr == PBLACK)
	{
		DrawTexture(textureB, y, x, RAYWHITE);
	}
	else
	{
		DrawTexture(textureW, y, x, RAYWHITE);
	}
}

bool Pawn::isLegal(Position D)
{
	int dr = D.ri - this->P.ri;
	int dc = D.ci - this->P.ci;

	int direction = (this->getColour() == PWHITE) ? -1 : 1;

	// Normal move forward
	if (dc == 0 && dr == direction && B->pieceAt(D) == nullptr)
	{
		return isVerticalPathClear(B, this->P, D);
	}

	// Two-square initial move
	if (dc == 0 && dr == 2 * direction && B->pieceAt(D) == nullptr)
	{
		if ((this->getColour() == PWHITE && P.ri == 6) ||
			(this->getColour() == PBLACK && P.ri == 1))
		{
			return isVerticalPathClear(B, this->P, D);
		}
	}

	// Normal capture
	if (abs(dc) == 1 && dr == direction)
	{
		// Diagonal capture
		if (B->pieceAt(D) && B->pieceAt(D)->getColour() != this->getColour())
		{
			return true;
		}

		// En passant capture
		Position lastMoveTo = B->getLastMoveTo();
		if (B->pieceAt(D) == nullptr &&
			lastMoveTo.ri == P.ri &&
			lastMoveTo.ci == D.ci)
		{
			Position temp = { P.ri, D.ci };
			Piece* adjacentPawn = B->pieceAt(temp);
			if (adjacentPawn &&
				adjacentPawn->getColour() != this->getColour() &&
				dynamic_cast<Pawn*>(adjacentPawn))
			{
				Position lastMoveFrom = B->getLastMoveFrom();
				if (abs(lastMoveFrom.ri - lastMoveTo.ri) == 2)
				{
					return true;
				}
			}
		}
	}

	return false;
}

void Pawn::_loadTexture()
{
	if (clr == PBLACK)
	{
		textureB = LoadTexture("pawn-B.png");
		textureB.height = 70;
		textureB.width = 60;
	}
	else
	{
		textureW = LoadTexture("pawn-W.png");
		textureW.height = 70;
		textureW.width = 60;
	}
}


Queen::Queen(int ri, int ci, Board* b, COLOUR clr)
	: Piece(ri, ci, b, clr), Rook(ri, ci, b, clr), Bishop(ri, ci, b, clr) {
}

void Queen::Draw()
{
	int x = P.ri * tileSize + (tileSize / 4);
	int y = P.ci * tileSize + (tileSize / 4);

	if (clr == PBLACK)
	{
		DrawTexture(textureB, y, x, RAYWHITE);
	}
	else
	{
		DrawTexture(textureW, y, x, RAYWHITE);
	}
}

bool Queen::isLegal(Position D)
{
	if (isVertical(P, D))
		return isVerticalPathClear(B, P, D);
	if (isHorizontal(P, D))
		return isHorizonatalPathClear(B, P, D);
	if (isDiagonal(P, D))
		return isDiagonalPathClear(B, P, D);
	return false;
}


void Queen::_loadTexture()
{
	if (clr == PBLACK)
	{
		textureB = LoadTexture("queen-B.png");
		textureB.height = 70;
		textureB.width = 60;
	}
	else
	{
		textureW = LoadTexture("queen-W.png");
		textureW.height = 70;
		textureW.width = 60;
	}
}


Rook::Rook(int _ri, int _ci, Board* _b, COLOUR _clr)
	:Piece(_ri, _ci, _b, _clr)
{
}
void Rook::Draw()
{
	int x = P.ri * tileSize + (tileSize / 4);
	int y = P.ci * tileSize + (tileSize / 4);

	if (clr == PBLACK)
	{
		DrawTexture(textureB, y, x, RAYWHITE);
	}
	else
	{
		DrawTexture(textureW, y, x, RAYWHITE);
	}

}

bool Rook::isLegal(Position D)
{
	return((isVertical(this->P, D) && isVerticalPathClear(B, this->P, D)
		|| (isHorizontal(this->P, D) && isHorizonatalPathClear(B, this->P, D))));
}

void Rook::_loadTexture()
{
	if (clr == PBLACK)
	{
		textureB = LoadTexture("rook-B.png");
		textureB.height = 70;
		textureB.width = 60;
	}
	else
	{
		textureW = LoadTexture("rook-W.png");
		textureW.height = 70;
		textureW.width = 60;
	}
}



Bishop::Bishop(int _ri, int _ci, Board* _b, COLOUR _clr)
	:Piece(_ri, _ci, _b, _clr)
{
}
void Bishop::Draw()
{
	int x = P.ri * tileSize + (tileSize / 4);
	int y = P.ci * tileSize + (tileSize / 4);

	if (clr == PBLACK)
	{
		DrawTexture(textureB, y, x, RAYWHITE);
	}
	else
	{
		DrawTexture(textureW, y, x, RAYWHITE);
	}
}
bool Bishop::isLegal(Position D)
{
	return isDiagonal(this->P, D) && isDiagonalPathClear(B, this->P, D);
}

void Bishop::_loadTexture()
{
	if (clr == PBLACK)
	{
		textureB = LoadTexture("bishop-B.png");
		textureB.height = 70;
		textureB.width = 60;
	}
	else
	{
		textureW = LoadTexture("bishop-W.png");
		textureW.height = 70;
		textureW.width = 60;
	}

}


