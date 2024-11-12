#include "CPU.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <QEventLoop>
#include <QTimer>

CPU::CPU(SOSgame* game) : game(game) {
    std::srand(static_cast<unsigned>(std::time(0)));
}

void CPU::makeMove() {

    QString sequence;

    QEventLoop loop;
    QTimer::singleShot(500, &loop, &QEventLoop::quit);  // Set up a 500 ms blocking delay
    loop.exec();

    //First, we will try to find an "SO sequence" and create an SOS.
    //this logic is similar to that in checkSOS function
    for (int row = 0; row < game->gridSize; row++) {
        for (int col = 0; col < game->gridSize; col++) {
            if (col <= game->gridSize - 3) {

                SOSpos pos = {row, col, "horizontal"};
                //std::cout<< row << ", " << col << std::endl;

                if (game->foundSOS.find(pos) == game->foundSOS.end()) {

                    sequence = game->buttons[row][col]->text() + game->buttons[row][col + 1]->text();

                    if (sequence == "SO" && game->buttons[row][col + 2]->text().isEmpty()) {
                        //Complete the SOS.
                        game->buttons[row][col + 2]->setStyleSheet((game->turn % 2 != 0) ? "color: blue" : "color: red");
                        game->buttons[row][col + 2]->setText("S");

                        std::cout<<"move made at " << row << ", " << col + 2 << std::endl;
                        return;
                    }
                }
            }

            //check verticle
            if (row <= game->gridSize - 3) {

                SOSpos pos = {row, col, "vertical"};

                if (game->foundSOS.find(pos) == game->foundSOS.end()) {

                    sequence = game->buttons[row][col]->text() + game->buttons[row + 1][col]->text();

                    if (sequence == "SO" && game->buttons[row + 2][col]->text().isEmpty()) {
                        game->buttons[row + 2][col]->setStyleSheet((game->turn % 2 != 0) ? "color: blue" : "color: red");
                        game->buttons[row + 2][col]->setText("S");

                        std::cout<<"move made at " << row + 2 << ", " << col << std::endl;
                        return;
                    }
                }
            }

            //check diagonal down left
            if ((row <= game->gridSize - 3) && (col >= 2)) {

                SOSpos pos = {row, col, "diagonal_left"};

                if (game->foundSOS.find(pos) == game->foundSOS.end()) {

                    sequence = game->buttons[row][col]->text() + game->buttons[row + 1][col - 1]->text();

                    if (sequence == "SO" && game->buttons[row + 2][col - 2]->text().isEmpty()) {
                        game->buttons[row + 2][col - 2]->setStyleSheet((game->turn % 2 != 0) ? "color: blue" : "color: red");
                        game->buttons[row + 2][col - 2]->setText("S");

                        std::cout<<"move made at "<< row + 2 << ", " << col - 2 << std::endl;
                        return;
                    }
                }
            }

            //check diagonal down right
            if ((row <= game->gridSize - 3) && (col <= game->gridSize - 3)) {

                SOSpos pos = {row, col, "diagonal_right"};

                if (game->foundSOS.find(pos) == game->foundSOS.end()) {

                    sequence = game->buttons[row][col]->text() + game->buttons[row + 1][col + 1]->text();

                    if (sequence == "SO" && game->buttons[row + 2][col + 2]->text().isEmpty()) {
                        game->buttons[row + 2][col + 2]->setStyleSheet((game->turn % 2 != 0) ? "color: blue" : "color: red");
                        game->buttons[row + 2][col + 2]->setText("S");

                        std::cout<<"move made at " << row + 2 << ", " << col + 2 << std::endl;
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
        row = std::rand() % game->gridSize;
        col = std::rand() % game->gridSize;
    } while (!game->buttons[row][col]->text().isEmpty());

    game->buttons[row][col]->setStyleSheet((game->turn % 2 != 0) ? "color: blue" : "color: red");
    //randomly place an S or an O
    game->buttons[row][col]->setText((std::rand() % 2 == 0) ? "S" : "O");
    std::cout<<"move made at " << row << ", " << col << std::endl;
}

void CPU::setGame(SOSgame* newGame) {
    game = newGame;
}
