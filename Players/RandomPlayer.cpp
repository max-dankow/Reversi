#include "RandomPlayer.h"
#include <random>

static std::random_device randomDevice;
static std::default_random_engine randomGenerator(randomDevice());

Cell RandomPlayer::takeTurn(const GameBoard gameBoard) {
    std::vector<Cell> availableTurns;
    for (size_t row = 0; row < gameBoard.getGameSize(); ++row) {
        for (size_t column = 0; column < gameBoard.getGameSize(); ++column) {
            Cell here(row, column);
            if (gameBoard.canPutTile(here, myTile)) {
                availableTurns.push_back(here);
            }
        }
    }
    if (availableTurns.size() == 0) {
        return Cell(-1, -1);
    }
    std::uniform_int_distribution<size_t> selectRandom(0, availableTurns.size() - 1);
    return availableTurns[selectRandom(randomGenerator)];;
}
