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
    PColor winner;

    bool Gameover = false;
    bool selected;
    Position selectedPos;


public:
    Board();
    ~Board();
   
    void DisplayBoard();
    void LoadTextures();
    void Play();

    void Update();

    Piece* PieceAt(Position P);
    void MoveOnBoard(Position S, Position D);
    void Highlight(Position S);
    void Unhighlight(Position S);
    Position FindKing(PColor Turn);
    bool IsCheck(PColor Turn);
    void WarnIfCheck(PColor Turn);
    bool IsCheckmate(PColor Turn);
  

};

#endif 