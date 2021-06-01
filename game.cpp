#include "game.h"



Game::Game (QObject *parent) : QObject(parent)
{
    player1 = new PCPlayer();
    player1->game = this;
    player2 = new CompPlayer();
    player2->game = this;
    startNewGame();
}

Game::~Game()
{
    delete player1;
    delete player2;
}

void Game::startNewGame()
{
    turn = player1;
    player1->board = Board(WIDTH_SQUARES_NUM, HEIGHT_SQUARES_NUM);
    player2->board = Board(WIDTH_SQUARES_NUM, HEIGHT_SQUARES_NUM);

    player1->startNewGame();
    player2->startNewGame();
}

void Game::handleTurn(Player *p, Square& square)
{
    switch(square.status) {
    case Square::occupied:
        square.status = Square::hit;
        if (p->checkLose()) {
            emit boardChanged();
            emit win(otherPlayer(p)->name);
            return;
        }
        emit boardChanged();
        break;
    case Square::empty:
        square.status = Square::miss;
        emit boardChanged();
        turn = otherPlayer(turn);
        emit changeTurn();
        break;
    case Square::dead:
    case Square::hit:
    case Square::miss:
        break;
    }
    turn->makeMove();
}

void Game::handleTurn(Player *p, int col, int row)
{
    handleTurn(otherPlayer(p), otherPlayer(p)->board.at(col, row));
}


