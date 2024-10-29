/*
Name: Yang Hong
Data: 10/28/2024
Title: A6: Qt Simon Game

This header file defines the gameModel class for a Simon  game.
The class manages game states, level progression, and player interactions.
 It is responsible for storing the sequenceof colors, validating player
inputs against the sequence, handling level transitions, and emitting signals
for UI updates.
*/

#include "gameModel.h"
#include <QRandomGenerator>
#include <QDebug>

//Constructs a gameModel object.
gameModel::gameModel(QObject *parent) : QObject(parent), currentIndex(0)
{
}

//Starts a new game by resetting all game variables and initializing the first move.
void gameModel::startNewGame() {
    sequence.clear();
    currentIndex = 0;
    levelCounter = 0;
    gameActive = true; // Game is active
    colorsSwapped = false;
    addRandomMove();
    flashSequence();
}

//Checks the player's input against the expected sequence at the current index.
void gameModel::checkPlayerInput(int color) {
    if (!gameActive) {
        qDebug() << "Game not active.";
        return;
    }

    qDebug() << "CurrentIndex:" << currentIndex << ", TotalSize:" << sequence.size();
    if (currentIndex < sequence.size() && color == sequence[currentIndex]) {
        qDebug() << "Input Color:" << color << ", Expected Color at Current Index:" << sequence[currentIndex];
        currentIndex++;

        if (currentIndex == sequence.size()) {
            qDebug() << "CurrentIndex:" << currentIndex << ", SequenceSize:" << sequence.size();
            emit progressUpdated(100);
            QTimer::singleShot(1000, this, [this]() {
                handleNextLevel();
            });

            currentIndex = 0;
        } else {
            emit progressUpdated(static_cast<int>(100.0 * currentIndex / sequence.size()));
        }

    } else {
        qDebug() << "Game over.";
        emit gameOver();
        currentIndex = 0;
        gameActive = false;
    }
}

//Adds a random move to the sequence.
void gameModel::addRandomMove() {
    int newColor = QRandomGenerator::global()->bounded(2);  // Generates 0 or 1 randomly
    sequence.append(newColor);
    emitProgress();
}

//ts a progress updated signal based on the current index relative to the sequence size.
void gameModel::emitProgress() {
    emit progressUpdated(static_cast<int>(100.0 * currentIndex / sequence.size()));
}

//Flashes the sequence of colors to the user.
void gameModel::flashSequence() {
    emit disableInput(); // Disable input before flashing
    printSequence();

    for (int i = 0; i < sequence.size(); ++i) {
        QTimer::singleShot(i * 1000, this, [this, i]() {
            int buttonId = sequence.at(i);
            if (buttonId == 0) {
                emit flashRed();
            } else {
                emit flashBlue();
            }
            QTimer::singleShot(500, this, [this, buttonId]() { emit unflashButton(buttonId); });
        });
    }
    QTimer::singleShot(sequence.size() * 1500, this, [this]() { emit enableInput(); currentIndex = 0; });
}

//Outputs the current sequence to the debug console.
void gameModel::printSequence() {
    QString seqOutput = "Sequence: ";
    for (int color : sequence) {
        if (color == 0) {
            seqOutput += "Red ";
        } else if (color == 1) {
            seqOutput += "Blue ";
        }
    }
    qDebug() << seqOutput;
}

//Handles the transition to the next level,  color swap based on the level counter.
void gameModel::handleNextLevel() {
    levelCounter++;

    if (levelCounter % 2 == 0) {  //change every 2 times
        colorsSwapped = !colorsSwapped;
        if (colorsSwapped) {
            emit swapColors();
        } else {
            emit restoreColors();
        }
    }

    QTimer::singleShot(500, this, [this]() {
        addRandomMove();
        flashSequence();
    });
}
