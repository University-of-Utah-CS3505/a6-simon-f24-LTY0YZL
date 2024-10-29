#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <QObject>
#include <QVector>
#include <QTimer>

class gameModel : public QObject
{
    Q_OBJECT

public:
    explicit gameModel(QObject *parent = nullptr);

public slots:
    void startNewGame();
    void checkPlayerInput(int color);
    void handleNextLevel();

signals:
    void progressUpdated(int value);
    void gameOver();
    void flashRed();
    void flashBlue();
    void unflashButton(int buttonId);
    void enableInput();
    void disableInput();
    void nextLevel();

    void swapColors();      // Signal to swap colors
    void restoreColors();   // Signal to restore original colors

private:
    QVector<int> sequence;
    int currentIndex;
    bool gameActive;

    int levelCounter;
    bool colorsSwapped;

    void addRandomMove();
    void flashSequence();
    void printSequence();
    void emitProgress();

};

#endif // GAMEMODEL_H
