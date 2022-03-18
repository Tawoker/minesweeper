#include "cell.h"
QImage zero(":/resources/images/0.png");
QImage one(":/resources/images/1.png");
QImage two(":/resources/images/2.png");
QImage three(":/resources/images/3.png");
QImage four(":/resources/images/4.png");
QImage five(":/resources/images/5.png");
QImage six(":/resources/images/6.png");
QImage seven(":/resources/images/7.png");
QImage eight(":/resources/images/8.png");
QImage flag(":/resources/images/flag.png");
QImage mine(":/resources/images/mine.png");
QImage unopend(":/resources/images/unopend.png");



Cell::Cell(QRect rect)
    :cellRect(rect)
{
    CellImage = unopend;
}

QRect Cell::GetCellRect(){return cellRect;}

bool Cell::Contains(QPoint p)
{
    if(cellRect.top() > p.y())
        return false;
    if(cellRect.bottom() < p.y())
        return false;
    if(cellRect.left() > p.x())
        return false;
    if(cellRect.right() < p.x())
        return false;
    return true;
}

void Cell::Open(int i, int j, QVector<QVector<Cell*>> cells)
{
    MinesAround(i, j, cells);
    cells[i][j]->is_unopend = false;
    switch (value) {
    case v0:
        CellImage = zero;
        cells[i][j]->OpenAround(i, j, cells);
        break;
    case v1:
        CellImage = one;
        break;
    case v2:
        CellImage = two;
        break;
    case v3:
        CellImage = three;
        break;
    case v4:
        CellImage = four;
        break;
    case v5:
        CellImage = five;
        break;
    case v6:
        CellImage = six;
        break;
    case v7:
        CellImage = seven;
        break;
    case v8:
        CellImage = eight;
        break;
    case MINE:
        CellImage = mine;
        break;
    default:
        break;
    }
}

int Cell::SetFlag()
{
    if (CellImage == unopend){
        CellImage = flag;
        return -1;
    }
    else if (CellImage == flag){
        CellImage = unopend;
        return 1;
    }
    return 0;
}

int Cell::MinesAround(int i, int j, QVector<QVector<Cell*>> cells)
{
    int minesCounter = 0;
    int iDown = i - 1, iUp = i + 1, jDown = j - 1, jUp = j + 1;
    if (iDown > -1 && jDown > -1)
        if(cells[iDown][jDown]->value == MINE)
            minesCounter++;
    if (iDown > -1 && jUp < cells[0].size())
        if(cells[iDown][jUp]->value == MINE)
            minesCounter++;
    if (iUp < cells.size() && jDown > -1)
        if(cells[iUp][jDown]->value == MINE)
            minesCounter++;
    if (iUp < cells.size() && jUp < cells[0].size())
        if(cells[iUp][jUp]->value == MINE)
            minesCounter++;
    if (iDown > -1)
        if (cells[iDown][j]->value == MINE)
            minesCounter++;
    if (iUp < cells.size())
        if (cells[iUp][j]->value == MINE)
            minesCounter++;
    if (jDown > -1)
        if (cells[i][jDown]->value == MINE)
            minesCounter++;
    if (jUp < cells.size())
        if (cells[i][jUp]->value == MINE)
            minesCounter++;
    if (cells[i][j]->value != MINE){
        switch (minesCounter) {
        case 0:
            cells[i][j]->value = v0;
            break;
        case 1:
            cells[i][j]->value = v1;
            break;
        case 2:
            cells[i][j]->value = v2;
            break;
        case 3:
            cells[i][j]->value = v3;
            break;
        case 4:
            cells[i][j]->value = v4;
            break;
        case 5:
            cells[i][j]->value = v5;
            break;
        case 6:
            cells[i][j]->value = v6;
            break;
        case 7:
            cells[i][j]->value = v7;
            break;
        case 8:
            cells[i][j]->value = v8;
            break;
        default:
            break;
        }
    }
    return minesCounter;
}

void Cell::OpenAround(int i, int j, QVector<QVector<Cell *> > cells)
{
    int iDown = i - 1, iUp = i + 1, jDown = j - 1, jUp = j + 1;
    if (iDown > -1 && jDown > -1)
        if (cells[iDown][jDown]->is_unopend)
            cells[iDown][jDown]->Open(iDown, jDown, cells);
    if (iDown > -1 && jUp < cells[0].size())
        if (cells[iDown][jUp]->is_unopend)
            cells[iDown][jUp]->Open(iDown, jUp, cells);
    if (iUp < cells.size() && jDown > -1)
        if (cells[iUp][jDown]->is_unopend)
            cells[iUp][jDown]->Open(iUp, jDown, cells);
    if (iUp < cells.size() && jUp < cells[0].size())
        if (cells[iUp][jUp]->is_unopend)
            cells[iUp][jUp]->Open(iUp, jUp, cells);
    if (iDown > -1)
        if (cells[iDown][j]->is_unopend)
            cells[iDown][j]->Open(iDown, j, cells);
    if (iUp < cells.size())
        if (cells[iUp][j]->is_unopend)
            cells[iUp][j]->Open(iUp, j, cells);
    if (jDown > -1)
        if (cells[i][jDown]->is_unopend)
            cells[i][jDown]->Open(i, jDown, cells);
    if (jUp < cells.size())
        if (cells[i][jUp]->is_unopend)
            cells[i][jUp]->Open(i, jUp, cells);
}

void Cell::Draw(QPainter *painter)
{
    painter->drawImage(cellRect, CellImage);
}

CellStatus Cell::getValue() const
{
    return value;
}

void Cell::setValue(CellStatus newValue)
{
    value = newValue;
}

bool Cell::getIs_unopend() const
{
    return is_unopend;
}

