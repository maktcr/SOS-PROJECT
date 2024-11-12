#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "SOSgame.h"
#include "CPU.h"
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    friend class SOSgame;
    friend class SOStest;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *ui;

    QVector<QVector<QPushButton*>> getGridButtons() const;  //for computer player logic
    bool currentGameMode; //true for simple, false for general

private slots:
    void onSetSizeButtonClicked();
    void onButtonClicked();

private:
    SOSgame *Game;
    CPU *CPU;

    QGridLayout *gridLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *controlLayout;

    void updateLabels();
    void delay();
    void cpuMove();
    void createGrid(int size);
    void fillCell();
    void newGame();
    void clearGrid();
};

#endif // MAINWINDOW_H
