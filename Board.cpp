#include"Peice.h"
#include"Board.h"
#include<iostream>

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

	SetBoard();
	Turn = PWHITE;
}
void Board::SetBoard()
{
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
	if (Ps[S.x][S.y] == nullptr)
	{
		return false;
	}
	return Ps[S.x][S.y]->getClr() == Turn;
}
bool Board::IsValidDestination(Position P)
{
	if (P.x < 0 || P.x >7 || P.y < 0 || P.y >7)
	{
		return false;
	}
	if (Ps[P.x][P.y] != nullptr)
	{
		if (Ps[P.x][P.y]->getClr() == Turn)
		{
			return false;
		}
	}
	return true;
}


void Board::PlayN()
{


	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);



		if (!Gameover) {
			Update();
		}
		DisplayBoard();
		if (Gameover && IsKeyPressed(KEY_ESCAPE)) {
			CloseWindow();
			exit(0);
		}


		EndDrawing();
	}
	CloseWindow();
}




void Board::DisplayBoard() {
	int squareSize = 80;
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			Color squareColor = ((row + col) % 2 == 0) ? LIGHTGRAY : DARKGRAY;
			DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize, squareColor);

			if (Ps[row][col] != nullptr)
			{

				Ps[row][col]->Draw(squareSize);

			}
		}
	}
	if (Gameover) {
		DrawRectangle(100, 150, 500, 200, Fade(RAYWHITE, 0.85f));
		DrawText("CHECKMATE!", 230, 180, 40, RED);

		const char* winnerText = (winner == PWHITE) ? "White Wins" : "Black Wins";
		DrawText(winnerText, 260, 240, 30, DARKBLUE);
		DrawText("Press ESC to exit", 250, 290, 20, GRAY);
	}

}

void Board::Update() {
	if (Gameover)
	{
		return;
	}

	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
		Vector2 mouse = GetMousePosition();
		int col = (int)mouse.x / 80;
		int row = (int)mouse.y / 80;
		Position clicked{ row, col };

		if (!selected) {
			if (IsValidSource(clicked)) {
				selectedPos = clicked;
				selected = true;
			}
		}
		else {
			if ((IsValidDestination(clicked) && Ps[selectedPos.x][selectedPos.y]->IsLegalMove(clicked))) {
				Ps[selectedPos.x][selectedPos.y]->move(clicked);
				MoveOnBoard(selectedPos, clicked);

				Turn = (Turn == PBLACK) ? PWHITE : PBLACK;
				if (IsCheckmate(Turn)) {
					Gameover = true;
					winner = (Turn == PWHITE ? PBLACK : PWHITE);
				}

			}
			selected = false;
		}

	}
}

void Board::MoveOnBoard(Position S, Position D)
{

	Ps[D.x][D.y] = Ps[S.x][S.y];
	Ps[S.x][S.y] = nullptr;
}
Piece* Board::PieceAt(Position P)
{
	return Ps[P.x][P.y];
}

Position Board::FindKing(PColor Turn)
{
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (Ps[r][c] != nullptr &&
				Ps[r][c]->getClr() == Turn &&
				dynamic_cast<King*>(Ps[r][c]) != nullptr) {
				return { r, c };
			}
		}
	}

	return { -1, -1 };
}

bool Board::IsCheck(PColor Turn)
{
	PColor OppTurn = (Turn == PBLACK) ? PWHITE : PBLACK;
	Position P = FindKing(Turn);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{

			if (Ps[i][j] != nullptr && Ps[i][j]->getClr() == OppTurn)
			{
				if (Ps[i][j]->IsLegalMove(P))
				{
					return true;
				}
			}
		}
	}
	return false;
}
void Board::WarnIfCheck(PColor Turn)
{
	if (IsCheck(Turn))
	{
		cout << "Your King is under Check!!!!!!!\n";
	}
}


bool Board::IsCheckmate(PColor Turn)
{
	if (!IsCheck(Turn))
		return false;

	for (int r = 0; r < 8; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (Ps[r][c] != nullptr && Ps[r][c]->getClr() == Turn)
			{
				for (int r2 = 0; r2 < 8; r2++)
				{
					for (int c2 = 0; c2 < 8; c2++)
					{
						Position dest{ r2, c2 };
						if (Ps[r][c]->IsLegalMove(dest) && IsValidDestination(dest))
						{

							Piece* temp = Ps[r2][c2];
							Ps[r2][c2] = Ps[r][c];
							Ps[r][c] = nullptr;

							bool stillInCheck = IsCheck(Turn);


							Ps[r][c] = Ps[r2][c2];
							Ps[r2][c2] = temp;

							if (!stillInCheck)
								return false;
						}
					}
				}
			}
		}
	}
	return true;
}
void Board::MakeAIMove() {
	vector<pair<Piece*, Position>> possibleMoves;


	PColor oldTurn = Turn;
	Turn = PWHITE;

	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (Ps[r][c] != nullptr && Ps[r][c]->getClr() == PWHITE) {
				for (int r2 = 0; r2 < 8; r2++) {
					for (int c2 = 0; c2 < 8; c2++) {
						Position dest{ r2, c2 };


						if (Ps[r][c]->IsLegalMove(dest) && IsValidDestination(dest)) {
							possibleMoves.push_back({ Ps[r][c], dest });
						}
					}
				}
			}
		}
	}

	if (possibleMoves.empty()) {
		Turn = oldTurn;
		return;
	}

	auto moveChoice = possibleMoves[rand() % possibleMoves.size()];
	Piece* selectedPiece = moveChoice.first;
	Position moveTo = moveChoice.second;
	Position startPos = selectedPiece->GetPosition();

	if (Ps[moveTo.x][moveTo.y] != nullptr) {
		delete Ps[moveTo.x][moveTo.y];
	}

	Ps[moveTo.x][moveTo.y] = selectedPiece;
	Ps[startPos.x][startPos.y] = nullptr;
	selectedPiece->move(moveTo);


	if (IsCheckmate(PBLACK)) {
		Gameover = true;
		winner = PWHITE;
	}

	Turn = oldTurn == PWHITE ? PBLACK : PWHITE;
}





void Board::PlayAI() {
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);



		DisplayBoard();

		if (!Gameover) {
			if (Turn == PWHITE) {
				MakeAIMove();
			}
			else {
				Update();
			}
		}

		if (Gameover && IsKeyPressed(KEY_ESCAPE)) {
			CloseWindow();
			exit(0);
		}

		EndDrawing();
	}
	CloseWindow();
}
void Board::Play()
{
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Press 1 to manual with AI & 2 for AI", 50, 300, 30, BLACK);
		if (IsKeyPressed(KEY_ONE))
		{

			PlayN();
		}
		else if (IsKeyPressed(KEY_TWO))
		{

			PlayAI();
		}

		EndDrawing();
	}
	CloseWindow();
}


