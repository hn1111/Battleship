#ifndef GAME_H
#define GAME_H

#include "pcplayer.h"
#include "compplayer.h"
#include "internetplayer.h"
#include "player.h"
#include <QObject>
const int WIDTH_SQUARES_NUM = 10;
const int HEIGHT_SQUARES_NUM = 10;

class Game : public QObject
{
    Q_OBJECT

    friend class Player;
public:
    explicit Game (QObject *parent = nullptr);
    ~Game();
    Player *player1;
    Player *player2;
    Player *turn;
    void startNewGame();
    void handleTurn(Player *p, Square &square);
    void handleTurn(Player *p, int col, int row);

signals:
    void boardChanged();
    void win(QString s);
    void changeTurn();

private:

    void checkWin();
    Player *otherPlayer(Player *p) {
        return (player1 == p) ? player2 : player1;
    }
};



#endif // GAME_H
