#include "MainPlayer.h"

Cell MainPlayer::takeTurn(const GameBoard &gameBoard) {
    int maxDepth = 2;
    if (gameBoard.getEmptyCount() < 10) {
        maxDepth = 5;
    }
    return recursion(gameBoard, myTile, 0, maxDepth).cell;
}

Move MainPlayer::recursion(const GameBoard &gameBoard, Tile tile,
                           size_t depth, size_t maxDepth) const {
//    gameBoard.print(std::cerr);
    if (depth > maxDepth) {
        Move stop({0, 0},
                  evaluateGameBoard(gameBoard, WHITE),
                  evaluateGameBoard(gameBoard, BLACK));
        return stop;
    }
    auto enemyTile = gameBoard.getEnemyTile(tile);
    auto gameSize = gameBoard.getGameSize();
    Move current, max;
    bool first = true;
    for (size_t row = 0; row < gameSize; ++row) {
        for (size_t column = 0; column < gameSize; ++column) {
            Cell here(row, column);
            if (gameBoard.canPutTile(here, tile)) {
                GameBoard newGameBoard = gameBoard;
                newGameBoard.putTile(here, tile);
//                newGameBoard.print(std::cerr);
                current = recursion(newGameBoard, enemyTile, depth + 1, maxDepth);
                if (first ||
                    current.getPriority(tile) - current.getPriority(enemyTile) / 2
                    > max.getPriority(tile) - max.getPriority(enemyTile) / 2) {
                    max = current;
                    max.cell = here;
                    first = false;
                }
            }
        }
    }
    return max;
}

static const std::vector<std::vector<long>> worth =
        {{99, -8,  8,  6,  6,  8,  -8,  99},
         {-8, -24, -4, -3, -3, -4, -24, -8},
         {8,  -4,  7,  4,  4,  7,  -4,  8},
         {6,  -3,  4,  0,  0,  4,  -3,  6},
         {6,  -3,  4,  0,  0,  4,  -3,  6},
         {8,  -4,  7,  4,  4,  7,  -4,  8},
         {-8, -24, -4, -3, -3, -4, -24, -8},
         {99, -8,  8,  6,  6,  8,  -8,  99}};

long MainPlayer::evaluateGameBoard(const GameBoard &gameBoard, Tile tile) const {
    long value = 0;
    auto gameSize = gameBoard.getGameSize();
    auto enemyTile = gameBoard.getEnemyTile(tile);
//    if (gameBoard.isGameOver()) {
//        if (gameBoard.whoWins() == tile) {
//            return 77777;
//        }
//        if (gameBoard.whoWins() == enemyTile) {
//            return -77777;
//        }
//        return -1000;
//    }
    for (size_t row = 0; row < gameSize; ++row) {
        for (size_t column = 0; column < gameSize; ++column) {
            if (gameBoard.getAt(row, column) == tile) {
                value += worth[row][column];
            }
        }
    }
    return value;
}