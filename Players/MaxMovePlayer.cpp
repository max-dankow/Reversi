#include "MaxMovePlayer.h"
#include <random>

//static std::random_device randomDevice;
static std::default_random_engine randomGenerator/*(randomDevice())*/;

Cell MaxMovePlayer::takeTurn(const GameBoard &gameBoard) {
    int maxTurnedOver = 0;
    Cell maxMove;
    std::uniform_int_distribution<int> coin(0, 1);
    for (size_t row = 0; row < gameBoard.getGameSize(); ++row) {
        for (size_t column = 0; column < gameBoard.getGameSize(); ++column) {
            Cell here(row, column);
            int turnedOver = gameBoard.countTurnedOver(here, myTile);
            if (turnedOver > maxTurnedOver
                || (turnedOver == maxTurnedOver && coin(randomGenerator) == 1)) {
                maxMove = here;
                maxTurnedOver = turnedOver;
            }
        }
    }
    if (maxTurnedOver == 0) {
        return Cell(-1, -1);
    }
    return maxMove;
}
