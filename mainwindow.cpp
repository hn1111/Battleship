#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    game = new Game();
    ui->fieldCurrentPlayer->setBoard(game->player1, false);
    ui->fieldCurrentPlayer->setGame(game);
    ui->fieldOtherPlayer->setBoard(game->player2, true);
    ui->fieldOtherPlayer->setGame(game);


    updateLabels();


    connect(ui->actionHelp, &QAction::triggered,
            this, &MainWindow::about);

    connect(ui->actionExit, &QAction::triggered,
            this, &MainWindow::exit);

    connect(ui->actionNewGame, &QAction::triggered,
            this, &MainWindow::askNewGame);



    connect(game, &Game::boardChanged,
            ui->fieldCurrentPlayer, &FieldView::updateBoard);

    connect(game, &Game::boardChanged,
            ui->fieldOtherPlayer, &FieldView::updateBoard);

    connect(game, &Game::win,
            this, &MainWindow::displayWinMessage);

    connect(ui->newGameButton, &QPushButton::pressed,
            this, &MainWindow::askNewGame);

    connect(ui->readyButton, &QPushButton::pressed,
            [=]() {
                    ui->fieldCurrentPlayer->setEditable(false);
                    ui->fieldOtherPlayer->setClickable(true);
                    ui->readyButton->setDisabled(true);
            });

    connect(game, &Game::changeTurn,
            this, &MainWindow::updateLabels);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::askNewGame()
{
    auto reply = QMessageBox::question(this,
                                       "New Game",
                                       "Do you want to start new game?");
    if (reply == QMessageBox::Yes) {
        game->startNewGame();
        ui->fieldCurrentPlayer->newGame();
        ui->fieldCurrentPlayer->setEditable(true);
        ui->readyButton->setDisabled(false);
        ui->fieldOtherPlayer->setClickable(false);
        ui->fieldOtherPlayer->setEnemyVisibility(false);
    }
}

void MainWindow::displayWinMessage(QString s)
{
    QMessageBox::information(this, "WIN", s + " win");
    ui->fieldOtherPlayer->setClickable(false);
    ui->fieldOtherPlayer->setEnemyVisibility(true);

}

void MainWindow::updateLabels()
{

    QFont baldFont = QFont();
    baldFont.setPointSize(20);
    QFont nonBaldFont = QFont();
    baldFont.setBold(true);
    if (game->turn == game->player1) {
        ui->labelP1->setFont(baldFont);
        ui->labelP2->setFont(nonBaldFont);
    } else {
        ui->labelP1->setFont(nonBaldFont);
        ui->labelP2->setFont(baldFont);
    }


}

void MainWindow::about()
{
// Might use about later.
//    About* a = new About;
//    a->show();

    QMessageBox::information(this, "Help", "Press LMB or Wheel to rotate");

}

void MainWindow::exit()
{
    QApplication::exit();
}

