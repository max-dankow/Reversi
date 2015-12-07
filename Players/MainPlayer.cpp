#include <random>
#include "MainPlayer.h"

Cell MainPlayer::takeTurn(const GameBoard &gameBoard) {
    gamePhase = getGamePhase(gameBoard);
    int maxDepth = 5;
    if (gamePhase == GAME_END) {
        maxDepth = 13;
    }
    startWorking = std::chrono::system_clock::now();
    return recursion(gameBoard, myTile, 0, maxDepth).cell;
}

Move MainPlayer::recursion(const GameBoard &gameBoard, Tile tile,
                           size_t depth, size_t maxDepth) const {
//    gameBoard.print(std::cerr);
    auto now = std::chrono::steady_clock::now();
    std::chrono::time_point<std::chrono::system_clock> nowTime;
    nowTime = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = nowTime - startWorking;
    /*if (elapsed_seconds.count() > 2.7) {
        std::cerr << "TL\n";
    }*/
    if (depth > maxDepth || gameBoard.isGameOver() || elapsed_seconds.count() > 2.7) {
        Move stop({0, 0},
                  evaluateGameBoard(gameBoard, WHITE),
                  evaluateGameBoard(gameBoard, BLACK));
        return stop;
    }
    auto enemyTile = gameBoard.getEnemyTile(tile);
    auto gameSize = gameBoard.getGameSize();
    std::bernoulli_distribution coin(0.5);
//    randomGenerator.seed(time(NULL));
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
                if (first || current.isBetterForThan(tile, max)) {
                    max = current;
                    max.cell = here;
                    first = false;
                }
            }
        }
    }
    // У текущего игрока нет ходов. Пропуск хода.
    if (first) {
        return recursion(gameBoard, enemyTile, depth, maxDepth);
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
    if (gameBoard.getEmptyCount() < 10) {
        edgeStabilityHeuristic(gameBoard, tile);
    }

    if (gameBoard.isGameOver()) {
        Score score = gameBoard.calculateScore();
        if (gameBoard.whoWins() == tile) {
            return 77777 + score.playersScore(tile) * 100;
        }
        if (gameBoard.whoWins() == enemyTile) {
            return -77777 - score.playersScore(enemyTile) * 100;
        }
    }

    long cornerValue = 0;
    for (size_t row = 0; row < gameSize; ++row) {
        for (size_t column = 0; column < gameSize; ++column) {
            if (gameBoard.getAt(row, column) == tile) {
                cornerValue += worth[row][column];
            }
        }
    }
    if (gamePhase == GAME_BEGIN) {
        value = (long) (cornerValue * 2 + 1 * mobilityHeuristic(gameBoard, tile) +
                        edgeStabilityHeuristic(gameBoard, tile) * 0.5);
    }
    if (gamePhase == GAME_MIDDLE) {
        value = cornerValue * 2 + mobilityHeuristic(gameBoard, tile) + edgeStabilityHeuristic(gameBoard, tile);
    }
    if (gamePhase == GAME_PREEND || gamePhase == GAME_END) {
        value = (long) (cornerValue + 0.5 * mobilityHeuristic(gameBoard, tile) +
                        edgeStabilityHeuristic(gameBoard, tile) * 1.5);
    }
    return value;
}


long MainPlayer::mobilityHeuristic(const GameBoard &gameBoard, Tile tile) const {
    long mobility = 0;
    auto gameSize = gameBoard.getGameSize();
    for (size_t row = 0; row < gameSize; ++row) {
        for (size_t column = 0; column < gameSize; ++column) {
            Cell here(row, column);
            if (gameBoard.canPutTile(here, tile)) {
                ++mobility;
            }
        }
    }
    /*gameBoard.print(std::cerr);
    std::cerr << mobility << '\n';*/
    return mobility;
}

long MainPlayer::potentialMobilityHeuristic(const GameBoard &gameBoard, Tile tile) {
    long potentialMobility = 0;
    auto gameSize = gameBoard.getGameSize();
    auto enemyTile = gameBoard.getEnemyTile(tile);

    for (size_t row = 0; row < gameSize; ++row) {
        for (size_t column = 0; column < gameSize; ++column) {
            Cell here(row, column);
            if (gameBoard.getAt(here) != tile) {
                continue;
            }
            for (int offsetRow = -1; offsetRow < 2; ++offsetRow) {
                for (int offsetCol = -1; offsetCol < 2; ++offsetCol) {
                    if (offsetCol == 0 && offsetRow == 0) {
                        continue;
                    }
                    Direction direction(offsetRow, offsetCol);
                    auto neighbor = here;
                    neighbor.move(direction);
                    if (gameBoard.isCorrect(neighbor)
                        && gameBoard.getAt(neighbor) == enemyTile) {
                        ++potentialMobility;
                    }
                }
            }
        }
    }
    return potentialMobility;
}

long MainPlayer::edgeStabilityHeuristic(const GameBoard &gameBoard, Tile tile) const {
    auto gameSize = gameBoard.getGameSize();
    std::vector<Direction> directions{{0,  1},
                                      {0,  -1},
                                      {1,  0},
                                      {-1, 0}};

    std::vector<Cell> corners{{0,            0},
                              {0,            gameSize - 1},
                              {gameSize - 1, 0},
                              {gameSize - 1, gameSize - 1}};
    auto board = gameBoard;
//    board.print(std::cerr);
    long stableCellsCount = 0;
    for (Cell corner : corners) {
        if (board.getAt(corner) != tile) {
            continue;
        }
        ++stableCellsCount;
        for (Direction direction : directions) {
            auto current = corner;
            current.move(direction);
            while (board.isCorrect(current) && board.getAt(current) == tile) {
                ++stableCellsCount;
                board.setAt(current, EMPTY);
//                board.print(std::cerr);
                current.move(direction);
            }
        }
    }
    return stableCellsCount;
}

GamePhase MainPlayer::getGamePhase(const GameBoard &gameBoard) {
    if (gameBoard.getEmptyCount() > 44) {
        return GAME_BEGIN;
    }
    if (gameBoard.getEmptyCount() < 12) {
        return GAME_END;
    }
    if (gameBoard.getEmptyCount() < 20) {
        return GAME_PREEND;
    }
    return GAME_MIDDLE;
}
