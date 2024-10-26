#include "SOSgame.h"
#include "mainwindow.h"




void SOSgame::checkSOS(int size) {
    //to check for points, we need to check each box against adjacent boxes

    int createdSOS = 0;


    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (checkCell(i,j, size) == true) {
                //This statement is reached when checkCell is called and
                //an SOS is found. At this stage, use 'turn' to determine which
                //player will recieve the point and be able to continue playing
                if (turn % 2 == 0) {
                    //it is player 1's turn
                    p1 ++;
                    createdSOS ++;
                    //mainwindow function to change p1pointsLabel

                }
                else if (turn % 2 != 0){
                    //its is player 2's turn
                    p2 ++;
                    createdSOS ++;

                }
            }
        }
    }

    //Player turn is only incrimented if no SOS was formed in the last turn
    if (createdSOS == 0) {
        turn ++;
    }
}

bool SOSgame::checkCell(int row, int col, int gridSize) {

    QString sequence;

    //check horizontal, vertical, and diagonal
    //horizontal
    if (col <= gridSize - 3) {
        sequence = buttons[row][col]->text() + buttons[row][col + 1]->text() + buttons[row][col + 2]->text();
        if (sequence == "SOS") {
            return true;
        }
    }

    //check verticle
    if (row <= gridSize - 3) {
        sequence = buttons[row][col]->text() + buttons[row + 1][col]->text() + buttons[row + 2][col]->text();
        if (sequence == "SOS") {
            return true;
        }
    }

    //check diagonal down left
    if ((row <= gridSize - 3) && (col >= 2)) {
        sequence = buttons[row][col]->text() + buttons[row + 1][col - 1]->text() + buttons[row + 2][col - 2]->text();
        if (sequence == "SOS") {
            return true;
        }
    }

    //check diagonal down right
    if ((row <= gridSize - 3) && (col <= gridSize - 3)) {
        sequence = buttons[row][col]->text() + buttons[row + 1][col + 1]->text() + buttons[row + 2][col + 2]->text();
        if (sequence == "SOS") {
            return true;
        }
    }

    return false;
}
