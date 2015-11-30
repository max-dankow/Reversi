#ifndef REVERSI_IPLAYER_H
#define REVERSI_IPLAYER_H

#include "../GameBoard.h"

class IPlayer {
public:
    IPlayer(Tile tile) : myTile(tile) { }

    virtual Cell takeTurn(const GameBoard &gameBoard) = 0;

    void play(std::istream &input, std::ostream &output);

    const Tile &getMyTile() const {
        return myTile;
    }
protected:
    Tile myTile;
};


#endif //REVERSI_IPLAYER_H
