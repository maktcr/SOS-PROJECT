#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QMainWindow>
#include "SOSgame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    friend class SOSgame;
    friend class SOStest;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSetSizeButtonClicked();
    void onButtonClicked();

private:
    Ui::MainWindow *ui;
    QGridLayout *gridLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *controlLayout;

    SOSgame game;

    void createGrid(int size);
    void clearGrid();
    static void setP1Label();
    static void setP2Label();
    static int gridSize;


    static int getGridSize() {
        return gridSize;
    }

};
#endif // MAINWINDOW_H
