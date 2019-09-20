#include <iostream>
#include <ctime>
#include <QApplication>
#include <QScrollBar>
#include <QProgressBar>
#include <QDesktopWidget>
#include <QSoundEffect>

using namespace std;
#include "ZorkUL.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "hero.h"

ZorkUL temp;
Hero player;
QMediaPlayer *music = new QMediaPlayer();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QDesktopWidget dw;
    temp.createRooms();
    ui->setupUi(this);
    this->setFixedSize(1344, 756);
    ui->progressBar->setValue(player.getHealth());
    ui->progressBar_2->setValue(player.stamina);
    ui->progressBar_3->setValue(0);
    ui->textEdit->setReadOnly(true);
    ui->textEdit_2->setStyleSheet("background-image:url(:/images/amap.png);");
    ui->textEdit->setStyleSheet("background-image:url(:/images/a.jpg); font: 75 20pt Constantia; color: gold; background-attachment: fixed;");
    ui->textEdit->insertPlainText("[WELCOME TO ZORK - DEFEAT ALL ENEMIES TO WIN!]");
    ui->textEdit->insertPlainText(QString::fromStdString(player.longDescription()));
    ui->textEdit->insertPlainText(QString::fromStdString(temp.currentRoom->longDescription() + "\n"));
    music.setMedia(QUrl("qrc:/audio/bgmusic.wav"));
    music.setVolume(10);
    music.play();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->goDirection("north");
}

void MainWindow::on_pushButton_2_clicked()
{
    this->goDirection("south");
}

void MainWindow::on_pushButton_3_clicked()
{
    this->goDirection("west");
}

void MainWindow::on_pushButton_4_clicked()
{
    this->goDirection("east");
}

void MainWindow::on_pushButton_6_clicked()
{
    if(player.getStatus() != "dead"){
        ui->textEdit->clear();
        setStamina(player, player.stamina - 10);
        if(!player.checkStamina()){
            ui->textEdit->insertPlainText("You collapse from exhaustion...\n[GAME OVER]");
            player.setDead();
        }
        ui->textEdit->insertPlainText(QString::fromStdString(player.longDescription()));
        ui->textEdit->insertPlainText(QString::fromStdString(temp.teleport()));
        ui->textEdit->setStyleSheet("background-image:url(:/images/" + QString::fromStdString(temp.currentRoom->name()) + ".jpg); font: 75 20pt Constantia; color: white; background-attachment: fixed;");
        ui->textEdit_2->setStyleSheet("background-image:url(:/images/" + QString::fromStdString(temp.currentRoom->name()) + "map.png); background-attachment: fixed;");
        if(temp.currentRoom->getEnemy().size() > 0){
            ui->progressBar_3->setValue(temp.currentRoom->enemy()->getHealth());
        }
        else{
            ui->progressBar_3->setValue(0);
        }
        ui->progressBar_2->setValue(player.stamina);

    }

}

void MainWindow::on_pushButton_8_clicked()
{
    QMediaPlayer effect;
    if(player.getStatus() != "dead"){
        ui->textEdit->clear();
        if (temp.currentRoom->getEnemy().size() > 0 && temp.currentRoom->enemy()->getStatus() != "dead") {
            if(player.attack(temp.currentRoom->enemy())){
                if(temp.currentRoom->enemy()->getHealth() > 0){
                    ui->progressBar_3->setValue(temp.currentRoom->enemy()->getHealth());
                    ui->textEdit->insertPlainText("\nYou wounded the creature");
                    temp.currentRoom->enemy()->setDodgeVal(temp.currentRoom->enemy()->getDodgeVal() - 1);
                }
                else {
                    ui->progressBar_3->setValue(0);
                    ui->textEdit->insertPlainText("\nThe creature was slain");
                    player++;
                    if(player.victory()){
                        ui->textEdit->insertPlainText("\nCongratulations hero, the dungeon is clear!\n[GAME OVER - YOU WIN!]");
                        player.setStatus("dead");
                    }
                }
            }
            else{
                 ui->textEdit->insertPlainText("\nYour strike missed, you took some damage");
                 if(!player.checkHealth()){
                     ui->textEdit->insertPlainText("\nYou were mortally wounded...\n[GAME OVER]");
                     player.setDead();
                 }
            }
        }
        else{
             ui->textEdit->insertPlainText("\nThere aren't any enemies here");
        }
        ui->textEdit->insertPlainText( QString::fromStdString(player.longDescription()));
        ui->textEdit->insertPlainText(QString::fromStdString(temp.currentRoom->longDescription() + "\n"));
        ui->progressBar->setValue(player.getHealth());

    }

}

void MainWindow::on_pushButton_7_clicked()
{
    if(player.getStatus() != "dead"){
        ui->textEdit->clear();
        if(temp.currentRoom->numberOfItems() > 0) {
        bool check = player.take(temp.currentRoom->item());
        if(check){
            ui->textEdit->insertPlainText("\nSword equipped. You are now more proficient in combat");
        }
        else{
            ui->textEdit->insertPlainText("\nItem taken");
        }
        temp.currentRoom->removeItem();
    }
    else{
         ui->textEdit->insertPlainText("\nThere aren't any items here");
    }
    ui->textEdit->insertPlainText( QString::fromStdString(player.longDescription()));
    ui->textEdit->insertPlainText(QString::fromStdString(temp.currentRoom->longDescription()));

    }

}

void MainWindow::on_pushButton_9_clicked()
{
    this->useItem(0);
}

void MainWindow::on_pushButton_10_clicked()
{
    this->useItem(1);
}

void MainWindow::goDirection(string direction){
    if(player.getStatus() != "dead"){
        ui->textEdit->clear();
        setStamina(player, player.stamina - 10);
        if(!player.checkStamina()){
            ui->textEdit->insertPlainText("You collapse from exhaustion... \n[GAME OVER]");
            player.setDead();
        }
        ui->textEdit->insertPlainText(QString::fromStdString(player.longDescription()));
        ui->textEdit->insertPlainText(QString::fromStdString(temp.go(temp.currentRoom, direction)));
        ui->textEdit->setStyleSheet("background-image:url(:/images/" + QString::fromStdString(temp.currentRoom->name()) + ".jpg); font: 75 20pt Constantia; color: gold; background-attachment: fixed;");
        ui->textEdit_2->setStyleSheet("background-image:url(:/images/" + QString::fromStdString(temp.currentRoom->name()) + "map.png); background-attachment: fixed;");
        if(temp.currentRoom->getEnemy().size() > 0){
            ui->progressBar_3->setMaximum(temp.currentRoom->enemy()->getMaxHealth());
            ui->progressBar_3->setValue(temp.currentRoom->enemy()->getHealth());
        }
        else{
            ui->progressBar_3->setValue(0);
        }
        ui->progressBar_2->setValue(player.stamina);

    }
}

void MainWindow::useItem(int which){
    if(player.getStatus() != "dead"){
        ui->textEdit->clear();
        if(player.itemsInCharacter.size() > which){
            vector<Item>::iterator it = player.itemsInCharacter.begin();
            if(which > 0){
                it++;
            }
            if(it->getLongDescription() == "Health Potion"){
                setHealth(player, 100);
                ui->progressBar->setValue(100);
                ui->progressBar->update();
                ui->textEdit->insertPlainText("\n\nYou seem to have regained your vigor");
            }
            else{
                int stam = player.stamina + 100;
                if(stam < 500){
                   setStamina(player, stam);
                }
                else{
                    setStamina(player, 500);
                }
                ui->progressBar_2->setValue(player.stamina);
                ui->textEdit->insertPlainText("\n\nYou feel a sudden burst of energy");
            }
            player - which;
        }
        else{
            ui->textEdit->insertPlainText("\nYou don't have any items to use. Try searching around");
        }
        ui->textEdit->insertPlainText( QString::fromStdString(player.longDescription()));
        ui->textEdit->insertPlainText(QString::fromStdString(temp.currentRoom->longDescription()));

    }
}
