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

    Game = new SOSgame();

    connect(ui->setSizeButton, &QPushButton::clicked, this, &MainWindow::onSetSizeButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
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

        delete Game;

        if (ui->simpleGame->isChecked()) {
            Game = new SOSgame();
            createGrid(newSize);
            Game->currentGameMode = true;
            currentGameMode = true;
        }
        else if (ui->generalGame->isChecked()) {
            Game = new SOSgame();
            createGrid(newSize);
            Game->currentGameMode = false;
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
    fillCell();
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
        //Checks radio box and inserts text accordingly.
        //First if executes if first radio button is checked,
        //inserting an S into the space.
        if (ui->radioButton->isChecked() == true) {
            button->setText("S");
            button->setStyleSheet(buttonColor);
            Game->occupiedCells++;
        }
        //Else if statement executes if second radio button is checked,
        //inserting an O into the space.
        else if (ui->radioButton_2->isChecked() == true) {
            button->setText("O");
            button->setStyleSheet(buttonColor);
            Game->occupiedCells++;
        }

        //after space is filled, check if the player earns a point
        Game->checkSOS();

        //after checkSOS is done, check if game is over
        //this function is where proper code goes to die
        if (Game->checkGameOver(currentGameMode)) {
            clearGrid();
        }
    }

    //update labels
    updateLabels();
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
    ui->p1pointsLabel->setText(QString::number(Game->p1));
    ui->p2pointsLabel->setText(QString::number(Game->p2));
}
