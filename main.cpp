#include <iostream>
#include <memory>
#include "GameBoard.h"
#include "Players/IPlayer.h"
#include "Players/MainPlayer.h"

int main() {
    MainPlayer player(BLACK);
    player.play(std::cin, std::cout);
    /*std::shared_ptr<IPlayer> randomPlayerBlack(new RandomPlayer(BLACK));
    std::shared_ptr<IPlayer> randomPlayerWhite(new MainPlayer(WHITE));
    Judge judge(randomPlayerWhite, randomPlayerBlack);
    judge.playGame();*/
    //judge.playTournament(100);
    return 0;
}
