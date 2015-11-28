#include <iostream>
#include "GameBoard.h"
#include "Players/RandomPlayer.h"

using namespace std;

static const size_t DEFAULT_GAME_SIZE = 8;

int main() {
    GameBoard gameBoard(DEFAULT_GAME_SIZE);
    gameBoard.print(std::cerr);
    RandomPlayer player(BLACK);
    for (int i = 0; i < 4; i++) {
        gameBoard.putTile(player.takeTurn(gameBoard), BLACK);
    }
    return 0;
}