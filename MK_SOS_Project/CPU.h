#ifndef CPU_H
#define CPU_H

#include "SOSgame.h"
//#include "mainwindow.h"

class CPU {
public:
    CPU(SOSgame* Game);
    void makeMove();  // Function to determine and execute the computer's move
    void cpuMove();
    void setGame(SOSgame* newGame);
    void setDifficulty(int diff);

private:
    SOSgame* Game;
    int difficulty; //cpu difficulty
};



#endif // CPU_H
