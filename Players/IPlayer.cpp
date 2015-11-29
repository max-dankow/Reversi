#include <assert.h>
#include "IPlayer.h"

void IPlayer::play(std::istream &input, std::ostream &output) {
    std::string comand;
    input >> comand;
    Tile enemyTile;
    assert(comand == "init");
    std::string color;
    input >> color;
    if (color == "white") {
        myTile = WHITE;
        enemyTile = BLACK;
    } else {
        if (color == "black") {
            myTile = BLACK;
            enemyTile = WHITE;
        } else {
            assert(false);
        }
    }
    bool shouldTerminate = false;
    GameBoard gameBoard(GameBoard::DEFAULT_GAME_SIZE);

    while (!shouldTerminate) {
        input >> comand;
        assert(comand.length() > 0);
        switch (comand[0]) {
            case 't': {
                // Т.к. нас просят сделать ход, то он существует.
                assert(comand == "turn");
                Cell move = takeTurn(gameBoard);
                assert(gameBoard.canPutTile(move, myTile));
                gameBoard.putTile(move, myTile);
                output << "move ";
                move.print(output);
                break;
            }
            case 'm': {
                assert(comand == "move");
                Cell enemyMove;
                enemyMove.read(input);
                assert(gameBoard.canPutTile(enemyMove, enemyTile));
                gameBoard.putTile(enemyMove, enemyTile);
                break;
            }
            case 'l':
            case 'w':
            case 'd': {
                assert(comand == "lose" || comand == "win" || comand == "draw");
                shouldTerminate = true;
                break;
            }
            case 'b':
            default: {
                assert(false);
            }
        }
    }
}