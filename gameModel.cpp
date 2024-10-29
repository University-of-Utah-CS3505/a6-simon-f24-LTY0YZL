#include "gameModel.h"
#include <QRandomGenerator>
#include <QDebug>

gameModel::gameModel(QObject *parent) : QObject(parent), currentIndex(0)
{
}

void gameModel::startNewGame() {
    sequence.clear();
    currentIndex = 0;
    levelCounter = 0;
    gameActive = true; // Game is active
    colorsSwapped = false;
    addRandomMove();
    flashSequence();
}

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

void gameModel::addRandomMove() {
    int newColor = QRandomGenerator::global()->bounded(2);  // Generates 0 or 1 randomly
    sequence.append(newColor);
    emitProgress();
}

void gameModel::emitProgress() {
    emit progressUpdated(static_cast<int>(100.0 * currentIndex / sequence.size()));
}

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
