#include "Judge.h"

Score Judge::playGame() {
    GameBoard gameBoard(GameBoard::DEFAULT_GAME_SIZE);
    currentPlayer = playerBlack;
    int noMoveCount = 0;
    while (!gameBoard.isGameOver() && noMoveCount < 2) {
        Cell move = currentPlayer->takeTurn(gameBoard);

        if (gameBoard.canPutTile(move, currentPlayer->getMyTile())) {
            gameBoard.putTile(move, currentPlayer->getMyTile());
            noMoveCount = 0;

//            gameBoard.print(std::cerr);
        } else {
            ++noMoveCount;
        }

        if (currentPlayer == playerBlack) {
            currentPlayer = playerWhite;
        } else {
            currentPlayer = playerBlack;
        }
    }
    if (noMoveCount >= 2) {
        gameBoard.print(std::cerr);
    }
    auto score = gameBoard.calculateScore();
    std::cerr << score.whiteTiles << ' ' << score.blackTiles << '\n';
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
