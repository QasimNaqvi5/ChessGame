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








