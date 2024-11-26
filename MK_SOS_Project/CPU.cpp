#include "CPU.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QEventLoop>
#include <QTimer>
#include <fstream>


CPU::CPU(SOSgame* Game) : Game(Game) {
    std::srand(static_cast<unsigned>(std::time(0)));
}

void CPU::makeMove() {

    QString sequence;

    std::ofstream file("gameRecord.txt", std::ios::app);

    //set up a delay for cpu players turn
    QEventLoop loop;
    QTimer::singleShot(500, &loop, &QEventLoop::quit);
    loop.exec();

    //First, we will try to find an "SO sequence" and create an SOS.
    //this logic is similar to that in checkSOS function
    for (int row = 0; row < Game->gridSize; row++) {
        for (int col = 0; col < Game->gridSize; col++) {
            if (col <= Game->gridSize - 3) {

                SOSpos pos = {row, col, "horizontal"};


                if (Game->foundSOS.find(pos) == Game->foundSOS.end()) {

                    sequence = Game->buttons[row][col]->text() + Game->buttons[row][col + 1]->text();

                    if (sequence == "SO" && Game->buttons[row][col + 2]->text().isEmpty()) {
                        //Complete the SOS.
                        Game->buttons[row][col + 2]->setStyleSheet((Game->turn % 2 != 0) ? "color: blue" : "color: red");
                        Game->buttons[row][col + 2]->setText("S");

                        std::string player = (Game->turn % 2 == 0) ? "PlayerOne" : "PlayerTwo";
                        file << player << "," << Game->buttons[row][col + 2]->text().toStdString() << "," << Game->buttons[row][col + 2]->property("row").toInt() << " " << Game->buttons[row][col + 2]->property("col").toInt() << std::endl;
                        return;
                    }
                }
            }

            //check verticle
            if (row <= Game->gridSize - 3) {

                SOSpos pos = {row, col, "vertical"};

                if (Game->foundSOS.find(pos) == Game->foundSOS.end()) {

                    sequence = Game->buttons[row][col]->text() + Game->buttons[row + 1][col]->text();

                    if (sequence == "SO" && Game->buttons[row + 2][col]->text().isEmpty()) {
                        Game->buttons[row + 2][col]->setStyleSheet((Game->turn % 2 != 0) ? "color: blue" : "color: red");
                        Game->buttons[row + 2][col]->setText("S");

                        std::string player = (Game->turn % 2 == 0) ? "PlayerOne" : "PlayerTwo";
                        file << player << "," << Game->buttons[row + 2][col]->text().toStdString() << "," << Game->buttons[row + 2][col]->property("row").toInt() << " " << Game->buttons[row + 2][col]->property("col").toInt() << std::endl;
                        return;
                    }
                }
            }

            //check diagonal down left
            if ((row <= Game->gridSize - 3) && (col >= 2)) {

                SOSpos pos = {row, col, "diagonal_left"};

                if (Game->foundSOS.find(pos) == Game->foundSOS.end()) {

                    sequence = Game->buttons[row][col]->text() + Game->buttons[row + 1][col - 1]->text();

                    if (sequence == "SO" && Game->buttons[row + 2][col - 2]->text().isEmpty()) {
                        Game->buttons[row + 2][col - 2]->setStyleSheet((Game->turn % 2 != 0) ? "color: blue" : "color: red");
                        Game->buttons[row + 2][col - 2]->setText("S");

                        std::string player = (Game->turn % 2 == 0) ? "PlayerOne" : "PlayerTwo";
                        file << player << "," << Game->buttons[row + 2][col - 2]->text().toStdString() << "," << Game->buttons[row + 2][col - 2]->property("row").toInt() << " " << Game->buttons[row + 2][col - 2]->property("col").toInt() << std::endl;
                        return;
                    }
                }
            }

            //check diagonal down right
            if ((row <= Game->gridSize - 3) && (col <= Game->gridSize - 3)) {

                SOSpos pos = {row, col, "diagonal_right"};

                if (Game->foundSOS.find(pos) == Game->foundSOS.end()) {

                    sequence = Game->buttons[row][col]->text() + Game->buttons[row + 1][col + 1]->text();

                    if (sequence == "SO" && Game->buttons[row + 2][col + 2]->text().isEmpty()) {
                        Game->buttons[row + 2][col + 2]->setStyleSheet((Game->turn % 2 != 0) ? "color: blue" : "color: red");
                        Game->buttons[row + 2][col + 2]->setText("S");

                        std::string player = (Game->turn % 2 == 0) ? "PlayerOne" : "PlayerTwo";
                        file << player << "," << Game->buttons[row + 2][col + 2]->text().toStdString() << "," << Game->buttons[row + 2][col + 2]->property("row").toInt() << " " << Game->buttons[row + 2][col + 2]->property("col").toInt() << std::endl;
                        return;
                    }
                }
            }

        }
    }

    //this is reached if no "SO" sequence is found.
    //select a random empty cell and place either an S or an O.
    int row, col;
    do {
        row = std::rand() % Game->gridSize;
        col = std::rand() % Game->gridSize;
    } while (!Game->buttons[row][col]->text().isEmpty());

    Game->buttons[row][col]->setStyleSheet((Game->turn % 2 != 0) ? "color: blue" : "color: red");
    //randomly place an S or an O
    Game->buttons[row][col]->setText((std::rand() % 2 == 0) ? "S" : "O");

    std::string player = (Game->turn % 2 == 0) ? "PlayerOne" : "PlayerTwo";
    file << player << "," << Game->buttons[row][col]->text().toStdString() << "," << Game->buttons[row][col]->property("row").toInt() << " " << Game->buttons[row][col]->property("col").toInt() << std::endl;
    file.close();
}

void CPU::cpuMove() {
    //condition for player two is CPU but player one is human
    if (Game->playerTwoType && !Game->playerOneType) {
        if (Game->turn % 2 != 0) {
            while(Game->turn % 2 !=0) {
                makeMove();
                Game->occupiedCells++;
                Game->checkSOS();
                if (Game->checkGameOver()) {
                    return;
                }
            }
        }
    }
    //condition for player one is CPU but player two is human
    else if (Game->playerOneType && !Game->playerTwoType) {
        if (Game->turn % 2 == 0) {
            while(Game->turn % 2 == 0) {
                makeMove();
                Game->occupiedCells++;
                Game->checkSOS();
                if (Game->checkGameOver()) {
                    return;
                }
            }
        }
    }
    //condition for if both players are CPU
    else if (Game->playerOneType && Game->playerTwoType) {
        if (Game->turn % 2 != 0) {
            while(Game->turn % 2 != 0) {
                makeMove();
                Game->occupiedCells++;
                Game->checkSOS();
                if (Game->checkGameOver()) {
                    return;
                }
            }
        }
        else if (Game->turn % 2 == 0) {
            while(Game->turn % 2 ==0) {
                makeMove();
                Game->occupiedCells++;
                Game->checkSOS();
                if (Game->checkGameOver()) {
                    return;
                }
            }
        }
    }
}

void CPU::setGame(SOSgame* newGame) {
    Game = newGame;
}
