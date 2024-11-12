#ifndef CPU_H
#define CPU_H

#include "SOSgame.h"
//#include "mainwindow.h"

class CPU {
public:
    CPU(SOSgame* game);
    void makeMove();  // Function to determine and execute the computer's move
    void setGame(SOSgame* newGame);

private:
    SOSgame* game;
};



#endif // CPU_H
