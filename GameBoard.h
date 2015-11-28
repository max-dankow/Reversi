#ifndef REVERSI_GAMEBOARD_H
#define REVERSI_GAMEBOARD_H

#include <vector>
#include <iostream>

enum Tile {
    EMPTY,
    WHITE,
    BLACK
};

class GameBoard {
public:
    explicit GameBoard(size_t gameSize);

    void print(std::ostream &output) const;

    Tile getAt(size_t row, size_t column) const;

    void setAt(size_t row, size_t column, Tile tile);

    bool canPutTile(size_t row, size_t column, Tile tile) const;

    void putTile(size_t row, size_t column, Tile tile);

    Tile getEnemyTile(Tile tile) const;

    bool isGameOver() const;

private:
    struct Direction {
        Direction(int offsetRow, int offsetCol) :
                offsetRow(offsetRow), offsetCol(offsetCol) { }

        Direction getOpposite() const {
            return Direction(this->offsetRow * -1, this->offsetCol * -1);
        }

        int offsetRow, offsetCol;
    };

    size_t getIndex(size_t row, size_t column) const;

    bool isCorrect(size_t row, size_t column) const;

    int goThroughTiles(Tile tile, Tile replacer, size_t rowStart, size_t colStart, Direction direction);

    int lookThroughTiles(Tile tile, size_t rowStart, size_t colStart, Direction direction) const;

    size_t gameSize, emptyCount;
    std::vector<Tile> field;
};


#endif //REVERSI_GAMEBOARD_H
