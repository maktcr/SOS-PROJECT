#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QVBoxLayout>
//#include <iostream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //grid layout for resizable game board creation
    QWidget *containerWidget = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout();

    gridLayout = new QGridLayout();
    containerWidget->setLayout(gridLayout);
    mainLayout->addWidget(containerWidget);
    ui->centralWidget->setLayout(mainLayout);

    connect(ui->setSizeButton, &QPushButton::clicked, this, &MainWindow::onSetSizeButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Game;
    delete CPU;
}

void MainWindow::createGrid(int size) {

    clearGrid();

    Game->gridSize = size;;
    Game->buttons.resize(size);
    Game->labels.resize(size);;

    //create the grid of buttons
    for (int i = 0; i < size; ++i) {

        Game->buttons[i].resize(size);
        Game->labels[i].resize(size);

        for (int j = 0; j < size; ++j) {
            QPushButton *button = new QPushButton();
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            // Set a larger font size for the button text
            QFont font = button->font();
            font.setPointSize(16);  // Adjust to the desired font size
            button->setFont(font);

            gridLayout->addWidget(button, i, j);
            connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);

            //stores the button in a vector for easy access later
            Game->buttons[i][j] = button;

            //create a transparent label over the button, this is used for putting the line through the SOS when it is found
            QLabel *label = new QLabel(this);
            label->setAttribute(Qt::WA_TransparentForMouseEvents);
            label->setStyleSheet("background: transparent;");
            gridLayout->addWidget(label, i, j);
            Game->labels[i][j] = label;
        }
    }

    //update labels after grid creation
    updateLabels();
}

void MainWindow::clearGrid() {
    //this function deletes the current grid of buttons on the game board
    Game->turn = 0;

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

void MainWindow::onSetSizeButtonClicked() { //aka, new game button
    //call the new game function
    //this may seem not neccesarry, but i didnt want much logic in the button function itself.
    newGame();
}

void MainWindow::onButtonClicked() {

    //First,check if a radio button is checked. If not, display a warning to the user.
    if ((ui->radioButton->isChecked() == false) && (ui->radioButton_2->isChecked() == false)) {
        QMessageBox::warning(this, "Invalid Input","Please select a radio button to enter an 'S' or an 'O'");
        return;
    }

    //Fill cell function
    fillCell();
}

void MainWindow::newGame() {
    bool ok;
    int newSize = ui->sizeLineEdit->text().toInt(&ok);

    //make sure all inputs are valid
    if ((ok && newSize > 2 && newSize < 11) &&
        (ui->simpleGame->isChecked() || ui->generalGame->isChecked()) &&
        (ui->humanOpp->isChecked() || ui->compOpp->isChecked()) && (ui->humanOpp_2->isChecked() || ui->compOpp_2->isChecked()) ) {

        //all inputs are valid, create a new game based on the inputs
        Game = new SOSgame();
        CPU->setGame(Game);
        createGrid(newSize);
        Game->currentGameMode = ui->simpleGame->isChecked();    //this sets currentGameMode to true for simple game, or false for general game.
        Game->playerOneType = ui->compOpp->isChecked();         //playerOneType set to true if its CPU player
        Game->playerTwoType = ui->compOpp_2->isChecked();       //playerTwoType set to true if its a CPU player
        ui->setSizeButton->setText("New Game");

        //Set up game where player one is CPU
        if (Game->playerOneType && !Game->playerTwoType) {
            CPU->cpuMove();
            updateLabels();
        }

        //Set up game where both players are CPU
        else if (Game->playerOneType && Game->playerTwoType) {
            cpuGame();
        }

    }
    else {
        QMessageBox::warning(this, "Invalid Input","Please select a game mode, opponent type, and a board size greater than 2 and less than 11.");
    }
}

void MainWindow::fillCell() {

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString buttonColor;

    //Set color of the letter before-hand to avoid nesting another if statement.
    //Might nest later if i dont like how it looks//
    if (Game->turn % 2 == 0) {
        //it is player 1's turn
        buttonColor = "color: red;";
    }
    else if (Game->turn % 2 != 0){
        //its is player 2's turn
        buttonColor = "color: blue;";
    }

    //Make sure current grid space is empty before adding new text
    if (button && button->text().isEmpty()) {
        //Checks radio button and inserts text accordingly.
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
        Game->occupiedCells++;
        //after space is filled, check if the player earns a point
        Game->checkSOS();

        //after checkSOS is done, check if game is over
        if (Game->checkGameOver()) {
            clearGrid();
            return;
        }

        //after grid space is filled, call CPU move if a cpu player is active in the current game
        if (Game->playerOneType || Game->playerTwoType) {
            CPU->cpuMove();
        }
    }

    //update labels
    updateLabels();
}

void MainWindow::cpuGame() {

    do {
        CPU->cpuMove();
        updateLabels();
    }
    while (!Game->checkGameOver());
    clearGrid();
}


void MainWindow::updateLabels() {

    //set turn label depending on whose turn it is
    if (Game->turn % 2 == 0) {
        ui->playerTurnLabel->setText("Turn: It is Player One's turn");
    }
    else if (Game->turn % 2 != 0){
        ui->playerTurnLabel->setText("Turn: It is Player Two's turn");
    }

    ui->playerTurnCounterLabel->setText(QString::number(Game->turn));
    ui->p1pointsLabel->setText("Player One Points: " + QString::number(Game->p1));
    ui->p2pointsLabel->setText("Player Two Points: " + QString::number(Game->p2));
}
