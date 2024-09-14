#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSetSizeButtonClicked();
    void onButtonClicked();

    //void onRadioButtonToggled(bool checked);

private:
    Ui::MainWindow *ui;
    QGridLayout *gridLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *controlLayout;


    void createGrid(int size);
    void checkPoints();
    void clearGrid();
    int gridSize;
    int turn = 0;
};
#endif // MAINWINDOW_H
