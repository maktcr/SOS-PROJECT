#include "SOSgame.h"
#include <QMessageBox>
#include <QPainter>

void SOSgame::checkSOS() {
    //to check for points, we need to check each box against adjacent boxes

    int createdSOS = 0;


    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            int sosCount = checkCell(i, j);
            if (sosCount > 0) {
                //This statement is reached when checkCell is called and
                //an SOS is found. At this stage, use 'turn' to determine which
                //player will recieve the point and be able to continue playing
                if (turn % 2 == 0) {
                    //it is player 1's turn
                    p1 += sosCount;
                    createdSOS += sosCount;
                }
                else if (turn % 2 != 0){
                    //its is player 2's turn
                    p2 += sosCount;
                    createdSOS += sosCount;
                }
            }
        }
    }

    //Player turn is only incrimented if no SOS was formed in the last turn
    if (createdSOS == 0) {
        turn ++;
    }
}

int SOSgame::checkCell(int row, int col) {

    QString sequence;
    int sosCount = 0;

    //check horizontal, vertical, and diagonal
    //horizontal
    if (col <= gridSize - 3) {

        SOSpos pos = {row, col, "horizontal"};
        //ensures that SOS's arent counted twice
        if (foundSOS.find(pos) == foundSOS.end()) {
            //create a sequence and check if its an SOS
            sequence = buttons[row][col]->text() + buttons[row][col + 1]->text() + buttons[row][col + 2]->text();

            if (sequence == "SOS") {
                //if SOS is found, insert it into foundSOS set to ensure it isnt counted again
                foundSOS.insert(pos);

                //when sos is found, draw a line
                drawLine(labels[row][col], "horizontal");
                drawLine(labels[row][col + 1], "horizontal");
                drawLine(labels[row][col + 2], "horizontal");
                //incriment sosCount, which is used for determining when the player turn is incrimented
                sosCount++;
            }

        }
    }

    //check verticle
    if (row <= gridSize - 3) {

        SOSpos pos = {row, col, "vertical"};

        if (foundSOS.find(pos) == foundSOS.end()) {

            sequence = buttons[row][col]->text() + buttons[row + 1][col]->text() + buttons[row + 2][col]->text();

            if (sequence == "SOS") {

                foundSOS.insert(pos);

                drawLine(labels[row][col], "vertical");
                drawLine(labels[row + 1][col], "vertical");
                drawLine(labels[row + 2][col], "vertical");
                sosCount++;
            }
        }
    }

    //check diagonal down left
    if ((row <= gridSize - 3) && (col >= 2)) {

        SOSpos pos = {row, col, "diagonal_left"};

        if (foundSOS.find(pos) == foundSOS.end()) {

            sequence = buttons[row][col]->text() + buttons[row + 1][col - 1]->text() + buttons[row + 2][col - 2]->text();

            if (sequence == "SOS") {

                foundSOS.insert(pos);

                drawLine(labels[row][col], "diagonal_left");
                drawLine(labels[row + 1][col - 1], "diagonal_left");
                drawLine(labels[row + 2][col - 2], "diagonal_left");
                sosCount++;
            }
        }
    }

    //check diagonal down right
    if ((row <= gridSize - 3) && (col <= gridSize - 3)) {

        SOSpos pos = {row, col, "diagonal_right"};

        if (foundSOS.find(pos) == foundSOS.end()) {

            sequence = buttons[row][col]->text() + buttons[row + 1][col + 1]->text() + buttons[row + 2][col + 2]->text();

            if (sequence == "SOS") {

                foundSOS.insert(pos);

                drawLine(labels[row][col], "diagonal_right");
                drawLine(labels[row + 1][col + 1], "diagonal_right");
                drawLine(labels[row + 2][col + 2], "diagonal_right");
                sosCount++;
            }
        }
    }

    return sosCount;
}

bool SOSgame::checkGameOver() {
    // in a simple game, the game is over once a single SOS is found or when the board is filled
    if ((currentGameMode == true && (p1 > 0 || p2 > 0)) || (currentGameMode == true && occupiedCells == gridSize * gridSize)) {
        return true;
    }
    // in a general game, the game is over once the whole board is full.
    else if (currentGameMode == false && (occupiedCells == gridSize * gridSize)) {
        return true;
    }
    else {
        return false;
    }
}

void SOSgame::gameOver() {
    //player One win
    if (p1 > p2) {
        QMessageBox::warning(this, "Player One is the winner!","Please use the new game button to start a new game.");
    }
    //player two win
    else if (p1 < p2) {
        QMessageBox::warning(this, "Player Two is the winner!","Please use the new game button to start a new game.");
    }
    //draw
    else {
        QMessageBox::warning(this, "Game has ended in a Draw!","Please use the new game button to start a new game.");
    }
}

void SOSgame::drawLine(QLabel *label, const QString &direction) {

    QPixmap pixmap;
    if (labelPixmaps.contains(label)) {
        pixmap = labelPixmaps[label];  // retrieve the existing pixmap if it exists
    } else {
        pixmap = QPixmap(label->size());
        pixmap.fill(Qt::transparent);  // initialize a new pixmap as transparent only once
    }


    // Use a painter to draw on the pixmap
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);  // this smooths out the lines
    painter.setPen(QPen(Qt::black, 3));

    // draw the new line based on the specified direction
    if (direction == "horizontal") {
        painter.drawLine(0, label->height() / 2, label->width(), label->height() / 2);
    }
    else if (direction == "vertical") {
        painter.drawLine(label->width() / 2, 0, label->width() / 2, label->height());
    }
    else if (direction == "diagonal_left") {
        painter.drawLine(label->width(), 0, 0, label->height());
    }
    else if (direction == "diagonal_right") {
        painter.drawLine(0, 0, label->width(), label->height());
    }

    // end the painter and set the updated pixmap back to the label
    painter.end();
    labelPixmaps[label] = pixmap;
    label->setPixmap(pixmap);
}

QVector<QVector<QPushButton*>> SOSgame::getGridButtons() const {
    return buttons;
}


