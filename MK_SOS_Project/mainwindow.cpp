#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QVBoxLayout>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //grid layout for resizable game board creation
    gridLayout = new QGridLayout();
    QWidget *containerWidget = new QWidget();
    containerWidget->setLayout(gridLayout);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(containerWidget);
    ui->centralWidget->setLayout(mainLayout);

    //might work might not
    simpleGame = new SOSgame();
    generalGame = new SOSgame();

    connect(ui->setSizeButton, &QPushButton::clicked, this, &MainWindow::onSetSizeButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createGrid(int size, SOSgame *game) {
    clearGrid();

    gridSize = size;

    //player moves will be kept track of using a 2d vector
    //vect.resize(size);
    //for (auto& row: vect) {
    //    row.resize(size, 0);
    //}

    game->buttons.clear();
    game->buttons.resize(size);


    //create a grid of buttons based on the user input
    for (int i = 0; i < size; ++i) {
        game->buttons[i].resize(size);
        for (int j = 0; j < size; ++j) {
            QPushButton *button = new QPushButton();
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            gridLayout->addWidget(button, i, j);
            connect(button, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
            //stores the button in a vector for easy access later
            game->buttons[i][j] = button;
        }
    }
    //When grid is created, display that it is now player ones turn.
    ui->playerTurnLabel->setText("Turn: It is Player One's turn");
}

void MainWindow::clearGrid() {
    //When clearGrid is called, create a new game environment.
    //First, reset points and turns.
    simpleGame->turn = 0;
    generalGame ->turn = 0;

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
    bool ok;
    int newSize = ui->sizeLineEdit->text().toInt(&ok);

    if (ok && newSize > 2 && newSize < 11) {
        if (ui->simpleGame->isChecked()) {
            createGrid(newSize, simpleGame);
            currentGameMode = true;
        }
        else if (ui->generalGame->isChecked()) {
            createGrid(newSize, generalGame);
            currentGameMode = false;
        }
    }
    else {
        QMessageBox::warning(this, "Invalid Input","Enter a value greater than 2 and less than or equal to 10.");
    }
}

void MainWindow::onButtonClicked() {

    //First,check if a radio button is checked. If not, display a warning to the user.
    if ((ui->radioButton->isChecked() == false) && (ui->radioButton_2->isChecked() == false)) {
        QMessageBox::warning(this, "Invalid Input","Please select a radio button to enter an 'S' or an 'O'");
        return;
    }

    //Fill cell function
    if (currentGameMode == true) {
        fillCell(simpleGame);
    }
    else if (currentGameMode == false) {
        fillCell(generalGame);
    }
}

void MainWindow::fillCell(SOSgame *game) {

    QPushButton *button = qobject_cast<QPushButton*>(sender());
    QString buttonColor;

    //Set color of the letter before-hand to avoid nesting another if statement.
    //Might nest later if i dont like how it looks//
    if (game->turn % 2 == 0) {
        //it is player 1's turn
        //Text is reversed due to the nature of how this function
        //executes when one of the game board buttons are pressed.
        ui->playerTurnLabel->setText("Turn: It is Player Two's turn");
        buttonColor = "color: red;";
    }
    else if (game->turn % 2 != 0){
        //its is player 2's turn
        ui->playerTurnLabel->setText("Turn: It is Player One's turn");
        buttonColor = "color: blue;";
    }

    ui->playerTurnCounterLabel->setText(QString::number(game->turn)); //QString::number() converts and int into a qstring

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
        game->checkSOS(gridSize);
    }
}


