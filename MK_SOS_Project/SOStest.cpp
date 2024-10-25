#include "mainwindow.h"
#include <QTest>


class SOStest : public QObject {

    Q_OBJECT

private slots:
    void testCreateGrid();
    void testClearGrid();
    void testSizeButton();
};

void SOStest::testCreateGrid() {

    MainWindow testClass;
    int testInput = 3;

    testClass.createGrid(testInput);

    QCOMPARE(testClass.buttons.size(), testInput);
    QCOMPARE(testClass.gridSize, testInput);

}

void SOStest::testClearGrid() {

    MainWindow testClass;
    int testInput = 3;

    testClass.createGrid(testInput);
    testClass.clearGrid();

    QCOMPARE(testClass.gridSize, 0);
    QCOMPARE(testClass.buttons.size(), 0);
}

//chatgpt unit test...
void SOStest::testSizeButton() {

    //testing valid input on testSizeButton

    MainWindow testClass;
    testClass.show();

    //connect to the text box to edit its contents
    QLineEdit *lineEdit = testClass.findChild<QLineEdit*>("sizeLineEdit");
    lineEdit->setText("5");

    //simulate button press
    QPushButton *button = testClass.findChild<QPushButton*>("setSizeButton");
    QVERIFY(button != nullptr);
    QTest::mouseClick(button, Qt::LeftButton);

    //verify that the grid has been created with the correct size
    QCOMPARE(testClass.buttons.size(), 5);
    for (int i = 0; i < 5; i++) {
        QCOMPARE(testClass.buttons[i].size(), 5);
    }


}








