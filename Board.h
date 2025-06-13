#ifndef BOARD_H
#define BOARD_H

#include"Peice.h"
#include<raylib.h>
#include<vector>
using namespace std;
//class Piece;
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
    bool Gameover = false;
    PColor winner;

public:
    Board();
    ~Board();
    void PlayN();
    void DisplayBoard();
    void LoadTextures();

    void Update();
    void SetBoard();

    Piece* PieceAt(Position P);
    void MoveOnBoard(Position S, Position D);

    Position FindKing(PColor Turn);
    bool IsCheck(PColor Turn);
    void WarnIfCheck(PColor Turn);
    bool IsCheckmate(PColor Turn);

    void MakeAIMove();
    void PlayAI();
    void Play();







};

#endif



