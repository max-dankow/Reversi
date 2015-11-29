#ifndef REVERSI_RANDOMPLAYER_H
#define REVERSI_RANDOMPLAYER_H

#include "IPlayer.h"

class RandomPlayer : public IPlayer {
public:
    RandomPlayer(Tile tile) : IPlayer(tile) { }

    virtual Cell takeTurn(const GameBoard gameBoard);

private:
};


#endif //REVERSI_RANDOMPLAYER_H
