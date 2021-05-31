#ifndef FIELD_H
#define FIELD_H

#include <QGraphicsView>
#include <QGraphicsItem>
#include "ship.h"
#include "square.h"
#include "board.h"
#include <QObject>
#include "dragship.h"
#include "player.h"


class Field : public QGraphicsRectItem
{

public:
    Field(int boardWidth, int boardHeight, int squareWidth, int squareHeight, Board *b, QGraphicsItem *parent = nullptr);
    ~Field();

    void setVisibility(bool visibility) {
        m_visibility = visibility;
    }
    void press();
    void release();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    int sqW, sqH;
    int boardW, boardH;
    QPointF prevP; // for dragging
    Player *player;
    Board *board;
    bool m_visibility = true;

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};



#endif // BOARD_H
