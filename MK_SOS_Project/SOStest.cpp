#include "mainwindow.h"
#include <QTest>


class SOStest : public QObject {

    Q_OBJECT

private slots:
    void testCreateGrid();
    void testClearGrid();
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










