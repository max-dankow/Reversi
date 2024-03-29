#ifndef REVERSI_GAMEBOARD_H
#define REVERSI_GAMEBOARD_H

#include <vector>
#include <iostream>
#include <assert.h>

enum Tile {
    EMPTY,
    WHITE,
    BLACK
};

static Tile getEnemyTile(Tile tile) {
    Tile enemyTile;
    switch (tile) {
        case WHITE:
            enemyTile = BLACK;
            break;
        case BLACK:
            enemyTile = WHITE;
            break;
        default:
            assert(false);
    }
    return enemyTile;
}

struct Direction {

    Direction(int offsetRow = 0, int offsetCol = 0) :
            offsetRow(offsetRow), offsetCol(offsetCol) { }

    Direction getOpposite() const {
        return Direction(this->offsetRow * -1, this->offsetCol * -1);
    }

    static Direction getDirectionUp() {
        return Direction(-1, 0);
    }

    static Direction getDirectionDown() {
        return Direction(1, 0);
    }

    static Direction getDirectionLeft() {
        return Direction(0, -1);
    }

    static Direction getDirectionRight() {
        return Direction(0, 1);
    }

    int offsetRow, offsetCol;
};

struct Cell {
    Cell(size_t row, size_t column) : row((int) row), column((int) column) { }

    Cell() { }

    void move(const Direction &direction) {
        row += direction.offsetRow;
        column += direction.offsetCol;
    }

    void print(std::ostream &output) {
        output << char('a' + column) << ' ' << row + 1 << '\n';
    }

    void read(std::istream &input) {
        char a;
        input >> a >> row;
        --row;
        column = int(a - 'a');
    }

    int row, column;
};

struct Score {
    Score(int whiteTiles = 0, int blackTiles = 0) :
            whiteTiles(whiteTiles),
            blackTiles(blackTiles) { }

    Tile whoWins() {
        if (whiteTiles > blackTiles) {
            return WHITE;
        }
        if (whiteTiles < blackTiles) {
            return BLACK;
        }
        return EMPTY;
    }

    long playersScore(Tile tile) {
        if (tile == WHITE) {
            return whiteTiles;
        }
        if (tile == BLACK) {
            return blackTiles;
        }
        assert(false);
    }

    int whiteTiles, blackTiles;
};

class GameBoard {
public:
    static const size_t DEFAULT_GAME_SIZE = 8;

    explicit GameBoard(size_t gameSize);

    size_t getGameSize() const;

    void print(std::ostream &output) const;

    Tile getAt(const Cell cell) const;

    Tile getAt(size_t row, size_t column) const;

    void setAt(const Cell &cell, const Tile &tile);

    void setAt(size_t row, size_t column, const Tile &tile);

    int countTurnedOver(const Cell &cell, const Tile &tile) const;

    bool canPutTile(const Cell &cell, const Tile &tile) const;

    void putTile(const Cell &cell, const Tile &tile);

    Tile getEnemyTile(Tile tile) const;

    bool isGameOver() const;

    bool isGameOverFor(Tile tile) const;

    Tile whoWins() const;

    Score calculateScore() const;

    size_t getEmptyCount() const;

    bool isCorrect(const Cell cell) const;

private:
    size_t getIndex(const Cell cell) const;

    int goThroughTiles(const Cell &startCell, Direction direction, Tile tile, Tile replacer);

    int lookThroughTiles(const Cell &startCell, const Direction &direction, Tile tile) const;

    size_t gameSize, emptyCount;
    std::vector<Tile> field;
};

inline size_t GameBoard::getEmptyCount() const {
    return emptyCount;
}

inline size_t GameBoard::getGameSize() const {
    return gameSize;
}


#endif //REVERSI_GAMEBOARD_H
