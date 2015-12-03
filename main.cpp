#include <iostream>
#include <memory>
#include "GameBoard.h"
#include "Players/IPlayer.h"
#include "Players/MaxMovePlayer.h"
#include "Players/MainPlayer.h"
#include "Judge.h"

int main() {
    std::shared_ptr<IPlayer> randomPlayerBlack(new MaxMovePlayer(BLACK));
    std::shared_ptr<IPlayer> randomPlayerWhite(new MainPlayer(WHITE));
    Judge judge(randomPlayerWhite, randomPlayerBlack);
    Direction direction(0, 0);
    std::cerr << sizeof direction << '\n';
//    judge.playGame();
    judge.playTournament(100);
    return 0;
}