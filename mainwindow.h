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
