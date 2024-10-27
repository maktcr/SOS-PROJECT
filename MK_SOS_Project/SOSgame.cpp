#include "SOSgame.h"
#include <QMessageBox>

void SOSgame::checkSOS() {
    //to check for points, we need to check each box against adjacent boxes

    int createdSOS = 0;


    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (checkCell(i,j) == true) {
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

    //Player turn is only incrimented if no SOS was formed in the last turn
    if (createdSOS == 0) {
        turn ++;
    }
}

bool SOSgame::checkCell(int row, int col) {

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

bool SOSgame::checkGameOver(bool mode) {

    if (mode == true && (p1 | p2 > 0)) {
        //in a simple game, the game is over once a single SOS is found, if its not a simple game, continue
        if (p1 == 1) {
            QMessageBox::warning(this, "Player One is the winner!","You may continue playing this game to the end, or start a new one");
        }
        if (p2 == 1) {
            QMessageBox::warning(this, "Player Two is the winner!","You may continue playing this game to the end, or start a new one");
        }
        return true;
    }
    //in a general game, the game is over once the whole board is full.
    else if (mode == false && (occupiedCells >= gridSize)) {

        if (p1 > p2) {
            QMessageBox::warning(this, "Player One is the winner!","Please use the new game button to start a new game.");
        }
        else if (p2 > p1) {
            QMessageBox::warning(this, "Player Two is the winner!","Please use the new game button to start a new game.");
        }
        else {
            QMessageBox::warning(this, "Game has ended in a Draw!","Please use the new game button to start a new game.");
        }
        return true;
    }
    else {
        return false;
    }


}
