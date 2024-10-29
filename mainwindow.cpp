/*
Name: Yang Hong
Data: 10/28/2024
Title: A6: Qt Simon Game

This file provides the implementation for the MainWindow class defined in MainWindow.h.
It includes methods for setting up the UI layout, connecting UI elements to signals and slots for
interaction, and updating the UI based on game state changes.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set initial button styles
    ui->redButton->setStyleSheet("QPushButton {background-color: red;} QPushButton:pressed {background-color: darkred;}");
    ui->blueButton->setStyleSheet("QPushButton {background-color: blue;} QPushButton:pressed {background-color: darkblue;}");

    // Disable the red and blue buttons initially
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);

    // Connect UI signals to slots
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(ui->redButton, &QPushButton::clicked, this, &MainWindow::onRedButtonClicked);
    connect(ui->blueButton, &QPushButton::clicked, this, &MainWindow::onBlueButtonClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startGame() {
    emit startGameSignal();
    ui->pushButton->setEnabled(false); // Disable the start button
    ui->loseMessage->clear();          // Clear any lose messages
}

void MainWindow::onRedButtonClicked() {
    emit playerInputSignal(0);
}

void MainWindow::onBlueButtonClicked() {
    emit playerInputSignal(1);
}

void MainWindow::onGameOver() {
    ui->loseMessage->setText("You lose! Click start button to play again");
    ui->pushButton->setEnabled(true);    // Enable the start button
    ui->redButton->setEnabled(false);    // Disable input buttons
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

void MainWindow::disableInput() {
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
}

void MainWindow::handleSequenceComp() {
    qDebug() << "To next level.";
}

void MainWindow::swapButtonColors() {
    std::swap(redButtonColor, blueButtonColor);

    ui->redButton->setStyleSheet("QPushButton { background-color: " + redButtonColor + "; }");
    ui->blueButton->setStyleSheet("QPushButton { background-color: " + blueButtonColor + "; }");
}

void MainWindow::restoreButtonColors() {
    // Reset the colors to their defaults
    redButtonColor = "red";
    blueButtonColor = "blue";

    //Apply the default styles
    ui->redButton->setStyleSheet("QPushButton { background-color: red; }");
    ui->blueButton->setStyleSheet("QPushButton { background-color: blue; }");
}
