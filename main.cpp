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
