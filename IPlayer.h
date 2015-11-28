#ifndef REVERSI_IPLAYER_H
#define REVERSI_IPLAYER_H

#include "GameBoard.h"

class IPlayer {
    virtual Cell takeTurn(const GameBoard gameBoard) = 0;
};


#endif //REVERSI_IPLAYER_H
