#ifndef BOARD_H
#define BOARD_H

#include <QVector>
#include <QRandomGenerator>
#include "square.h"
#include "ship.h"

class Board
{
    friend class Game;
    friend class Player;
    friend class CompPlayer;
public:
    Board() {};
    ~Board();
    Board(int w, int h);

    QVector<Ship*> ships() const {
        return m_ships;
    }

    int columns() const {
        return m_columns;
    }
    int rows() const {
        return m_rows;
    }
    Square::Status status(int col, int row) const;
    Square& at(int col, int row) ;
    const Square& at(int col, int row) const;
    bool isSpaceFree(int col, int row, int sqNum, Ship::Direction) const;
    void createSquarePointers(Ship *sh);
//    void display() {
//        for (int row = 0; row < m_rows; row++) {
//            QString s;
//            for (int col = 0; col < m_columns; col++) {
//                s += QString::number(at(col, row).status);
//            }
//            qDebug() << s;
//        }
//    }

private:
    int m_columns, m_rows;
    QVector<Square> m_board;
    QVector<Ship*> m_ships;
    void createShips();
    void addShip(Ship *sh);
    void clear();

    Ship *putShipRandom(int sqNum);
    bool isSquaresAroundFree(int col, int row) const;
};

#endif // BOARD_H
