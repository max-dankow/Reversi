#include <iostream>
#include "GameBoard.h"

using namespace std;

static const size_t DEFAULT_GAME_SIZE = 8;

int main() {
    GameBoard gameBoard(DEFAULT_GAME_SIZE);
    gameBoard.putTile(4, 2, WHITE);
    gameBoard.putTile(5, 2, BLACK);
    gameBoard.putTile(3, 2, BLACK);
    gameBoard.putTile(4, 1, WHITE);
    return 0;
}