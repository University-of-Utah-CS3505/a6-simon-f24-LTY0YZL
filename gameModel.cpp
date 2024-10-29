#include "gameModel.h"
#include <QRandomGenerator>
#include <QDebug>

gameModel::gameModel(QObject *parent) : QObject(parent), currentIndex(0)
{
}

void gameModel::startNewGame() {
    sequence.clear();
    currentIndex = 0;
    addRandomMove();
    flashSequence();
}

void gameModel::checkPlayerInput(int color) {
    qDebug() << "Checking input. Current Index:" << currentIndex << ", Total Sequence Size:" << sequence.size();
    if (currentIndex < sequence.size() && color == sequence[currentIndex]) {
        qDebug() << "Input Color:" << color << ", Expected Color at Current Index:" << sequence[currentIndex];
        currentIndex++;

        if (currentIndex == sequence.size()) {
            qDebug() << "Sequence complete. Current Index:" << currentIndex << ", Sequence Size:" << sequence.size();
            emit progressUpdated(100);
            QTimer::singleShot(1000, this, &gameModel::nextLevel);
            currentIndex = 0;
        } else {
            emit progressUpdated(static_cast<int>(100.0 * currentIndex / sequence.size()));
        }
        emit inputProcessed();
    } else {
        qDebug() << "Incorrect input or excess input. Game over.";
        emit gameOver();
        currentIndex = 0;
    }
}

void gameModel::addRandomMove() {
    int newColor = QRandomGenerator::global()->bounded(2);  // 0 or 1 randomly
    sequence.append(newColor);
    emitProgress();
}

void gameModel::emitProgress() {
    emit progressUpdated(static_cast<int>(100.0 * currentIndex / sequence.size()));
}

void gameModel::flashSequence() {
    emit disableInput();
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
    QTimer::singleShot(sequence.size() * 1500, this, [this]() { emit enableInput(); });
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
