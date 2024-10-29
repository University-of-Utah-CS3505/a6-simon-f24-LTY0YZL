#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameModel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gameModel = new class gameModel(this);

    // Set initial button styles
    ui->redButton->setStyleSheet("QPushButton {background-color: red;} QPushButton:pressed {background-color: darkred;}");
    ui->blueButton->setStyleSheet("QPushButton {background-color: blue;} QPushButton:pressed {background-color: darkblue;}");

    // Disable the red and blue buttons initially
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);

    //Connect signal and slot
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(ui->redButton, &QPushButton::clicked, this, &MainWindow::onRedButtonClicked);
    connect(ui->blueButton, &QPushButton::clicked, this, &MainWindow::onBlueButtonClicked);
    connect(gameModel, &gameModel::gameOver, this, &MainWindow::onGameOver);
    connect(gameModel, &gameModel::progressUpdated, this, &MainWindow::updateProgressBar);
    connect(gameModel, &gameModel::flashRed, this, &MainWindow::flashRed);
    connect(gameModel, &gameModel::flashBlue, this, &MainWindow::flashBlue);
    connect(gameModel, &gameModel::unflashButton, this, &MainWindow::unflashButton);
    connect(gameModel, &gameModel::enableInput, this, &MainWindow::enableInput);
    connect(gameModel, &gameModel::nextLevel, this, &MainWindow::handleSequenceComp);
    connect(gameModel, &gameModel::inputProcessed, this, &MainWindow::enableInput);
    connect(gameModel, &gameModel::disableInput, this, &MainWindow::disableInput);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame() {
    gameModel->startNewGame();
    ui->pushButton->setEnabled(false);
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    ui->loseMessage->clear();
}

void MainWindow::onRedButtonClicked() {
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    gameModel->checkPlayerInput(0);
}

void MainWindow::onBlueButtonClicked() {
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    gameModel->checkPlayerInput(1);
}

void MainWindow::onGameOver() {
    ui->loseMessage->setText("You lose. Click start to play again.");
    ui->pushButton->setEnabled(true);
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
}

void MainWindow::updateProgressBar(int value) {
    ui->progressBar->setValue(value);
}

void MainWindow::flashRed() {
    ui->redButton->setStyleSheet("QPushButton {background-color: darkred;}");
}

void MainWindow::flashBlue() {
    ui->blueButton->setStyleSheet("QPushButton {background-color: darkblue;}");
}

void MainWindow::unflashButton(int buttonId) {
    if (buttonId == 0) { // Red button
        ui->redButton->setStyleSheet("QPushButton {background-color: red;}");
    } else { // Blue button
        ui->blueButton->setStyleSheet("QPushButton {background-color: blue;}");
    }
}

void MainWindow::enableInput() {
    ui->redButton->setEnabled(true);
    ui->blueButton->setEnabled(true);
}

void MainWindow::handleSequenceComp() {
    gameModel->addRandomMove();
    gameModel->flashSequence();
}

void MainWindow::disableInput() {
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
}
