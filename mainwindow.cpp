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

// Constructor for MainWindow
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

//Destructor for MainWindow.
MainWindow::~MainWindow()
{
    delete ui;
}

//Starts the game  and updating the UI accordingly.
void MainWindow::startGame() {
    emit startGameSignal();
    ui->pushButton->setEnabled(false); // Disable the start button
    ui->loseMessage->clear();          // Clear any lose messages
}

// Slot that handles red button clicks. Emits a signal indicating a input of color 0 (red).
void MainWindow::onRedButtonClicked() {
    emit playerInputSignal(0);
}

// Slot that handles red button clicks. Emits a signal indicating a input of color 1 (blue).
void MainWindow::onBlueButtonClicked() {
    emit playerInputSignal(1);
}

//Handles the game over condition by updating the UI to reflect the game's end
void MainWindow::onGameOver() {
    ui->loseMessage->setText("You lose! Click start button to play again");
    ui->pushButton->setEnabled(true);    // Enable the start button
    ui->redButton->setEnabled(false);    // Disable input buttons
    ui->blueButton->setEnabled(false);
}

//Updates the game's progress bar with the given value.
void MainWindow::updateProgressBar(int value) {
    ui->progressBar->setValue(value);
}

//Temporarily change the color of the red button.
void MainWindow::flashRed() {
    ui->redButton->setStyleSheet("QPushButton {background-color: darkred;}");
}

//Temporarily change the color of the blue button.
void MainWindow::flashBlue() {
    ui->blueButton->setStyleSheet("QPushButton {background-color: darkblue;}");
}

//Restores the button color after a flash.
void MainWindow::unflashButton(int buttonId) {
    if (buttonId == 0) { // Red button
        ui->redButton->setStyleSheet("QPushButton {background-color: red;}");
    } else { // Blue button
        ui->blueButton->setStyleSheet("QPushButton {background-color: blue;}");
    }
}

//Enables the input buttons allowing the player to interact with the game
void MainWindow::enableInput() {
    ui->redButton->setEnabled(true);
    ui->blueButton->setEnabled(true);
}

//Disenables the input buttons allowing the player to interact with the game
void MainWindow::disableInput() {
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
}

void MainWindow::handleSequenceComp() {
    qDebug() << "To next level.";
}

//Swaps the colors of the buttons to add variability to the gameplay
void MainWindow::swapButtonColors() {
    std::swap(redButtonColor, blueButtonColor);

    ui->redButton->setStyleSheet("QPushButton { background-color: " + redButtonColor + "; }");
    ui->blueButton->setStyleSheet("QPushButton { background-color: " + blueButtonColor + "; }");
}

//Restores the button colors to their default settings.
void MainWindow::restoreButtonColors() {
    // Reset the colors to their defaults
    redButtonColor = "red";
    blueButtonColor = "blue";

    //Apply the default styles
    ui->redButton->setStyleSheet("QPushButton { background-color: red; }");
    ui->blueButton->setStyleSheet("QPushButton { background-color: blue; }");
}
