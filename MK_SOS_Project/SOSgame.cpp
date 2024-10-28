#include "SOSgame.h"
#include <QMessageBox>
#include <QPainter>

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

        SOSpos pos1 = {row, col, "horizontal"};
        SOSpos pos2 = {row, col + 1, "horizontal"};
        SOSpos pos3 = {row, col + 2, "horizontal"};



        if (foundSOS.find(pos1) == foundSOS.end() &&
            foundSOS.find(pos2) == foundSOS.end() &&
            foundSOS.find(pos3) == foundSOS.end()) {

            sequence = buttons[row][col]->text() + buttons[row][col + 1]->text() + buttons[row][col + 2]->text();

            if (sequence == "SOS") {
                foundSOS.insert(pos1);
                foundSOS.insert(pos2);
                foundSOS.insert(pos3);

                //draw line
                drawLine(labels[row][col], "horizontal");
                drawLine(labels[row][col + 1], "horizontal");
                drawLine(labels[row][col + 2], "horizontal");

                return true;
            }

        }
    }



    //check verticle
    if (row <= gridSize - 3) {

        SOSpos pos1 = {row, col, "verticle"};
        SOSpos pos2 = {row + 1, col, "verticle"};
        SOSpos pos3 = {row + 2, col, "verticle"};

        if (foundSOS.find(pos1) == foundSOS.end() &&
            foundSOS.find(pos2) == foundSOS.end() &&
            foundSOS.find(pos3) == foundSOS.end()) {

            sequence = buttons[row][col]->text() + buttons[row + 1][col]->text() + buttons[row + 2][col]->text();
            ;
            if (sequence == "SOS") {

                foundSOS.insert(pos1);
                foundSOS.insert(pos2);
                foundSOS.insert(pos3);

                drawLine(labels[row][col], "vertical");
                drawLine(labels[row + 1][col], "vertical");
                drawLine(labels[row + 2][col], "vertical");

                return true;
            }
        }
    }

    //check diagonal down left
    if ((row <= gridSize - 3) && (col >= 2)) {
        sequence = buttons[row][col]->text() + buttons[row + 1][col - 1]->text() + buttons[row + 2][col - 2]->text();
        if (sequence == "SOS") {
            SOSpos pos1 = {row, col, "diagonal_left"};
            SOSpos pos2 = {row + 1, col - 1, "diagonal_left"};
            SOSpos pos3 = {row + 2, col - 2, "diagonal_left"};
            if (foundSOS.find(pos1) == foundSOS.end() &&
                foundSOS.find(pos2) == foundSOS.end() &&
                foundSOS.find(pos3) == foundSOS.end()) {

                foundSOS.insert(pos1);
                foundSOS.insert(pos2);
                foundSOS.insert(pos3);

                drawLine(labels[row][col], "diagonal_left");
                drawLine(labels[row + 1][col - 1], "diagonal_left");
                drawLine(labels[row + 2][col - 2], "diagonal_left");

                return true;
            }
        }
    }

    //check diagonal down right
    if ((row <= gridSize - 3) && (col <= gridSize - 3)) {
        sequence = buttons[row][col]->text() + buttons[row + 1][col + 1]->text() + buttons[row + 2][col + 2]->text();
        if (sequence == "SOS") {

            SOSpos pos1 = {row, col, "diagonal_right"};
            SOSpos pos2 = {row + 1, col + 1, "diagonal_right"};
            SOSpos pos3 = {row + 2, col + 2, "diagonal_right"};

            if (foundSOS.find(pos1) == foundSOS.end() &&
                foundSOS.find(pos2) == foundSOS.end() &&
                foundSOS.find(pos3) == foundSOS.end()) {

                foundSOS.insert(pos1);
                foundSOS.insert(pos2);
                foundSOS.insert(pos3);

                drawLine(labels[row][col], "diagonal_right");
                drawLine(labels[row + 1][col + 1], "diagonal_right");
                drawLine(labels[row + 2][col + 2], "diagonal_right");

                return true;
            }
        }
    }

    return false;
}

bool SOSgame::checkGameOver(bool mode) {

    if (mode == true && ((p1 > 0) | (p2 > 0))) {
        //in a simple game, the game is over once a single SOS is found, if its not a simple game, continue
        if (p1 == 1) {
            QMessageBox::warning(this, "Player One is the winner!","You may continue playing this game to the end, or start a new one");
        }
        if (p2 == 1) {
            QMessageBox::warning(this, "Player Two is the winner!","You may continue playing this game to the end, or start a new one");
        }
        return true;
    }
    else if (mode == true && (occupiedCells == gridSize * gridSize)) {
        QMessageBox::warning(this, "DRAW", "Game has ended in a Draw!");
        return true;
    }
    //in a general game, the game is over once the whole board is full.
    else if (mode == false && (occupiedCells == gridSize * gridSize)) {

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

void SOSgame::drawLine(QLabel *label, const QString &direction) {
    QPixmap pixmap(label->size());
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 3));

    if (direction == "horizontal") {
        painter.drawLine(0, label->height() / 2, label->width(), label->height() / 2);;
    }
    else if (direction == "verticle") {
        painter.drawLine(label->width() / 2, 0, label->width() / 2, label->height());
    }
    else if (direction == "diagonal_left") {
        painter.drawLine(label->width(), 0, 0, label->height());
    }
    else if (direction == "diagonal_right") {
        painter.drawLine(0, 0, label->width(), label->height());;
    }

    painter.end();
    label->setPixmap(pixmap);
}
