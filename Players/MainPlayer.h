#ifndef REVERSI_MAINPLAYER_H
#define REVERSI_MAINPLAYER_H

#include <assert.h>
#include "IPlayer.h"

struct Move {
    Move(Cell cell = {0, 0}, long whitePriority = 0, long blackPriority = 0) :
            cell(cell),
            whitePriority(whitePriority),
            blackPriority(blackPriority) { }

    long getPriority(Tile tile) {
        if (tile == WHITE) {
            return whitePriority;
        }
        if (tile == BLACK) {
            return blackPriority;
        }
        assert(false);
    }

    Cell cell;
    long whitePriority, blackPriority;
};

class MainPlayer : public IPlayer {
public:
    MainPlayer(Tile tile) : IPlayer(tile) { }

    virtual Cell takeTurn(const GameBoard &gameBoard);

private:
    Move recursion(const GameBoard &gameBoard, Tile tile, size_t depth, size_t maxDepth) const;

    long evaluateGameBoard(const GameBoard &gameBoard, Tile tile) const;

};


#endif //REVERSI_MAINPLAYER_H
