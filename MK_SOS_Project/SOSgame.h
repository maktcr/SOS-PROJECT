#ifndef SOSGAME_H
#define SOSGAME_H

#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QMainWindow>


class SOSgame : public QMainWindow {
    friend class MainWindow;
public:

private:
    bool checkCell(int row, int col);

    void checkSOS();
    int turn = 0;
    static double p1;  //stores player 1 points
    static double p2;  //stores player 2 points
    QVector<QVector<QPushButton*>> buttons;
};


#endif // SOSGAME_H
