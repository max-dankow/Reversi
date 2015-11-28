#include <iostream>
#include "GameBoard.h"

using namespace std;

static const size_t DEFAULT_GAME_SIZE = 8;

int main() {
    GameBoard gameBoard(DEFAULT_GAME_SIZE);
    gameBoard.print(std::cerr);
    return 0;
}