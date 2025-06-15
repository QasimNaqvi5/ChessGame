
#include "Board.h"
#include "Peice.h"
#include"raylib.h"

int main() {
    int choice;
    std::cout << "Select Game Mode:\n1. Human vs Human\n2. Human vs AI\nEnter choice: ";
    std::cin >> choice;

    GameMode mode = (choice == 2) ? HUMAN_VS_AI : HUMAN_VS_HUMAN;

    Board b;
    b.setGameMode(mode);
    b.playGUI();

    return 0;
}
