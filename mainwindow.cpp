#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer ->start(1000);
    ui->label->setText("Прошло времени: " + QString::number(sec));
    initGame();
    ui->label_2->setText(QString::number(MinesLeft));
    connect(ui->actionEasy, SIGNAL(triggered(bool)), this, SLOT(SwitchGameLevel()));
    connect(ui->actionMedium, SIGNAL(triggered(bool)), this, SLOT(SwitchGameLevel()));
    connect(ui->actionHard, SIGNAL(triggered(bool)), this, SLOT(SwitchGameLevel()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent( QPaintEvent *event )
{
    QPainter painter(this);
    for (int i = 0; i < cells.size(); i++){
        for (int j = 0; j < cells[i].size(); j++){
            cells[i][j]->Draw(&painter);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    p = new QPoint(event->x(),event->y());
    for (int i = 0; i < cells.size(); i++){
        for (int j = 0; j < cells[i].size(); j++){
            if(cells[i][j]->Contains(*p)){
                if (event->button() == Qt::RightButton)
                    MinesLeft += cells[i][j]->SetFlag();
                else{
                    cells[i][j]->Open(i, j, cells);
                    if(cells[i][j]->getValue() == MINE)
                        qApp->exit();
                }
            }
        }
    }
    ui->label_2->setText(QString::number(MinesLeft));
    repaint();
    checkWin();
}

void MainWindow::initGame()
{
    srand(time(NULL));
    sec = 0;
    ui->label->setText("Прошло времени: " + QString::number(sec));
    cells.clear();
    if (GameLevel == EASY){
        MinesLeft = EASY_MINES;
        this->setFixedSize(EASY_WINDOW_SIZE, EASY_WINDOW_SIZE + STATUS_PANEL_HEIGHT);
        for(int i = 0; i < EASY_COLS; i++){
            if (cells.size() < EASY_COLS)
                cells.append(QVector<Cell*>());
            for (int j = 0; j < EASY_ROWS; j++) {
                rect = new QRect(i*EASY_CELL_SIZE, STATUS_PANEL_HEIGHT + j*EASY_CELL_SIZE, EASY_CELL_SIZE, EASY_CELL_SIZE);
                mycell = new Cell(*rect);
                cells[i].append(mycell);
            }
        }
        int minesCounter = 0;
        while (minesCounter < EASY_MINES){
            randX = rand() % EASY_COLS;
            randY = rand() % EASY_ROWS;
            if (cells[randX][randY]->getValue() != MINE){
                cells[randX][randY]->setValue(MINE);
                minesCounter++;
                qDebug() << randX << " " << randY;
            }
        }
    } else if (GameLevel == MEDIUM){
        MinesLeft = MEDIUM_MINES;
        this->setFixedSize(MEDIUM_WINDOW_SIZE, MEDIUM_WINDOW_SIZE + STATUS_PANEL_HEIGHT);
        for(int i = 0; i < MEDIUM_COLS; i++){
            if (cells.size() < MEDIUM_COLS)
                cells.append(QVector<Cell*>());
            for (int j = 0; j < MEDIUM_ROWS; j++) {
                rect = new QRect(i*MEDIUM_CELL_SIZE, STATUS_PANEL_HEIGHT + j*MEDIUM_CELL_SIZE, MEDIUM_CELL_SIZE, MEDIUM_CELL_SIZE);
                mycell = new Cell(*rect);
                cells[i].append(mycell);
                }
        }
        int minesCounter = 0;
        while (minesCounter != MEDIUM_MINES){
            randX = rand() % MEDIUM_COLS;
            randY = rand() % MEDIUM_ROWS;
            if (cells[randX][randY]->getValue() != MINE){
                cells[randX][randY]->setValue(MINE);
                minesCounter++;
            }
        }
    } else if (GameLevel == HARD){
        MinesLeft = HARD_MINES;
        this->setFixedSize(HARD_WINDOW_WIDTH, HARD_WINDOW_HEIGHT + STATUS_PANEL_HEIGHT);
        for(int i = 0; i < HARD_COLS; i++){
            if (cells.size() < HARD_COLS)
                cells.append(QVector<Cell*>());
            for (int j = 0; j < HARD_ROWS; j++) {
                rect = new QRect(i*HARD_CELL_SIZE,STATUS_PANEL_HEIGHT + j*HARD_CELL_SIZE, HARD_CELL_SIZE, HARD_CELL_SIZE);
                mycell = new Cell(*rect);
                cells[i].append(mycell);
                }
        }
        int minesCounter = 0;
        while (minesCounter != HARD_MINES){
            randX = rand() % HARD_COLS;
            randY = rand() % HARD_ROWS;
            if (cells[randX][randY]->getValue() != MINE){
                cells[randX][randY]->setValue(MINE);
                minesCounter++;
            }
        }
    }
    repaint();
}

void MainWindow::checkWin()
{
    openedCells = 0;
    for (int i = 0; i < cells.size(); i++){
        for (int j = 0; j < cells[i].size(); j++){
            if (!cells[i][j]->getIs_unopend()){
                openedCells++;
            }
        }
    }
    switch (GameLevel) {
    case EASY:
        if (EASY_CELLS - openedCells == EASY_MINES){
            QMessageBox win(this);
            win.setText("WIN");
            win.exec();
        }
        break;
    case MEDIUM:
        if (MEDIUM_CELLS - openedCells == MEDIUM_MINES){
            QMessageBox win(this);
            win.setText("WIN");
            win.exec();
        }
        break;
    case HARD:
        if (HARD_CELLS - openedCells == HARD_MINES){
            QMessageBox win(this);
            win.setText("WIN");
            win.exec();
        }
        break;
    }
}

void MainWindow::SwitchGameLevel()
{
    QAction *GameMode = (QAction *)sender();
    if (GameMode == ui->actionEasy)
        GameLevel = EASY;
    else if (GameMode == ui->actionMedium)
        GameLevel = MEDIUM;
    else if (GameMode == ui->actionHard)
        GameLevel = HARD;
    initGame();
}

void MainWindow::update()
{
    sec +=1;
    ui->label->setText("Прошло времени: " + QString::number(sec));
}













