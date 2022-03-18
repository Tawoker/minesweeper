#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QTimer>
#include <QVector>
#include <QPainter>
#include <QMouseEvent>
#include <QMainWindow>
#include <QMessageBox>
#include "cell.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void initGame();
    void checkWin();
public slots:
    void SwitchGameLevel();
    void update();
private:
    int randX, randY, MinesLeft = 0, openedCells = 0, sec = 0;
    Ui::MainWindow *ui;
    Level GameLevel = EASY;
    QPoint *p = nullptr;
    QRect *rect = nullptr;
    Cell *mycell = nullptr;
    QVector<QVector<Cell*>> cells;
};
#endif // MAINWINDOW_H
