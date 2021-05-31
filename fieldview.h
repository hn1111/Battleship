#ifndef FIELDVIEW_H
#define FIELDVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <memory>
#include "player.h"
#include "game.h"
#include "field.h"

//const int WIDTH_SQUARES = 10;
//const int HEIGHT_SQUARES = 10;

class FieldView : public QGraphicsView
{
public:
    FieldView(QWidget* parent);
    void setBoard(Player *pl, bool isEnemy = false);
    void setGame(Game *g) {
        game = g;
    }
    void newGame() {
        addShipShapes();
    }

    void setEditable(bool b);

    void setClickable(bool b) {
        isClickable = b;
    }
    void setEnemyVisibility(bool b) {
        if (field)
            field->setVisibility(b);
    }
protected:
    void showEvent(QShowEvent *event) override;
    //void mouseDoubleClickEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void click();

public slots:
    void updateBoard();


private:
    int sqWidth;
    int sqHeight;
    int columns;
    int rows;
    Player *player;
    Game *game;
    Field *field;
    QVector<DragShip*> movableShips;
    bool isEditable;
    bool isClickable;
    bool invisibleEnemy;
    Square& getCell(int x, int y);
    void addShipShapes();

    // QAbstractScrollArea interface
protected:
    void scrollContentsBy(int dx, int dy) override;
};

#endif // FIELDVIEW_H
