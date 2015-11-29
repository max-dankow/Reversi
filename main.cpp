#include <iostream>
#include <memory>
#include "GameBoard.h"
#include "Players/RandomPlayer.h"

int main() {
    std::shared_ptr<IPlayer> randomPlayerBlack(new RandomPlayer(BLACK));
    randomPlayerBlack->play(std::cin, std::cout);
//    std::shared_ptr<IPlayer> randomPlayerWhite(new MaxMovePlayer(WHITE));
//    Judge judge(randomPlayerWhite, randomPlayerBlack);
//    judge.playTournament(1000);
//    GameBoard gameBoard(DEFAULT_GAME_SIZE);
//    gameBoard.print(std::cerr);
//    RandomPlayer player(BLACK);
//    for (int i = 0; i < 4; i++) {
//        gameBoard.putTile(player.takeTurn(gameBoard), BLACK);
//    }
    return 0;
}