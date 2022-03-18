#ifndef CELL_H
#define CELL_H
#include "game_constants.h"
#include <QImage>
#include <QPoint>
#include <QPainter>
#include <QRect>

class Cell
{
public:
    Cell(QRect rect);
    QRect GetCellRect();
    bool Contains(QPoint p);
    void Open(int i, int j, QVector<QVector<Cell*>> cells);
    int SetFlag();
    int MinesAround(int i, int j, QVector<QVector<Cell*>> cells);
    void OpenAround(int i, int j, QVector<QVector<Cell*>> cells);
    void Draw(QPainter *painter);
    CellStatus getValue() const;
    void setValue(CellStatus newValue);
    bool getIs_unopend() const;

private:
    CellStatus value = v0;
    QRect cellRect;
    bool is_mine = false, is_unopend = true;
    QImage CellImage;
};

#endif // CELL_H
