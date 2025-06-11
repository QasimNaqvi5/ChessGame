#include "Peice.h"
#include<iostream>
using namespace std;
Piece::Piece(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex) :P{ px,py }, C{ _c }, B{ b }
{

    col = c;
    row = r;
    texture = tex;
}
void Piece::Draw(int squaresize)
{
    if (texture.id == 0) {
        cout << "Texture not loaded for piece at " << row << ", " << col << endl;
        return;
    }
    //DrawTexture(texture, col * squaresize, row * squaresize,WHITE);
    DrawTextureEx(texture,
        Vector2{ (float)(P.y * squaresize), (float)(P.x * squaresize) },
        0.0f,
        (float)squaresize / texture.width,
        WHITE);
}
void Piece::move(Position Des)
{
    this->P = Des;

}

PColor Piece::getClr()
{
    return C;
}
bool Piece::IsVertical(Position D)
{
    return P.y == D.y;
}
bool Piece::IsHorizontal(Position D)
{
    return P.x == D.x;
}
bool Piece::IsDiagonal(Position D)
{
    int dx = abs(P.x - D.x);
    int dy = abs(P.y - D.y);
    return dx == dy;

}


bool Piece::IsVerticalPathClear(Position D)
{
    int step = (P.x - D.x < 0 ? 1 : -1);
    for (int i = P.x + step; i != D.x; i += step) {
        if (B->PieceAt({ i,D.y }) != nullptr)
            return false;
    }
    return true;
}
bool Piece::IsHorizontalPathClear(Position D)
{
    int step = (P.y - D.y < 0 ? 1 : -1);
    for (int i = P.y + step; i != D.y; i += step) {
        if (B->PieceAt({ D.x,i }) != nullptr)
            return false;
    }
    return true;
}
bool Piece::IsDiagonalPathClear(Position D)
{
    int stepR = (P.x - D.x < 0 ? 1 : -1);
    int stepC = (P.y - D.y < 0 ? 1 : -1);
    for (int i = P.x + stepR, j = P.y + stepC; i != D.x; i += stepR, j += stepC) {
        if (B->PieceAt({ i,j }) != nullptr)
            return false;
    }
    return true;
}












Bishop::Bishop(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex) :Piece(px, py, _c, b, c, r, tex)
{

}


void Bishop::Draw()
{
    if (C == PBLACK)
    {
        cout << "B";
    }
    else
    {
        cout << "b";
    }

}
bool Bishop::IsLegalMove(Position D)
{
    return IsDiagonal(D) && IsDiagonalPathClear(D);
}


Rook::Rook(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex) :Piece(px, py, _c, b, c, r, tex)
{

}


void Rook::Draw()
{
    if (C == PBLACK)
    {
        cout << "R";
    }
    else
    {
        cout << "r";
    }

}
bool Rook::IsLegalMove(Position D)
{
    if (IsVertical(D) && IsVerticalPathClear(D))
        return true;
    if (IsHorizontal(D) && IsHorizontalPathClear(D))
        return true;
    return false;
}

King::King(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex) :Piece(px, py, _c, b, c, r, tex)
{

}



bool King::IsLegalMove(Position D)
{
    int dx = abs(P.x - D.x);
    int dy = abs(P.y - D.y);

    return (dx <= 1 && dy <= 1);
}






Knight::Knight(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex) :Piece(px, py, _c, b, c, r, tex)
{

}


void Knight::Draw()
{
    if (C == PBLACK)
    {
        cout << "N";
    }
    else
    {
        cout << "n";
    }

}
bool Knight::IsLegalMove(Position D)
{
    int dx = abs(P.x - D.x);
    int dy = abs(P.y - D.y);

    return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
}




Pawn::Pawn(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex) :Piece(px, py, _c, b, c, r, tex)
{

}





bool Pawn::IsLegalMove(Position D) {
    int direction = (C == PWHITE) ? -1 : 1;
    int startRow = (C == PWHITE) ? 6 : 1;


    if (D.y == P.y && D.x == P.x + direction && B->PieceAt(D) == nullptr)
        return true;


    if (D.y == P.y && D.x == P.x + 2 * direction && P.x == startRow &&
        B->PieceAt(D) == nullptr && B->PieceAt({ P.x + direction, P.y }) == nullptr)
        return true;


    if (abs(D.y - P.y) == 1 && D.x == P.x + direction &&
        B->PieceAt(D) != nullptr && B->PieceAt(D)->getClr() != C)
        return true;

    return false;
}



Queen::Queen(int px, int py, PColor _c, Board* b, int c, int r, Texture2D tex) :Piece(px, py, _c, b, c, r, tex)
{

}



bool Queen::IsLegalMove(Position D)
{
    return
        (IsVertical(D) && IsVerticalPathClear(D)) ||
        (IsHorizontal(D) && IsHorizontalPathClear(D)) ||
        (IsDiagonal(D) && IsDiagonalPathClear(D));
}







