#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameModel.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startGame();
    void onRedButtonClicked();
    void onBlueButtonClicked();
    void onGameOver();
    void updateProgressBar(int value);
    void flashRed();
    void flashBlue();
    void unflashButton(int buttonId);
    void enableInput();
    void handleSequenceComp();

private:
    Ui::MainWindow *ui;
    gameModel *gameModel;
};
#endif // MAINWINDOW_H
