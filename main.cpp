/*
Name: Yang Hong
GitHub name: LTY0YZL
Data: 10/28/2024
Title: A6: Qt Simon Game

This is the entry point of the Simon Says game application.
It sets up the QApplication environment, creates instances
of MainWindow and gameModel, and establishes the necessary
connectionsbetween the MainWindow and the gameModel.

creative element:
After every two successful levels, all buttons will randomly
change to the same color (blue or red) during the display sequence
phase. At this time, you need to pay attention to the flashing
buttons instead of the flashing colors.
*/

#include "mainwindow.h"
#include <QApplication>
#include "gameModel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    gameModel model;

    // Connect view signals to model slots
    QObject::connect(&w, &MainWindow::startGameSignal, &model, &gameModel::startNewGame);
    QObject::connect(&w, &MainWindow::playerInputSignal, &model, &gameModel::checkPlayerInput);

    // Connect model signals to view slots
    QObject::connect(&model, &gameModel::progressUpdated, &w, &MainWindow::updateProgressBar);
    QObject::connect(&model, &gameModel::gameOver, &w, &MainWindow::onGameOver);
    QObject::connect(&model, &gameModel::flashRed, &w, &MainWindow::flashRed);
    QObject::connect(&model, &gameModel::flashBlue, &w, &MainWindow::flashBlue);
    QObject::connect(&model, &gameModel::unflashButton, &w, &MainWindow::unflashButton);
    QObject::connect(&model, &gameModel::enableInput, &w, &MainWindow::enableInput);
    QObject::connect(&model, &gameModel::disableInput, &w, &MainWindow::disableInput);
    QObject::connect(&model, &gameModel::nextLevel, &w, &MainWindow::handleSequenceComp);

    QObject::connect(&model, &gameModel::swapColors, &w, &MainWindow::swapButtonColors);
    QObject::connect(&model, &gameModel::restoreColors, &w, &MainWindow::restoreButtonColors);

    w.show();
    return a.exec();
}
