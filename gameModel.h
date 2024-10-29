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
    void startNewGame();
    void checkPlayerInput(int color);
    void addRandomMove();
    void flashSequence();
    void printSequence();

signals:
    void progressUpdated(int value);
    void gameOver();
    void flashRed();
    void flashBlue();
    void unflashButton(int buttonId);
    void enableInput();
    void nextLevel();
    void inputProcessed();
    void disableInput();

private:
    QVector<int> sequence;
    int currentIndex;

    void emitProgress();


};

#endif // GAMEMODEL_H
