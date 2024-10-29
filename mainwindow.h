/*
Name: Yang Hong
Data: 10/28/2024
Title: A6: Qt Simon Game

This header file of the MainWindow class, which serves as
the primary user interface for the Simon game. It includes
methods for initializing the UI components, handling user
interactions, and responding to signals from the gameModel.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void startGameSignal();
    void playerInputSignal(int color);

public slots:
    void startGame();
    void onRedButtonClicked();
    void onBlueButtonClicked();
    void onGameOver();
    void updateProgressBar(int value);
    void flashRed();
    void flashBlue();
    void unflashButton(int buttonId);
    void enableInput();
    void disableInput();
    void handleSequenceComp();

    void swapButtonColors();
    void restoreButtonColors();

private:
    Ui::MainWindow *ui;

    QString redButtonColor = "red";
    QString blueButtonColor = "blue";
};

#endif // MAINWINDOW_H
