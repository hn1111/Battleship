#include "fieldview.h"

FieldView::FieldView(QWidget* parent):
    QGraphicsView(parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(new QGraphicsScene(parent));
}

void FieldView::setBoard(Player *pl, bool isEnemy)
{
    // runs before showEvent
    player = pl;
    if (isEnemy) {
        isEditable = false;
        isClickable = false;
        invisibleEnemy = true;
    } else {
        isEditable = true;
        isClickable = false;
        invisibleEnemy = false;
    }

}

void FieldView::setEditable(bool b)
{
    if (b) {
        for (auto item : movableShips) {
            item->show();
        }
    } else {
        for (auto item : movableShips)
            item->hide();
    }
}

void FieldView::showEvent(QShowEvent *event)
{
    QGraphicsView::showEvent(event);
    int h = height();
    int w = width();

    sqWidth = w/WIDTH_SQUARES_NUM;
    sqHeight = h/HEIGHT_SQUARES_NUM;
    // vertical lines
    // They're invisible
    // Without them board is displayd incorrectly
    // Don't know how to fix
    for (int i = 0; i < WIDTH_SQUARES_NUM - 1; i++) {
        scene()->addLine(sqWidth + i * sqWidth, 0,
                      sqWidth + i * sqWidth, h);
    }
    // horizontal lines
    for (int i = 0; i < HEIGHT_SQUARES_NUM - 1; i++) {
        scene()->addLine(0, sqHeight + sqHeight * i,
                      w, sqHeight + sqHeight * i);
    }

    // width and height of a field are known only after exec of showEvent
    field = new Field(height(), width(), sqWidth, sqHeight, &player->board);
    scene()->addItem(field);
    if (invisibleEnemy)
        field->setVisibility(false);

    if (isEditable) {
        addShipShapes();
    }
}

//void FieldView::mouseDoubleClickEvent(QMouseEvent *event)
//{

//}

void FieldView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    if (isClickable) {
        auto &cell = getCell(event->position().x(), event->position().y());
        game->handleTurn(player, cell);
        scene()->update();
    }

}

//void FieldView::mouseMoveEvent(QMouseEvent *event)
//{

//}

void FieldView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
    scene()->update();
}

void FieldView::updateBoard()
{
    scene()->update();
}

Square &FieldView::getCell(int x, int y)
{
    return player->board.at(x / sqWidth, y / sqHeight);
}

void FieldView::addShipShapes()
{
    if (movableShips.count() > 0) {
        for (auto shape : movableShips)
            delete shape;
        movableShips.clear();
    }
    for (auto sh : player->board.ships()) {
        auto shape = new DragShip(sh, sqWidth, sqHeight, width(), height(), &player->board);
        movableShips.append(shape);
        scene()->addItem(shape);
    }
}

void FieldView::scrollContentsBy(int dx, int dy)
{
    // no scroll
}


