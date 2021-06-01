#include "board.h"

Board::~Board()
{
    for (auto ship : m_ships)
        delete ship;
    m_ships.clear();
}

Board::Board(int w, int h):
    m_columns(w), m_rows(h)
{
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            m_board.append({j, i, w, h, Square::empty});
        }
    }
}

void Board::addShip(Ship *sh)
{
    m_ships.append(sh);
    createSquarePointers(sh);

}

void Board::clear()
{
    m_ships.clear();
    for (auto &sq : m_board)
        sq.status = Square::empty;
}

bool Board::isSpaceFree(int col, int row, int sqNum, Ship::Direction d) const
{
    if (d == Ship::vertical) {
        for (int i = 0; i < sqNum; i++) {
            if (row+i >= rows())
                return false;
            if (status(col, row+i) != Square::empty)
                return false;
            if (!isSquaresAroundFree(col, row+i))
                return false;
        }
    } else {

        for (int i = 0; i < sqNum; i++) {
            if (col+i >= columns())
                return false;
            if (status(col+i, row) != Square::empty)
                return false;
            if (!isSquaresAroundFree(col+i, row))
                return false;
        }
    }
    return true;
}

void Board::createSquarePointers(Ship *sh)
{
    sh->squares.clear();
    if (sh->dir == Ship::horizontal) {
        for (int i = 0; i < sh->sqNum; i++) {
            Square &s = at(sh->xB + i, sh->yB);
            s.status = Square::occupied;
            sh->squares.append(&s);
        }
    } else {
            for (int i = 0; i < sh->sqNum; i++) {
                Square &s = at(sh->xB, sh->yB + i);
                s.status = Square::occupied;
                sh->squares.append(&s);
            }
    }
}

Ship* Board::putShipRandom(int sqNum)
{
    int tries = 0; // in case if too many ships for board
    // Ships can be put in supoptimal way, in one generated map there isn't enough space
    // but other time all ships can fit
    Ship::Direction d;
    int col, row;
    while (true) {
        d = (QRandomGenerator::global()->generate() % 2) ?
                    Ship::horizontal : Ship::vertical;
        col = QRandomGenerator::global()->generate() % 10;
        row = QRandomGenerator::global()->generate() % 10;
        if (isSpaceFree(col,row,sqNum, d))
            break;
        if (++tries > 1000)
            throw std::runtime_error("Can't generate map");
    }
    return new Ship(col, row, sqNum, d);
}

bool Board::isSquaresAroundFree(int col, int row) const
{
    // up
    if (row > 0) {
        if (status(col, row - 1) == Square::occupied)
            return false;
    }

    if (col < columns()-1) {
        // up right
        if (row > 0 && status(col + 1, row - 1) == Square::occupied)
            return false;
        // right
        if (status(col + 1, row) == Square::occupied)
            return false;
        // bottom right
        if (row < rows()-1 && status(col + 1, row + 1) == Square::occupied)
            return false;
    }
    // down
    if (row < rows()-1) {
        if (status(col, row + 1) == Square::occupied)
            return false;
    }


    if (col > 0) {
        // bottom left
        if (row < rows() - 1 && status(col - 1, row + 1) == Square::occupied)
            return false;
        // left
        if (status(col - 1, row) == Square::occupied)
            return false;
        // up left
        if (row > 0 && status(col - 1, row - 1) == Square::occupied)
            return false;
    }
    return true;
}

void Board::createShips()
{
    // remove old ships
    if (m_ships.count() > 0) {
        for (auto ship : m_ships)
            delete ship;
        m_ships.clear();
    }

//    addShip(new Ship(0, 0, 1, Ship::Direction::horizontal));
//    addShip(new Ship(0, 2, 4, Ship::Direction::horizontal));
//    addShip(new Ship(0, 4, 4, Ship::Direction::horizontal));
//    return;

    int tries = 0;
    while (true)
        try {
            addShip(putShipRandom(5));
            addShip(putShipRandom(4));
            addShip(putShipRandom(4));
            addShip(putShipRandom(3));
            addShip(putShipRandom(3));
            addShip(putShipRandom(3));
            addShip(putShipRandom(2));
            addShip(putShipRandom(2));
            addShip(putShipRandom(2));
            addShip(putShipRandom(1));
            addShip(putShipRandom(1));
            addShip(putShipRandom(1));
            return;
        } catch (std::runtime_error &err) {
            if (++tries > 50)
                throw;
            clear();
        }
}


Square::Status Board::status(int col, int row) const
{
    return at(col, row).status;
}

Square &Board::at(int col, int row)
{
    return m_board[m_board.indexOf(Square({col,row}))];
}

const Square &Board::at(int col, int row) const
{
    return m_board[m_board.indexOf(Square({col,row}))];
}

