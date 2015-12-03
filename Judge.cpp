#include <chrono>
#include "Judge.h"
#include <assert.h>

Score Judge::playGame() {
    GameBoard gameBoard(GameBoard::DEFAULT_GAME_SIZE);
    currentPlayer = playerBlack;
    int noMoveCount = 0;
    std::chrono::milliseconds averageTimePlayerWhite(0);
    std::chrono::milliseconds averageTimePlayerBlack(0);
    int turnsCount = 0;
    while (!gameBoard.isGameOver() && noMoveCount < 2) {
        ++turnsCount;
        auto startTime = std::chrono::steady_clock::now();
        Cell move = currentPlayer->takeTurn(gameBoard);
        auto endTime = std::chrono::steady_clock::now();
        std::chrono::milliseconds workTime = std::chrono::milliseconds(
                std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime));
        assert(workTime.count() < 3000);
        if (gameBoard.canPutTile(move, currentPlayer->getMyTile())) {
            gameBoard.putTile(move, currentPlayer->getMyTile());
            noMoveCount = 0;
//            gameBoard.print(std::cerr);
        } else {
            ++noMoveCount;
        }

        if (currentPlayer == playerBlack) {
            currentPlayer = playerWhite;
            averageTimePlayerBlack += workTime;
        } else {
            currentPlayer = playerBlack;
            averageTimePlayerWhite += workTime;
        }
    }
    turnsCount /= 2;
    auto score = gameBoard.calculateScore();
    std::cerr << score.whiteTiles << ' ' << score.blackTiles << '\n';
    std::cerr << "White average " << averageTimePlayerWhite.count() / turnsCount << "ms.\n";
    std::cerr << "Black average " << averageTimePlayerBlack.count() / turnsCount << "ms.\n";
    return score;
}

Score Judge::playTournament(size_t gameNumber) {
    Score globalScore;
    for (size_t i = 0; i < gameNumber; ++i) {
        auto score = playGame();
        if (score.whoWins() == WHITE) {
            ++globalScore.whiteTiles;
        }
        if (score.whoWins() == BLACK) {
            ++globalScore.blackTiles;
        }
    }
    std::cerr << globalScore.whiteTiles << ' ' << globalScore.blackTiles << '\n';
    return globalScore;
}
