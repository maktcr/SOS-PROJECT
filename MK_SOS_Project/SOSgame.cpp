#include "SOSgame.h"

void SOSgame::checkSOS(int size, bool gameMode) {
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
                    //mainwindow function to change p1pointsLabel TOTOTOTOTDODODODOD///////////////////
                }
                else if (turn % 2 != 0){
                    //its is player 2's turn
                    p2 ++;
                    createdSOS ++;
                }
            }
        }
    }
    // if this is a simple game, the game is ended after one SOS is found, this logic is included here.





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
            SOSpos pos = {row, col, "horizontal"};
            if (foundSOS.find(pos) == foundSOS.end()) {
                foundSOS.insert(pos);
                return true;
            }
        }
    }

    //check verticle
    if (row <= gridSize - 3) {
        sequence = buttons[row][col]->text() + buttons[row + 1][col]->text() + buttons[row + 2][col]->text();
        if (sequence == "SOS") {
            SOSpos pos = {row, col, "verticle"};
            if (foundSOS.find(pos) == foundSOS.end()) {
                foundSOS.insert(pos);
                return true;
            }
        }
    }

    //check diagonal down left
    if ((row <= gridSize - 3) && (col >= 2)) {
        sequence = buttons[row][col]->text() + buttons[row + 1][col - 1]->text() + buttons[row + 2][col - 2]->text();
        if (sequence == "SOS") {
            SOSpos pos = {row, col, "diagonal_left"};
            if (foundSOS.find(pos) == foundSOS.end()) {
                foundSOS.insert(pos);
                return true;
            }
        }
    }

    //check diagonal down right
    if ((row <= gridSize - 3) && (col <= gridSize - 3)) {
        sequence = buttons[row][col]->text() + buttons[row + 1][col + 1]->text() + buttons[row + 2][col + 2]->text();
        if (sequence == "SOS") {
            SOSpos pos = {row, col, "diagonal_right"};
            if (foundSOS.find(pos) == foundSOS.end()) {
                foundSOS.insert(pos);
                return true;
            }
        }
    }

    return false;
}
