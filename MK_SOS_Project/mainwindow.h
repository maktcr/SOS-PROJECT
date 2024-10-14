#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QGridLayout>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

    friend class SOStest;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSetSizeButtonClicked();
    void onButtonClicked();

private:
    Ui::MainWindow *ui;
    QGridLayout *gridLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *controlLayout;

    bool checkCell(int row, int col);
    void createGrid(int size);
    void checkSOS();
    void clearGrid();
    int gridSize;
    int turn = 0;
    double playerOnePoints;
    double playerTwoPoints;
    QVector<QVector<QPushButton*>> buttons;

};
#endif // MAINWINDOW_H
