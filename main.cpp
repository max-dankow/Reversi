#include <iostream>
#include <memory>
#include "GameBoard.h"
#include "Players/IPlayer.h"
#include "Players/MainPlayer.h"

int main() {
    MainPlayer mainPlayer(BLACK);
    mainPlayer.play(std::cin, std::cout);
//    std::shared_ptr<IPlayer> randomPlayerBlack(new MaxMovePlayer(BLACK));
//    std::shared_ptr<IPlayer> randomPlayerWhite(new MainPlayer(WHITE));
//    Judge judge(randomPlayerWhite, randomPlayerBlack);
//    Direction direction(0, 0);
//    judge.playGame();
//    judge.playTournament(100);
    return 0;
}