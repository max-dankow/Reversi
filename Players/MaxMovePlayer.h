#ifndef REVERSI_MAXMOVEPLAYER_H
#define REVERSI_MAXMOVEPLAYER_H

#include "IPlayer.h"

class MaxMovePlayer : public IPlayer {
public:
    MaxMovePlayer(Tile tile) : IPlayer(tile) { }

    virtual Cell takeTurn(const GameBoard &gameBoard);

private:
};


#endif //REVERSI_MAXMOVEPLAYER_H
