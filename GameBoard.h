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
    GameBoard(size_t gameSize);
    void print(std::ostream &output) const;
    Tile getAt(size_t row, size_t column) const;
    void setAt(size_t row, size_t column, Tile tile);
private:
    size_t getIndex(size_t row, size_t column) const;
    size_t gameSize;
    std::vector<Tile> field;
};


#endif //REVERSI_GAMEBOARD_H
