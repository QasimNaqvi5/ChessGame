#ifndef BOARD_H
#define BOARD_H

#include<raylib.h>
#include"Peice.h"
class Board
{
    PColor Turn;
    Piece* Ps[8][8];
    bool Copy[8][8];
    static void TakeCoordinates(Position& P);
    bool IsValidSource(Position S);
    bool IsValidDestination(Position P);

    bool selected;
    Position selectedPos;


public:
    Board();
    ~Board();
    //void Play();
    void DisplayBoard();
    void LoadTextures();
    void Update();
};

#endif 