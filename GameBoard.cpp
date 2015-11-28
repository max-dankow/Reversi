#include <assert.h>
#include "GameBoard.h"

GameBoard::GameBoard(size_t gameSize) : gameSize(gameSize) {
    field.assign(gameSize * gameSize, EMPTY);
    setAt(gameSize / 2 - 1, gameSize / 2 - 1, WHITE);
    setAt(gameSize / 2 - 1, gameSize / 2, BLACK);
    setAt(gameSize / 2, gameSize / 2 - 1, BLACK);
    setAt(gameSize / 2, gameSize / 2, WHITE);
}

void GameBoard::print(std::ostream &output) const {
    for (size_t row = 0; row < gameSize; ++row) {
        for (size_t column = 0; column < gameSize; ++column) {
            switch (getAt(row, column)) {
                case EMPTY:
                    output << '.';
                    break;
                case WHITE:
                    output << 'W';
                    break;
                case BLACK:
                    output << 'B';
                    break;
                default:
                    assert(false);
            }
        }
        output << '\n';
    }
    output << '\n';
}

Tile GameBoard::getAt(size_t row, size_t column) const {
    return field[getIndex(row, column)];
}

size_t GameBoard::getIndex(size_t row, size_t column) const {
    assert(row < gameSize && column < gameSize);
    return row * gameSize + column;
}

void GameBoard::setAt(size_t row, size_t column, Tile tile) {
    field[getIndex(row, column)] = tile;
}
