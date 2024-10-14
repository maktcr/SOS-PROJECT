#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QLineEdit>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), gridSize(3) {
    ui->setupUi(this);

    //grid layout for resizable game board creation
    gridLayout = new QGridLayout();
    QWidget *containerWidget = new QWidget();
    containerWidget->setLayout(gridLayout);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(containerWidget);
    ui->centralWidget->setLayout(mainLayout);

    connect(ui->setSizeButton, &QPushButton::clicked, this, &MainWindow::onSetSizeButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGrid(int size) {
    clearGrid();

    gridSize = size;

    //player moves will be kept track of using a 2d vector
    //vect.resize(size);
    //for (auto& row: vect) {
    //    row.resize(size, 0);
    //}
    buttons.clear();
    buttons.resize(size);

    //create a grid of buttons based on the user input
    for (int i = 0; i < size; ++i) {
        buttons[i].resize(size);
        for (int j = 0; j < size; ++j) {
            QPushButton *button = new QPushButton();
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            gridLayout->addWidget(button, i, j);
            connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
            //stores the button in a vector for easy access later
            buttons[i][j] = button;
        }
    }
    //When grid is created, display that it is now player ones turn.
    ui->playerTurnLabel->setText("Turn: It is Player One's turn");
}

void MainWindow::clearGrid() {
    //When clearGrid is called, create a new game environment.
    //First, reset points and turns.
    turn = 0;

    QLayoutItem *item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        QWidget *widget = item->widget();
        if (widget) {
            //deletes existing widget and item to prevent memory leak
            delete widget;
        }
        delete item;
    }
}

void MainWindow::onSetSizeButtonClicked() {
    bool ok;
    int newSize = ui->sizeLineEdit->text().toInt(&ok);

    if (ok && newSize > 2 && newSize < 11) {
        createGrid(newSize);
    }
    else {
        QMessageBox::warning(this, "Invalid Input","Enter a value greater than 2 and less than or equal to 10.");
    }
}

void MainWindow::onButtonClicked() {


    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString buttonColor;



    //All if statements can be nested, but I chose to keep them seperate to improve the readability of the code.

    //First,check if a radio button is checked. If not, display a warning to the user.
    if ((ui->radioButton->isChecked() == false) && (ui->radioButton_2->isChecked() == false)) {
        QMessageBox::warning(this, "Invalid Input","Please select a radio button to enter an 'S' or an 'O'");
        return;
    }


    //Set color of the letter before-hand to avoid nesting another if statement.
    //Might nest later if i dont like how it looks//
    if ((turn == 0) || (turn % 2 == 0)) {
        //it is player 1's turn
        //Text is reversed due to the nature of how this function
        //executes when one of the game board buttons are pressed.
        ui->playerTurnLabel->setText("Turn: It is Player Two's turn");
        buttonColor = "color: red;";
    }
    else if ((turn == 1) || (turn % 2 != 0)){
        //its is player 2's turn
        ui->playerTurnLabel->setText("Turn: It is Player One's turn");
        buttonColor = "color: blue;";
    }

    ui->playerTurnCounterLabel->setText(QString::number(turn)); //QString::number() converts and int into a qstring

    //Make sure current grid space is empty before adding new text
    if (button && button->text().isEmpty()) {
        //Checks radio box and inserts text accordingly.
        //First if executes if first radio button is checked,
        //inserting an S into the space.
        if (ui->radioButton->isChecked() == true) {
            button->setText("S");
            button->setStyleSheet(buttonColor);
        }
        //Else if statement executes if second radio button is checked,
        //inserting an O into the space.
        else if (ui->radioButton_2->isChecked() == true) {
            button->setText("O");
            button->setStyleSheet(buttonColor);
        }
        //after space is filled, check if the player earns a point
        checkSOS();
    }
}


void MainWindow::checkSOS() {
    //to check for points, we need to check each box against adjacent boxes

    int createdSOS = 0;


    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridSize; ++j) {
            if (checkCell(i,j) == true) {
                //This statement is reached when checkCell is called and
                //an SOS is found. At this stage, use 'turn' to determine which
                //player will recieve the point and be able to continue playing
                if ((turn == 0) || (turn % 2 == 0)) {
                    //it is player 1's turn
                    playerOnePoints ++;
                    createdSOS ++;
                    QString newText1 = QString::number(playerOnePoints);
                    ui->p1pointsLabel->setText(newText1);

                }
                else if ((turn == 1) || (turn % 2 != 0)){
                    //its is player 2's turn
                    playerTwoPoints ++;
                    createdSOS ++;
                    QString newText = QString::number(playerTwoPoints);
                    ui->label2->setText(newText);
                }
            }
        }
    }



    //Player turn is only incrimented if no SOS was formed in the last turn
    if (createdSOS == 0) {
        turn ++;
    }
}

bool MainWindow::checkCell(int row, int col) {

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


