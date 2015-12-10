#ifndef REVERSI_MAINPLAYER_H
#define REVERSI_MAINPLAYER_H

#include <assert.h>
#include "IPlayer.h"
#include <chrono>

enum GamePhase {
    GAME_BEGIN,
    GAME_MIDDLE,
    GAME_PREEND,
    GAME_END
};

//static std::random_device randomDevice;
//static std::default_random_engine randomGenerator/*(randomDevice())*/;

struct Move {
    Move(Cell cell = {0, 0}, long score = 0) :
            cell(cell),
            score(score) { }


    /*Move(Cell cell = {0, 0}, long whitePriority = 0, long blackPriority = 0) :
            cell(cell),
            whitePriority(whitePriority),
            blackPriority(blackPriority) { }

    long getPriority(Tile tile) const {
        if (tile == WHITE) {
            return whitePriority;
        }
        if (tile == BLACK) {
            return blackPriority;
        }
        assert(false);
    }

    bool isBetterForThan(Tile tile, const Move &other) {
        auto enemyTile = getEnemyTile(tile);
        return (this->getPriority(tile) - this->getPriority(enemyTile)
                > other.getPriority(tile) - other.getPriority(enemyTile));
    }*/

    Cell cell;
    //long whitePriority, blackPriority;
    long score;
};

class MainPlayer : public IPlayer {
public:
    MainPlayer(Tile tile) : IPlayer(tile) { }

    virtual Cell takeTurn(const GameBoard &gameBoard);

private:
    Move recursion(const GameBoard &gameBoard, Tile tile, size_t depth, size_t maxDepth, long alpha, long beta) const;

    long evaluateGameBoard(const GameBoard &gameBoard, Tile tile) const;

    long mobilityHeuristic(const GameBoard &gameBoard, Tile tile) const;

    long potentialMobilityHeuristic(const GameBoard &gameBoard, Tile tile);

    long edgeStabilityHeuristic(const GameBoard &gameBoard, Tile tile) const;

    GamePhase getGamePhase(const GameBoard &gameBoard);

    std::chrono::time_point<std::chrono::system_clock> startWorking;

    GamePhase gamePhase;
};


#endif //REVERSI_MAINPLAYER_H
