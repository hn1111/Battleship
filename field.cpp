#include "field.h"

Field::Field(int boardWidth, int boardHeight, int squareWidth, int squareHeight, Board *b, QGraphicsItem *parent):
    boardW(boardWidth), boardH(boardHeight),
    QGraphicsRectItem(0,0, boardWidth, boardHeight, parent),
    sqW(squareWidth), sqH(squareHeight),
    board(b)
{
}

Field::~Field()
{
    //delete mh;
}

void Field::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    event->setAccepted(false);
}

void Field::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
}

void Field::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
}




void Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    int R = 8;
    auto borderColor = Qt::darkCyan;
    for (int i = 0; i < board->rows(); i++)
        for (int j = 0; j < board->columns(); j++) {
            switch (board->status(j,i)) {
            case Square::empty:
                painter->setBrush(Qt::transparent);
                painter->setPen(Qt::darkCyan);
                painter->drawRect(j*sqW, i*sqH, sqW, sqH);
                break;
            case Square::occupied:
                if (m_visibility) {
                    painter->setBrush(Qt::cyan);
                    painter->setPen(Qt::darkCyan);
                    painter->drawRect(j*sqW, i*sqH, sqW, sqH);
                } else {
                    painter->setBrush(Qt::transparent);
                    painter->setPen(Qt::darkCyan);
                    painter->drawRect(j*sqW, i*sqH, sqW, sqH);
                }
                break;
            case Square::hit:
                painter->setBrush(Qt::cyan);
                painter->setPen(Qt::darkCyan);
                painter->drawRect(j*sqW, i*sqH, sqW, sqH);
                painter->setPen(QPen(Qt::darkCyan,2));
                painter->drawLine(j*sqW, i*sqH, (j + 1)*sqW, (i + 1)*sqH);
                painter->drawLine((j+1)*sqW, i*sqH, j*sqW, (i + 1)*sqH);
                break;
            case Square::dead:
                painter->setBrush(Qt::gray);
                painter->setPen(Qt::darkGray);
                painter->drawRect(j*sqW, i*sqH, sqW, sqH);
                painter->setPen(QPen(Qt::darkGray,2));
                painter->drawLine(j*sqW, i*sqH, (j + 1)*sqW, (i + 1)*sqH);
                painter->drawLine((j+1)*sqW, i*sqH, j*sqW, (i + 1)*sqH);
                break;
            case Square::miss:
                painter->setBrush(Qt::white);
                painter->setPen(Qt::darkCyan);
                painter->drawRect(j*sqW, i*sqH, sqW, sqH);
                painter->setBrush(Qt::black);
                painter->setPen(Qt::black);
                painter->drawEllipse((j+0.5)*sqW - R/2, (i+0.5)*sqH - R/2, R, R);
            }

        }
}


