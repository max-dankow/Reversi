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

    void move(const Direction &direction) {
        row += direction.offsetRow;
        column += direction.offsetCol;
    }

    int row, column;
};

class GameBoard {
public:
    explicit GameBoard(size_t gameSize);

    void print(std::ostream &output) const;

    Tile getAt(const Cell cell) const;
    Tile getAt(size_t row, size_t column) const;

    void setAt(const Cell cell, const Tile tile);

    void setAt(size_t row, size_t column, const Tile tile);

    bool canPutTile(const Tile tile, const Cell cell) const;

    void putTile(const Tile tile, const Cell cell);

    Tile getEnemyTile(Tile tile) const;

    bool isGameOver() const;

private:
    size_t getIndex(const Cell cell) const;

    bool isCorrect(const Cell cell) const;

    int goThroughTiles(const Cell &startCell, Direction direction, Tile tile, Tile replacer);

    int lookThroughTiles(const Cell &startCell, Direction direction, Tile tile) const;

    size_t gameSize, emptyCount;
    std::vector<Tile> field;
};


#endif //REVERSI_GAMEBOARD_H
