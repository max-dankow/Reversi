#include <iostream>
#include <memory>
#include "GameBoard.h"
#include "Players/RandomPlayer.h"
#include "Players/MaxMovePlayer.h"
#include "Judge.h"

int main() {
    std::shared_ptr<IPlayer> randomPlayerBlack(new RandomPlayer(BLACK));
    std::shared_ptr<IPlayer> randomPlayerWhite(new MaxMovePlayer(WHITE));
    Judge judge(randomPlayerWhite, randomPlayerBlack);
    judge.playTournament(1);
//    GameBoard gameBoard(DEFAULT_GAME_SIZE);
//    gameBoard.print(std::cerr);
//    RandomPlayer player(BLACK);
//    for (int i = 0; i < 4; i++) {
//        gameBoard.putTile(player.takeTurn(gameBoard), BLACK);
//    }
    return 0;
}