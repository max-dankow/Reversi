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
    judge.playTournament(100);
    return 0;
}