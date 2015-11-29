#ifndef REVERSI_JUDGE_H
#define REVERSI_JUDGE_H

#include <memory>
#include "Players/IPlayer.h"

class Judge {
public:
    explicit Judge(std::shared_ptr<IPlayer> playerWhite,
                   std::shared_ptr<IPlayer> playerBlack) :
            playerWhite(playerWhite),
            playerBlack(playerBlack) { }

    Score playGame();

    Score playTournament(size_t gameNumber);

private:
    std::shared_ptr<IPlayer> playerWhite, playerBlack;
    std::shared_ptr<IPlayer> currentPlayer;
};


#endif //REVERSI_JUDGE_H