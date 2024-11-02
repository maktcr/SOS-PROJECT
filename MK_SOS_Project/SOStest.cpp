#ifndef TEST

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTest>
#include <QMessageBox>

class SOStest : public QObject {

    Q_OBJECT

private slots:
    void testCreateGrid();
    void testClearGrid();
    void testSizeButton();
    void testSimpleGame();
    void testGeneralGame();

private:
    MainWindow *testClass;

};

void SOStest::testCreateGrid() {

    MainWindow tempTestClass;
    int testInput = 3;

    tempTestClass.createGrid(testInput);

    QCOMPARE(tempTestClass.Game->buttons.size(), testInput);
    QCOMPARE(tempTestClass.Game->gridSize, testInput);

}

void SOStest::testClearGrid() {

    MainWindow tempTestClass;
    int testInput = 3;

    tempTestClass.createGrid(testInput);
    tempTestClass.clearGrid();

    QCOMPARE(tempTestClass.Game->gridSize, 0);
    QCOMPARE(tempTestClass.Game->buttons.size(), 0);
}

//chatgpt unit test...
void SOStest::testSizeButton() {

    //testing valid input on testSizeButton

    MainWindow tempTestClass;
    //testClass->show();

    //connect to the text box to edit its contents
    QLineEdit *lineEdit = tempTestClass.findChild<QLineEdit*>("sizeLineEdit");
    lineEdit->setText("5");

    //simulate button press
    QPushButton *button = tempTestClass.findChild<QPushButton*>("setSizeButton");
    QVERIFY(button != nullptr);
    QTest::mouseClick(button, Qt::LeftButton);

    //verify that the grid has been created with the correct size
    QCOMPARE(tempTestClass.Game->buttons.size(), 5);
    for (int i = 0; i < 5; i++) {
        QCOMPARE(tempTestClass.Game->buttons[i].size(), 5);
    }
}


void SOStest::testSimpleGame() {

    // Set up a 3x3 grid for testing, enable simple game mode
    testClass->createGrid(3);
    testClass->Game->currentGameMode = true;

    //test horizontal SOS detection using first 3 cells
    testClass->ui->radioButton->setChecked(true);
    testClass->Game->buttons[0][0]->click();
    testClass->ui->radioButton_2->setChecked(true);
    testClass->Game->buttons[0][1]->click();
    testClass->ui->radioButton->setChecked(true);
    testClass->Game->buttons[0][2]->click();

    // Check if SOS was detected horizontally and game ends
    QVERIFY(testClass->Game->checkCell(0, 0) == true);
    QVERIFY(testClass->Game->checkGameOver(true) == true);

    // Reset the grid
    testClass->createGrid(3);

    //testvertical SOS detection
    testClass->ui->radioButton->setChecked(true);
    testClass->Game->buttons[0][0]->click();
    testClass->ui->radioButton_2->setChecked(true);
    testClass->Game->buttons[1][0]->click();
    testClass->ui->radioButton->setChecked(true);
    testClass->Game->buttons[2][0]->click();

    // Check if SOS was detected vertically and game ends
    QVERIFY(testClass->Game->checkCell(0, 0) == true);
    QVERIFY(testClass->Game->checkGameOver(true) == true);

    // Reset the grid
    testClass->createGrid(3);

    // Testing diagonal SOS detection
    testClass->ui->radioButton->setChecked(true);
    testClass->Game->buttons[0][0]->click();
    testClass->ui->radioButton_2->setChecked(true);
    testClass->Game->buttons[1][1]->click();
    testClass->ui->radioButton->setChecked(true);
    testClass->Game->buttons[2][2]->click();

    // Check if SOS was detected diagonally and game ends
    QVERIFY(testClass->Game->checkCell(0, 0) == true);
    QVERIFY(testClass->Game->checkGameOver(true) == true);
}

void SOStest::testGeneralGame() {

    // Set up a 3x3 grid for testing, enable simple game mode
    testClass->createGrid(3);
    testClass->Game->currentGameMode = false;

    //test horizontal SOS detection using first 3 cells
    testClass->ui->radioButton->setChecked(true);
    testClass->Game->buttons[0][0]->click();
    testClass->ui->radioButton_2->setChecked(true);
    testClass->Game->buttons[0][1]->click();
    testClass->ui->radioButton->setChecked(true);
    testClass->Game->buttons[0][2]->click();

    // Check if SOS was detected horizontally and game ends
    QVERIFY(testClass->Game->checkCell(0, 0) == true);
    QVERIFY(testClass->Game->checkGameOver(false) == false);

    // Reset the grid
    testClass->createGrid(3);

    //test vertical SOS detection
    testClass->ui->radioButton->setChecked(true);
    testClass->Game->buttons[0][0]->click();
    testClass->ui->radioButton_2->setChecked(true);
    testClass->Game->buttons[1][0]->click();
    testClass->ui->radioButton->setChecked(true);
    testClass->Game->buttons[2][0]->click();

    // Check if SOS was detected vertically and game ends
    QVERIFY(testClass->Game->checkCell(0, 0) == true);
    QVERIFY(testClass->Game->checkGameOver(false) == false);

    // Reset the grid
    testClass->createGrid(3);

    // Testing diagonal SOS detection
    testClass->ui->radioButton->setChecked(true);
    testClass->Game->buttons[0][0]->click();
    testClass->ui->radioButton_2->setChecked(true);
    testClass->Game->buttons[1][1]->click();
    testClass->ui->radioButton->setChecked(true);
    testClass->Game->buttons[2][2]->click();

    // Check if SOS was detected diagonally and game ends
    QVERIFY(testClass->Game->checkCell(0, 0) == true);
    QVERIFY(testClass->Game->checkGameOver(true) == true);
}


QTEST_GUILESS_MAIN(SOStest);
#include "SOStest.moc"

#endif
