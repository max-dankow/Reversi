#include <assert.h>
#include "GameBoard.h"

GameBoard::GameBoard(size_t gameSize) : gameSize(gameSize), emptyCount(gameSize * gameSize) {
    field.assign(gameSize * gameSize, EMPTY);
    setAt(gameSize / 2 - 1, gameSize / 2 - 1, WHITE);
    setAt(gameSize / 2 - 1, gameSize / 2, BLACK);
    setAt(gameSize / 2, gameSize / 2 - 1, BLACK);
    setAt(gameSize / 2, gameSize / 2, WHITE);
}

Tile GameBoard::getAt(size_t row, size_t column) const {
    return field[getIndex(row, column)];
}

size_t GameBoard::getIndex(size_t row, size_t column) const {
    assert(isCorrect(row, column));
    return row * gameSize + column;
}

void GameBoard::setAt(size_t row, size_t column, Tile tile) {
    if (field[getIndex(row, column)] == EMPTY && tile != EMPTY) {
        --emptyCount;
    }
    if (field[getIndex(row, column)] != EMPTY && tile == EMPTY) {
        ++emptyCount;
    }
    field[getIndex(row, column)] = tile;
}

bool GameBoard::canPutTile(size_t row, size_t column, Tile tile) const {
    // Перебираем все 8 направлений.
    Tile enemyTile = getEnemyTile(tile);
    for (int offsetRow = -1; offsetRow < 2; ++offsetRow) {
        for (int offsetCol = -1; offsetCol < 2; ++offsetCol) {
            Direction direction(offsetRow, offsetCol);
            int replacedCount = lookThroughTiles(enemyTile, row, column, direction);
            if (replacedCount != 0) {
                return true;
            }
        }
    }
    return false;
}

void GameBoard::putTile(size_t row, size_t column, Tile tile) {
    assert(getAt(row, column) == EMPTY);
    assert(tile == WHITE || tile == BLACK);
    // Перебираем все 8 направлений.
    Tile enemyTile = getEnemyTile(tile);
    int replacedCount = 0;
    for (int offsetRow = -1; offsetRow < 2; ++offsetRow) {
        for (int offsetCol = -1; offsetCol < 2; ++offsetCol) {
            Direction direction(offsetRow, offsetCol);
            replacedCount += goThroughTiles(enemyTile, tile, row, column, direction);
        }
    }
    assert(replacedCount != 0);
    setAt(row, column, tile);
    print(std::cerr);
}

bool GameBoard::isCorrect(size_t row, size_t column) const {
    return row < gameSize && column < gameSize;
}

void GameBoard::print(std::ostream &output) const {
    for (size_t column = 0; column < gameSize; ++column) {
        output << ' ' << column;
    }
    output << '\n';
    for (size_t row = 0; row < gameSize; ++row) {
        output << row << ' ';
        for (size_t column = 0; column < gameSize; ++column) {
            switch (getAt(row, column)) {
                case EMPTY:
                    output << '.';
                    break;
                case WHITE:
                    output << "W";
                    break;
                case BLACK:
                    output << 'B';
                    break;
                default:
                    assert(false);
            }
            output << ' ';
        }
        output << '\n';
    }
    output << '\n';
}

int GameBoard::goThroughTiles(Tile tile, Tile replacer,
                              size_t rowStart, size_t colStart,
                              Direction direction) {
    bool shouldReplace = tile != replacer;
    size_t row = rowStart + direction.offsetRow;
    size_t column = colStart + direction.offsetCol;

    while (isCorrect(row, column) && getAt(row, column) == tile) {
        row += direction.offsetRow;
        column += direction.offsetCol;
    }
    int replacedCount = 0;
    if (isCorrect(row, column) && getAt(row, column) == replacer) {
        direction = direction.getOpposite();
        row = row + direction.offsetRow;
        column = column + direction.offsetCol;
        while (isCorrect(row, column) && getAt(row, column) == tile) {
            ++replacedCount;
            if (shouldReplace) {
                setAt(row, column, replacer);
            }
            row += direction.offsetRow;
            column += direction.offsetCol;
        }
    }
    return replacedCount;
}

// todo: придумать, как избавиться от копипасты!!!!
int GameBoard::lookThroughTiles(Tile tile, size_t rowStart, size_t colStart,
                                GameBoard::Direction direction) const {
    size_t row = rowStart + direction.offsetRow;
    size_t column = colStart + direction.offsetCol;

    while (isCorrect(row, column) && getAt(row, column) == tile) {
        row += direction.offsetRow;
        column += direction.offsetCol;
    }

    int replacedCount = 0;
    Tile enemyTile = getEnemyTile(tile);

    if (isCorrect(row, column) && getAt(row, column) == enemyTile) {
        direction = direction.getOpposite();
        row = row + direction.offsetRow;
        column = column + direction.offsetCol;
        while (isCorrect(row, column) && getAt(row, column) == tile) {
            ++replacedCount;
            row += direction.offsetRow;
            column += direction.offsetCol;
        }
    }
    return replacedCount;
}

Tile GameBoard::getEnemyTile(Tile tile) const {
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

bool GameBoard::isGameOver() const {
    return emptyCount == 0;
}
