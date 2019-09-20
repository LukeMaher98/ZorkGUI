#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ZorkUL.h"
#include "hero.h"
#include <iostream>
#include <string>
using namespace std;
#include <QMainWindow>
#include<QPushButton>
#include<QProgressBar>
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Ui::MainWindow *ui;
    ZorkUL temp;
    Hero player;
    QMediaPlayer music;

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();


private:

    QPushButton *push_button1;
    QPushButton *push_button2;
    QPushButton *push_button3;
    QPushButton *push_button4;
    QPushButton *push_button6;
    QPushButton *push_button7;
    QPushButton *push_button8;
    QPushButton *push_button9;
    QPushButton *push_button10;

    void goDirection(string direction);
    void useItem(int which);

};

#endif // MAINWINDOW_H
