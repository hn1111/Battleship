#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "pcplayer.h"
#include "field.h"
#include "game.h"
#include "namedialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void askNewGame();
    void displayWinMessage(QString s);
    void updateLabels();
    void about();
    void exit();

private:
    Ui::MainWindow *ui;
    Game *game;
    void askName();


};
#endif // MAINWINDOW_H
