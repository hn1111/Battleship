#ifndef SQUARE_H
#define SQUARE_H



class Square
{
public:
    enum Status {
        miss,
        hit,
        empty,
        occupied,
        dead
    };
    int col;
    int row;
    int width;
    int height;
    Status status;
    bool operator==(const Square& a) const {
        return (a.col == col and a.row == row);
    }
    bool operator<(const Square& a) const {
        if (row < a.row)
            return true;
        if (col < a.col)
            return true;
        return false;
    }
};

#endif // SQUARE_H
