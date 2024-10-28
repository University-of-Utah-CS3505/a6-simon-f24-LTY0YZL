#include "gameModel.h"
#include <QRandomGenerator>

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
    if (color == sequence[currentIndex]) {
        currentIndex++;
        if (currentIndex == sequence.size()) {
            emit progressUpdated(100);
            QTimer::singleShot(1000, this, &gameModel::nextLevel);
        } else {
            emit progressUpdated(static_cast<int>(100.0 * currentIndex / sequence.size()));
        }
    } else {
        emit gameOver();
        currentIndex = 0;
    }
}

void gameModel::addRandomMove() {
    sequence.append(QRandomGenerator::global()->bounded(2)); // 0 for Red, 1 for Blue
    emitProgress();
}

void gameModel::emitProgress() {
    emit progressUpdated(static_cast<int>(100.0 * currentIndex / sequence.size()));
}

void gameModel::flashSequence() {
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
    QTimer::singleShot(sequence.size() * 1000, this, &gameModel::enableInput);
}
