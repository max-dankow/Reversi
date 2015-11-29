#ifndef REVERSI_GAMEBOARD_H
#define REVERSI_GAMEBOARD_H

#include <vector>
#include <iostream>

enum Tile {
    EMPTY,
    WHITE,
    BLACK
};

struct Direction {
    Direction(int offsetRow, int offsetCol) :
            offsetRow(offsetRow), offsetCol(offsetCol) { }

    Direction getOpposite() const {
        return Direction(this->offsetRow * -1, this->offsetCol * -1);
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

    void setAt(const Cell cell, const Tile tile);

    void setAt(size_t row, size_t column, const Tile tile);

    int countTurnedOver(const Cell cell, const Tile tile) const;

    bool canPutTile(const Cell cell, const Tile tile) const;

    void putTile(const Cell cell, const Tile tile);

    Tile getEnemyTile(Tile tile) const;

    bool isGameOver() const;

    Tile whoWins() const;

    Score calculateScore() const;

private:
    size_t getIndex(const Cell cell) const;

    bool isCorrect(const Cell cell) const;

    int goThroughTiles(const Cell &startCell, Direction direction, Tile tile, Tile replacer);

    int lookThroughTiles(const Cell &startCell, Direction direction, Tile tile) const;

    size_t gameSize, emptyCount;
    std::vector<Tile> field;
};

inline size_t GameBoard::getGameSize() const {
    return gameSize;
}


#endif //REVERSI_GAMEBOARD_H
