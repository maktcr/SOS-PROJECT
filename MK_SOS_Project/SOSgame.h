#ifndef SOSGAME_H
#define SOSGAME_H

#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <set>
#include <tuple>

//this struct helps keep track of sos's that have been found
struct SOSpos {
    int row, col;
    std::string direction;

    bool operator<(const SOSpos &other) const {
        return std::tie(row,col,direction) < std::tie(other.row,other.col,other.direction);
    }
};





class SOSgame : public QMainWindow {
    friend class MainWindow;
public:


private:

    bool checkCell(int row, int col, int size);
    void checkSOS(int size, bool gameMode);

    int turn = 0;

    int p1;  //stores player 1 points
    int p2;  //stores player 2 points
    std::set<SOSpos> foundSOS; //track the sos's found
    QVector<QVector<QPushButton*>> buttons;
};


#endif // SOSGAME_H
