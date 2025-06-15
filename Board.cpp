

#include<vector>
#include "Board.h"
#include<iostream>
using namespace std;
COLOUR getOpponent(COLOUR clr) {
    return (clr == PWHITE) ? PBLACK : PWHITE;
}


Board::Board() : Turn(PBLACK), enPassantPossible(false),
whiteKingMoved(false), whiteRookKingSideMoved(false), whiteRookQueenSideMoved(false),
blackKingMoved(false), blackRookKingSideMoved(false), blackRookQueenSideMoved(false)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Ps[i][j] = nullptr;
            selectedPs = nullptr;
            selectedX = -1;
            selectedY = -1;
        }
    }
    lastMoveFrom = { -1, -1 };
    lastMoveTo = { -1, -1 };
}

void Board::InitializeBoard()
{
    for (int i = 0; i < 8; i++)
    {
    }
}

void Board::DrawChessBoard()
{
    Color light = BEIGE;
    Color dark = BROWN;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            bool isWhite = (i + j) % 2 == 0;
            Color color = isWhite ? light : dark;
            DrawRectangle(j * tileSize, i * tileSize, tileSize, tileSize, color);
        }
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Ps[i][j] != nullptr)
            {
                Ps[i][j]->Draw();
            }
        }
    }
}

void Board::load_Board()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Ps[i][j] != nullptr)
            {
                Ps[i][j]->_loadTexture();
            }
            else
            {
                Ps[i][j] = nullptr;
            }
        }
    }
}

void Board::init()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i == 1)
            {
                Ps[i][j] = new Pawn(i, j, this, PBLACK);
            }
            else if (i == 6)
            {
                Ps[i][j] = new Pawn(i, j, this, PWHITE);
            }
            else if (i == 0 && (j == 0 || j == 7))
            {
                Ps[i][j] = new Rook(i, j, this, PBLACK);
            }
            else if (i == 7 && (j == 0 || j == 7))
            {
                Ps[i][j] = new Rook(i, j, this, PWHITE);
            }
            else if (i == 0 && (j == 1 || j == 6))
            {
                Ps[i][j] = new Knight(i, j, this, PBLACK);
            }
            else if (i == 7 && (j == 1 || j == 6))
            {
                Ps[i][j] = new Knight(i, j, this, PWHITE);
            }
            else if (i == 0 && (j == 2 || j == 5))
            {
                Ps[i][j] = new Bishop(i, j, this, PBLACK);
            }
            else if (i == 7 && (j == 2 || j == 5))
            {
                Ps[i][j] = new Bishop(i, j, this, PWHITE);
            }
            else if (i == 0 && j == 4)
            {
                Ps[i][j] = new King(i, j, this, PBLACK);
            }
            else if (i == 7 && j == 4)
            {
                Ps[i][j] = new King(i, j, this, PWHITE);
            }
            else if (i == 0 && j == 3)
            {
                Ps[i][j] = new Queen(i, j, this, PBLACK);
            }
            else if (i == 7 && j == 3)
            {
                Ps[i][j] = new Queen(i, j, this, PWHITE);
            }
            else
            {
                Ps[i][j] = nullptr;
            }
        }
    }
}

void Board::loadFromFile()
{
    ifstream file("grid.txt");
    if (!file)
    {
        cout << "Error opening grid.txt! ." << endl;
        exit(0);
        return;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char piece;
            file >> piece;
            switch (piece)
            {
            case 'P':
                Ps[i][j] = new Pawn(i, j, this, PWHITE);
                break;
            case 'p':
                Ps[i][j] = new Pawn(i, j, this, PBLACK);
                break;
            case 'R':
                Ps[i][j] = new Rook(i, j, this, PWHITE);
                break;
            case 'r':
                Ps[i][j] = new Rook(i, j, this, PBLACK);
                break;
            case 'N':
                Ps[i][j] = new Knight(i, j, this, PWHITE);
                break;
            case 'n':
                Ps[i][j] = new Knight(i, j, this, PBLACK);
                break;
            case 'B':
                Ps[i][j] = new Bishop(i, j, this, PWHITE);
                break;
            case 'b':
                Ps[i][j] = new Bishop(i, j, this, PBLACK);
                break;
            case 'Q':
                Ps[i][j] = new Queen(i, j, this, PWHITE);
                break;
            case 'q':
                Ps[i][j] = new Queen(i, j, this, PBLACK);
                break;
            case 'K':
                Ps[i][j] = new King(i, j, this, PWHITE);
                break;
            case 'k':
                Ps[i][j] = new King(i, j, this, PBLACK);
                break;
            default:
                Ps[i][j] = nullptr;
                break;
            }
        }
    }
    file.close();
}

bool Board::validSource(Position S) const
{
    if ((S.ri >= 0 && S.ri < 8) && (S.ci >= 0 && S.ci < 8))
    {
        if (Ps[S.ri][S.ci] != nullptr && Ps[S.ri][S.ci]->getColour() == Turn)
            return true;
    }
    return false;
}

bool Board::validDestination(Position D) const
{
    if ((D.ri >= 0 && D.ri < 8) && (D.ci >= 0 && D.ci < 8))
    {
        if (Ps[D.ri][D.ci] == nullptr || Ps[D.ri][D.ci]->getColour() != Turn)
            return true;
    }
    return false;
}

void Board::restart() {
    init();
    load_Board();
}




bool Board::wouldLeaveKingInCheck(Position from, Position to) {
    Piece* movingPiece = Ps[from.ri][from.ci];
    if (!movingPiece) return true;

    Piece* capturedPiece = Ps[to.ri][to.ci];
    Position originalPos = movingPiece->getPos();

    // Simulate the move
    Ps[to.ri][to.ci] = movingPiece;
    Ps[from.ri][from.ci] = nullptr;
    movingPiece->setPos(to);

    bool kingInCheck = isCheck(movingPiece->getColour());

    // Undo the move
    Ps[from.ri][from.ci] = movingPiece;
    Ps[to.ri][to.ci] = capturedPiece;
    movingPiece->setPos(originalPos);

    return kingInCheck;
}





void Board::playGUI() {
    const int screenSize = 800;
    const int tileSize = screenSize / 8;

    InitWindow(screenSize, screenSize, "Chess Game");
    SetTargetFPS(60);

    bool fileLoaded = false;
    while (!fileLoaded) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Load from file? (1=Yes, 0=No)", 250, 350, 30, BLACK);
        EndDrawing();

        if (IsKeyPressed(KEY_ONE)) {
            loadFromFile();
            fileLoaded = true;
        }
        else if (IsKeyPressed(KEY_ZERO)) {
            init();
            fileLoaded = true;
        }
    }

    load_Board();

    Position S = { -1, -1 };
    Position D = { -1, -1 };
    bool selectingSource = true;
    bool sourceSelected = false;
    bool gameOver = false;
    isPromoting = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawChessBoard();

        if (isPromoting) {
            drawPromotionMenu();
            handlePromotionInput();
            EndDrawing();
            continue;
        }

        if (gameOver) {
            if (isCheckmate(PWHITE)) {
                DrawText("Black wins by checkmate!", 200, 700, 30, RED);
            }
            else if (isCheckmate(PBLACK)) {
                DrawText("White wins by checkmate!", 200, 700, 30, RED);
            }
            else {
                DrawText("Game ended in stalemate!", 200, 700, 30, RED);
            }
            DrawText("Press ESC to exit...", 200, 740, 20, DARKGRAY);

            if (IsKeyPressed(KEY_ESCAPE)) {
                break;
            }

            EndDrawing();
            continue;
        }

        // Normal in-game messages
        if (isCheck(Turn)) {
            DrawText((Turn == PWHITE ? "White is in check!" : "Black is in check!"), 100, 750, 20, RED);
        }

        DrawText((Turn == PWHITE ? "White's Turn" : "Black's Turn"), 600, 10, 20, BLACK);

        

        // AI TURN
        if (mode == HUMAN_VS_AI && Turn == PBLACK) {
            auto aiMove = getAIMove();

            if (aiMove.first.ri != -1) {
                updateBoard(aiMove.first, aiMove.second);

                Pawn* p = dynamic_cast<Pawn*>(Ps[aiMove.second.ri][aiMove.second.ci]);
                if (p && p->getColour() == PBLACK && aiMove.second.ri == 7) {
                    delete Ps[aiMove.second.ri][aiMove.second.ci];
                    Ps[aiMove.second.ri][aiMove.second.ci] = new Queen(aiMove.second.ri, aiMove.second.ci, this, PBLACK);
                }

                // Check for game end before turn changes
                if (isCheckmate(PWHITE)) {
                    gameOver = true;
                }
                else if (isStalemate(PWHITE)) {
                    gameOver = true;
                }

                if (!gameOver)
                    changeTurn();
            }
            else {
                // AI has no legal moves, check for game over
                if (isCheckmate(PBLACK)) {
                    gameOver = true;
                }
                else if (isStalemate(PBLACK)) {
                    gameOver = true;
                }
            }
        }



        // HUMAN TURN
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mousePos = GetMousePosition();
            int row = mousePos.y / tileSize;
            int col = mousePos.x / tileSize;

            Position clicked = { row, col };

            if (selectingSource) {
                if (validSource(clicked)) {
                    S = clicked;
                    sourceSelected = true;
                    selectingSource = false;
                }
            }
            else {
                D = clicked;

                if (validDestination(D) &&
                    Ps[S.ri][S.ci] &&
                    Ps[S.ri][S.ci]->isLegal(D) &&
                    (!Ps[D.ri][D.ci] || Ps[D.ri][D.ci]->getColour() != Turn) &&
                    !wouldLeaveKingInCheck(S, D)) {

                    updateBoard(S, D);

                    Pawn* p = dynamic_cast<Pawn*>(Ps[D.ri][D.ci]);
                    if (p && ((p->getColour() == PWHITE && D.ri == 0) || (p->getColour() == PBLACK && D.ri == 7))) {
                        isPromoting = true;
                        promotionPos = D;
                    }
                    else {
                        if (isCheckmate(getOpponent(Turn)) || isStalemate(getOpponent(Turn))) {
                            gameOver = true;
                        }
                        else {
                            changeTurn();
                        }
                    }
                }



                selectingSource = true;
                sourceSelected = false;
            }
        }

        if (sourceSelected) {
            Highlight(S);
        }

        EndDrawing();
    }

    CloseWindow();
}



void Board::drawPromotionMenu() {
    int menuX = promotionPos.ci * tileSize;
    int menuY = promotionPos.ri * tileSize - 100;
    if (menuY < 0) menuY = promotionPos.ri * tileSize + 100;

    DrawRectangle(menuX, menuY, tileSize, 400, LIGHTGRAY);

    // Draw promotion options
    Color color = (Turn == PWHITE) ? WHITE : BLACK;
    int yOffset = 0;

    // Queen
    DrawRectangle(menuX, menuY + yOffset, tileSize, 100, color);
    DrawText("Q", menuX + 40, menuY + yOffset + 40, 30, (color.r + color.g + color.b > 300) ? BLACK : WHITE);
    yOffset += 100;

    // Rook
    DrawRectangle(menuX, menuY + yOffset, tileSize, 100, color);
    DrawText("R", menuX + 40, menuY + yOffset + 40, 30, (color.r + color.g + color.b > 300) ? BLACK : WHITE);
    yOffset += 100;

    // Bishop
    DrawRectangle(menuX, menuY + yOffset, tileSize, 100, color);
    DrawText("B", menuX + 40, menuY + yOffset + 40, 30, (color.r + color.g + color.b > 300) ? BLACK : WHITE);
    yOffset += 100;

    // Knight
    DrawRectangle(menuX, menuY + yOffset, tileSize, 100, color);
    DrawText("N", menuX + 40, menuY + yOffset + 40, 30, (color.r + color.g + color.b > 300) ? BLACK : WHITE);
}

void Board::handlePromotionInput() {
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        Vector2 mousePos = GetMousePosition();
        int menuX = promotionPos.ci * tileSize;
        int menuY = promotionPos.ri * tileSize - 100;
        if (menuY < 0) menuY = promotionPos.ri * tileSize + 100;

        if (mousePos.x >= menuX && mousePos.x <= menuX + tileSize) {
            if (mousePos.y >= menuY && mousePos.y <= menuY + 100) {
                promotionChoice = 'Q';
            }
            else if (mousePos.y >= menuY + 100 && mousePos.y <= menuY + 200) {
                promotionChoice = 'R';
            }
            else if (mousePos.y >= menuY + 200 && mousePos.y <= menuY + 300) {
                promotionChoice = 'B';
            }
            else if (mousePos.y >= menuY + 300 && mousePos.y <= menuY + 400) {
                promotionChoice = 'N';
            }

            if (promotionChoice) {
                Piece* newPiece = nullptr;
                switch (promotionChoice) {
                case 'Q':
                    newPiece = new Queen(promotionPos.ri, promotionPos.ci, this, Turn);
                    break;
                case 'R':
                    newPiece = new Rook(promotionPos.ri, promotionPos.ci, this, Turn);
                    break;
                case 'B':
                    newPiece = new Bishop(promotionPos.ri, promotionPos.ci, this, Turn);
                    break;
                case 'N':
                    newPiece = new Knight(promotionPos.ri, promotionPos.ci, this, Turn);
                    break;
                }

                if (newPiece) {
                    delete Ps[promotionPos.ri][promotionPos.ci];
                    Ps[promotionPos.ri][promotionPos.ci] = newPiece;
                    newPiece->_loadTexture();
                }

                isPromoting = false;
                promotionChoice = '\0';
                changeTurn();
            }
        }
    }
}



void Board::move(Position S, Position D)
{
    // Handle castling first
    if (handleCastling(S, D)) {
        return;
    }

    handleEnPassant(S, D);

    // Track if kings or rooks moved
    King* k = dynamic_cast<King*>(Ps[S.ri][S.ci]);
    if (k) {
        if (k->getColour() == PWHITE) whiteKingMoved = true;
        else blackKingMoved = true;
    }

    Rook* r = dynamic_cast<Rook*>(Ps[S.ri][S.ci]);
    if (r) {
        if (r->getColour() == PWHITE) {
            if (S.ci == 7) whiteRookKingSideMoved = true;
            else if (S.ci == 0) whiteRookQueenSideMoved = true;
        }
        else {
            if (S.ci == 7) blackRookKingSideMoved = true;
            else if (S.ci == 0) blackRookQueenSideMoved = true;
        }
    }


    // Handle en passant capture
    Pawn* movingPawn = dynamic_cast<Pawn*>(Ps[S.ri][S.ci]);
    if (movingPawn && abs(D.ci - S.ci) == 1 && Ps[D.ri][D.ci] == nullptr)
    {
        Position lastMoveTo = getLastMoveTo();
        if (lastMoveTo.ri == S.ri && lastMoveTo.ci == D.ci)
        {
            Piece* adjacentPawn = Ps[S.ri][D.ci];
            if (adjacentPawn &&
                adjacentPawn->getColour() != movingPawn->getColour() &&
                dynamic_cast<Pawn*>(adjacentPawn))
            {
                Position lastMoveFrom = getLastMoveFrom();
                if (abs(lastMoveFrom.ri - lastMoveTo.ri) == 2)
                {
                    // Capture the pawn en passant
                    delete Ps[S.ri][D.ci];
                    Ps[S.ri][D.ci] = nullptr;
                }
            }
        }
    }

    // Update last move positions
    lastMoveFrom = S;
    lastMoveTo = D;

    // Move the piece
    Ps[D.ri][D.ci] = Ps[S.ri][S.ci];
    Ps[S.ri][S.ci] = nullptr;
    if (Ps[D.ri][D.ci])
    {
        Ps[D.ri][D.ci]->setPos(D);
    }
}


bool Board::handleCastling(Position S, Position D) {
    King* k = dynamic_cast<King*>(Ps[S.ri][S.ci]);
    if (!k) return false;

    int dr = D.ri - S.ri;
    int dc = D.ci - S.ci;

    // Check if this is a castling move (king moves two squares horizontally)
    if (abs(dc) == 2 && dr == 0) {
        COLOUR kingColor = k->getColour();

        // Check if king has moved
        if (hasKingMoved(kingColor)) return false;

        bool kingSide = dc > 0;

        // Check if the appropriate rook has moved
        if (hasRookMoved(kingColor, kingSide)) return false;

        // Check if squares between are empty
        int direction = kingSide ? 1 : -1;
        for (int c = S.ci + direction; c != (kingSide ? 7 : 0); c += direction) {
            if (Ps[S.ri][c] != nullptr) return false;
        }

        // Check if king would move through or into check
        Position intermediate = { S.ri, S.ci + direction };
        if (wouldLeaveKingInCheck(S, intermediate)) return false;
        if (wouldLeaveKingInCheck(S, D)) return false;

        // Perform the castling
        int rookCol = kingSide ? 7 : 0;
        int newRookCol = kingSide ? 5 : 3;

        // Move the king
        Ps[D.ri][D.ci] = Ps[S.ri][S.ci];
        Ps[S.ri][S.ci] = nullptr;
        Ps[D.ri][D.ci]->setPos(D);

        // Move the rook
        Ps[S.ri][newRookCol] = Ps[S.ri][rookCol];
        Ps[S.ri][rookCol] = nullptr;
        Ps[S.ri][newRookCol]->setPos({ S.ri, newRookCol });

        return true;
    }
    return false;
}

void Board::updateBoard(Position S, Position D)
{
    if ((Turn == PWHITE && Ps[S.ri][S.ci]->getColour() == PWHITE) || (Turn == PBLACK && Ps[S.ri][S.ci]->getColour() == PBLACK))
    {
        Ps[S.ri][S.ci]->Move(D);
        move(S, D);
        displayBoard();
    }
}

void Board::displayBoard()
{
    system("cls");
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Ps[i][j] == nullptr)
                cout << "-";
            else
                Ps[i][j]->Draw();
        }
        cout << endl;
    }
}

void Board::unHighlight()
{
    displayBoard();
}

Piece* Board::pieceAt(Position P)
{
    return Ps[P.ri][P.ci];
}

void Board::changeTurn()
{
    if (Turn == PBLACK)
    {
        Turn = PWHITE;
    }
    else
    {
        Turn = PBLACK;
    }
    enPassantPossible = false;
}

Board::~Board()
{
}

void Board::Highlight(Position S)
{
    if (Ps[S.ri][S.ci] == nullptr)
        return;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (validDestination({ i,j }) && Ps[S.ri][S.ci]->isLegal({ i,j }))
            {
                DrawRectangle(j * 100, i * 100, 100, 100, ColorAlpha(YELLOW, 0.3f));
            }
        }
        cout << endl;
    }
}

void Board::copyBoard(Board& CP)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            King* K = dynamic_cast<King*>(Ps[i][j]);
            Queen* Q = dynamic_cast<Queen*>(Ps[i][j]);
            Rook* R = dynamic_cast<Rook*>(Ps[i][j]);
            Bishop* B = dynamic_cast<Bishop*>(Ps[i][j]);
            Knight* N = dynamic_cast<Knight*>(Ps[i][j]);
            Pawn* P = dynamic_cast<Pawn*>(Ps[i][j]);

            if (K)
            {
                CP.Ps[i][j] = new King(i, j, &CP, K->getColour());
            }
            else if (Q)
            {
                CP.Ps[i][j] = new Queen(i, j, &CP, Q->getColour());
            }
            else if (R)
            {
                CP.Ps[i][j] = new Rook(i, j, &CP, R->getColour());
            }
            else if (B)
            {
                CP.Ps[i][j] = new Bishop(i, j, &CP, B->getColour());
            }
            else if (N)
            {
                CP.Ps[i][j] = new Knight(i, j, &CP, N->getColour());
            }
            else if (P)
            {
                CP.Ps[i][j] = new Pawn(i, j, &CP, P->getColour());
            }
            else
            {
                CP.Ps[i][j] = nullptr;
            }
        }
    }
    CP.Turn = this->Turn;
}

void Board::PawnPromotion()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (Ps[i][j] != nullptr) {
                Pawn* p = dynamic_cast<Pawn*>(Ps[i][j]);
                if (p != nullptr) {
                    if ((p->getColour() == PWHITE && i == 0) || (p->getColour() == PBLACK && i == 7)) {
                        char choice;
                        cout << "Pawn promotion! Choose a piece (Q,R,B,N): ";
                        cin >> choice;

                        Piece* newPiece = nullptr;
                        switch (toupper(choice)) {
                        case 'Q':
                            newPiece = new Queen(i, j, this, p->getColour());
                            break;
                        case 'R':
                            newPiece = new Rook(i, j, this, p->getColour());
                            break;
                        case 'B':
                            newPiece = new Bishop(i, j, this, p->getColour());
                            break;
                        case 'N':
                            newPiece = new Knight(i, j, this, p->getColour());
                            break;
                        default:
                            newPiece = new Queen(i, j, this, p->getColour());
                            break;
                        }
                        delete Ps[i][j];
                        Ps[i][j] = newPiece;
                        displayBoard();
                    }
                }
            }
        }
    }
}

Position Board::findKing(COLOUR kingColor)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Ps[i][j] != nullptr && Ps[i][j]->getColour() == kingColor)
            {
                King* k = dynamic_cast<King*>(Ps[i][j]);
                if (k != nullptr)
                {
                    return { i,j };
                }
            }
        }
    }
    return { -1,-1 };
}

bool Board::isCheck(COLOUR kingColor)
{
    Position kingPos = findKing(kingColor);
    if (kingPos.ri == -1) return false;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (Ps[i][j] != nullptr && Ps[i][j]->getColour() != kingColor)
            {
                if (Ps[i][j]->isLegal(kingPos))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::hasLegalMoves(COLOUR playerColor)
{
    Position kingPos = findKing(playerColor);
    if (kingPos.ri == -1) return false;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Position from = { i, j };
            Piece* piece = Ps[i][j];

            if (!piece || piece->getColour() != playerColor)
                continue;

            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    Position to = { x, y };

                    if (!validDestination(to) || !piece->isLegal(to))
                        continue;

                    if (from.ri == to.ri && from.ci == to.ci)
                        continue;

                    Piece* originalDest = Ps[to.ri][to.ci];
                    Position originalPos = piece->getPos();

                    Ps[to.ri][to.ci] = piece;
                    Ps[from.ri][from.ci] = nullptr;
                    piece->setPos(to);

                    bool inCheck = isCheck(playerColor);

                    Ps[from.ri][from.ci] = piece;
                    Ps[to.ri][to.ci] = originalDest;
                    piece->setPos(originalPos);

                    if (!inCheck) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Board::isCheckmate(COLOUR kingColor)
{
    bool check = false, lm = false;
    if (isCheck(kingColor))
    {
        check = true;
    }
    if (!hasLegalMoves(kingColor))
    {
        lm = true;
    }

    return check && lm;
}

bool Board::isStalemate(COLOUR playerColor)
{
    return isCheck(playerColor) && !hasLegalMoves(playerColor);
}

void Board::handleEnPassant(Position S, Position D)
{
    Pawn* movingPawn = dynamic_cast<Pawn*>(Ps[S.ri][S.ci]);
    if (!movingPawn) return;

    // Check if this is a two-square pawn move
    if (abs(D.ri - S.ri) == 2)
    {
        enPassantPossible = true;
        return;
    }

    // Check for en passant capture
    if (abs(D.ci - S.ci) == 1 && Ps[D.ri][D.ci] == nullptr)
    {
        int direction = (movingPawn->getColour() == PWHITE) ? -1 : 1;
        Position adjacentPos = { D.ri - direction, D.ci };
        Pawn* adjacentPawn = dynamic_cast<Pawn*>(Ps[adjacentPos.ri][adjacentPos.ci]);

        if (adjacentPawn && adjacentPawn->getColour() != movingPawn->getColour())
        {
            // Check if the adjacent pawn just moved two squares
            if (lastMoveTo.ri == adjacentPos.ri && lastMoveTo.ci == adjacentPos.ci &&
                abs(lastMoveFrom.ri - lastMoveTo.ri) == 2)
            {
                // Capture the pawn en passant
                delete Ps[adjacentPos.ri][adjacentPos.ci];
                Ps[adjacentPos.ri][adjacentPos.ci] = nullptr;
            }
        }
    }
}







pair<Position, Position> Board::getAIMove() {
    std::vector<std::pair<std::pair<Position, Position>, int>> scoredMoves;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = Ps[i][j];
            if (piece && piece->getColour() == PBLACK) {
                Position from = { i, j };

                for (int x = 0; x < 8; ++x) {
                    for (int y = 0; y < 8; ++y) {
                        Position to = { x, y };
                        Piece* target = Ps[x][y];

                        if (target && target->getColour() == piece->getColour()) continue;
                        if (piece->isLegal(to) && !wouldLeaveKingInCheck(from, to)) {
                            int score = 0;

                            // Score for capturing
                            if (target)
                                score += getPieceValue(target);

                            //  Bonus if move gives check
                            if (wouldGiveCheck(from, to))
                                score += 50;

                            //  Bonus for moving toward center (control)
                            if (x >= 2 && x <= 5 && y >= 2 && y <= 5)
                                score += 5;

                            scoredMoves.push_back({ {from, to}, score });
                        }
                    }
                }
            }
        }
    }

    if (scoredMoves.empty())
        return { {-1, -1}, {-1, -1} };

    // Find move with highest score
    auto bestMove = scoredMoves[0];
    for (auto& move : scoredMoves) {
        if (move.second > bestMove.second)
            bestMove = move;
    }

    return bestMove.first;
}




int Board::getPieceValue(Piece* p) {
    if (dynamic_cast<Queen*>(p))   return 90;
    if (dynamic_cast<Rook*>(p))    return 50;
    if (dynamic_cast<Bishop*>(p))  return 30;
    if (dynamic_cast<Knight*>(p))  return 30;
    if (dynamic_cast<Pawn*>(p))    return 10;
    if (dynamic_cast<King*>(p))    return 1000; // only for check detection, not capture
    return 0;
}

bool Board::wouldGiveCheck(Position from, Position to) {
    // Simulate move
    Piece* movingPiece = Ps[from.ri][from.ci];
    Piece* captured = Ps[to.ri][to.ci];

    Ps[to.ri][to.ci] = movingPiece;
    Ps[from.ri][from.ci] = nullptr;
    Position origPos = movingPiece->getPos();
    movingPiece->setPos(to);

    bool givesCheck = isCheck(PWHITE); // Check if AI puts white in check

    // Undo move
    movingPiece->setPos(origPos);
    Ps[from.ri][from.ci] = movingPiece;
    Ps[to.ri][to.ci] = captured;

    return givesCheck;
}
