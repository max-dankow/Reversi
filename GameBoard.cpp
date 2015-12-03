#include <assert.h>
#include "GameBoard.h"

GameBoard::GameBoard(size_t gameSize) : gameSize(gameSize), emptyCount(gameSize * gameSize) {
    field.assign(gameSize * gameSize, EMPTY);
    setAt(gameSize / 2 - 1, gameSize / 2 - 1, WHITE);
    setAt(gameSize / 2, gameSize / 2 - 1, BLACK);
    setAt(gameSize / 2 - 1, gameSize / 2, BLACK);
    setAt(gameSize / 2, gameSize / 2, WHITE);
}

Tile GameBoard::getAt(const Cell cell) const {
    return field[getIndex(cell)];
}

Tile GameBoard::getAt(size_t row, size_t column) const {
    return getAt(Cell(row, column));
}

size_t GameBoard::getIndex(const Cell cell) const {
    assert(isCorrect(cell));
    return cell.row * gameSize + cell.column;
}

void GameBoard::setAt(size_t row, size_t column, const Tile &tile) {
    setAt(Cell(row, column), tile);
}

void GameBoard::setAt(const Cell &cell, const Tile &tile) {
    if (field[getIndex(cell)] == EMPTY && tile != EMPTY) {
        --emptyCount;
    }
    if (field[getIndex(cell)] != EMPTY && tile == EMPTY) {
        ++emptyCount;
    }
    field[getIndex(cell)] = tile;
}

int GameBoard::countTurnedOver(const Cell &cell, const Tile &tile) const {
    assert(tile == WHITE || tile == BLACK);
    if (!isCorrect(cell) || getAt(cell) != EMPTY) {
        return false;
    }
    Tile enemyTile = getEnemyTile(tile);
    int replacedCount = 0;
    // Перебираем все 8 направлений.
    for (int offsetRow = -1; offsetRow < 2; ++offsetRow) {
        for (int offsetCol = -1; offsetCol < 2; ++offsetCol) {
            Direction direction(offsetRow, offsetCol);
            replacedCount += lookThroughTiles(cell, direction, enemyTile);
        }
    }
    return replacedCount;
}

bool GameBoard::canPutTile(const Cell &cell, const Tile &tile) const {
    return countTurnedOver(cell, tile) != 0;
}

void GameBoard::putTile(const Cell &cell, const Tile &tile) {
    assert(isCorrect(cell));
    assert(getAt(cell) == EMPTY);
    assert(tile == WHITE || tile == BLACK);
    // Перебираем все 8 направлений.
    Tile enemyTile = getEnemyTile(tile);
    int replacedCount = 0;
    for (int offsetRow = -1; offsetRow < 2; ++offsetRow) {
        for (int offsetCol = -1; offsetCol < 2; ++offsetCol) {
            Direction direction(offsetRow, offsetCol);
            replacedCount += goThroughTiles(cell, direction, enemyTile, tile);
        }
    }
    assert(replacedCount != 0);
    setAt(cell, tile);
//    print(std::cerr);
}

bool GameBoard::isCorrect(const Cell cell) const {
    return cell.row < gameSize
           && cell.column < gameSize
           && cell.row >= 0
           && cell.column >= 0;
}

void GameBoard::print(std::ostream &output) const {
    output << ' ';
    for (size_t column = 0; column < gameSize; ++column) {
        output << " " << column;
    }
    output << '\n';
    for (size_t row = 0; row < gameSize; ++row) {
        output << row << ' ';
        for (size_t column = 0; column < gameSize; ++column) {
            switch (getAt(Cell(row, column))) {
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

int GameBoard::goThroughTiles(const Cell &startCell, Direction direction, Tile tile, Tile replacer) {
    bool shouldReplace = tile != replacer;
    Cell cell = startCell;
    cell.move(direction);

    while (isCorrect(cell) && getAt(cell) == tile) {
        cell.move(direction);
    }
    int replacedCount = 0;
    if (isCorrect(cell) && getAt(cell) == replacer) {
        direction = direction.getOpposite();
        cell.move(direction);
        while (isCorrect(cell) && getAt(cell) == tile) {
            ++replacedCount;
            if (shouldReplace) {
                setAt(cell, replacer);
            }
            cell.move(direction);
        }
    }
    return replacedCount;
}

// todo: придумать, как избавиться от копипасты!!!!
int GameBoard::lookThroughTiles(const Cell &startCell, const Direction &direction, Tile tile) const {
    Cell cell = startCell;
    cell.move(direction);

    while (isCorrect(cell) && getAt(cell) == tile) {
        cell.move(direction);
    }
    int replacedCount = 0;
    Tile enemyTile = getEnemyTile(tile);
    if (isCorrect(cell) && getAt(cell) == enemyTile) {
        auto oppositeDirection = direction.getOpposite();
        cell.move(oppositeDirection);
        while (isCorrect(cell) && getAt(cell) == tile) {
            ++replacedCount;
            cell.move(oppositeDirection);
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
    return isGameOverFor(WHITE) && isGameOverFor(BLACK);
}

bool GameBoard::isGameOverFor(Tile tile) const {
    if (emptyCount == 0) {
        return true;
    }
    for (size_t row = 0; row < gameSize; ++row) {
        for (size_t column = 0; column < gameSize; ++column) {
            Cell here(row, column);
            if (canPutTile(here, tile)) {
                return false;
            }
        }
    }
    return true;
}

Tile GameBoard::whoWins() const {
    assert(isGameOver());
    auto score = calculateScore();
    if (score.whiteTiles > score.blackTiles) {
        return WHITE;
    }
    if (score.whiteTiles < score.blackTiles) {
        return BLACK;
    }
    return EMPTY;
}

Score GameBoard::calculateScore() const {
    Score score;
    for (Tile tile : field) {
        if (tile == WHITE) {
            ++score.whiteTiles;
        }
        if (tile == BLACK) {
            ++score.blackTiles;
        }
    }
    return score;
}
