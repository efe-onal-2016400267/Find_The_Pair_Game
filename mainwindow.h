#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "custombutton.h"
#include <QStack>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void buttonClicked(bool checked);
    void checkAndDestroy();
    void slotReboot();
private:
    Ui::MainWindow *ui;
    CustomButton *buttons[24];
    QVector<char> letters = {'A','A','B','B','C','C','D','D','E','E','F','F','G','G','H','H','I','I','J','J','K','K','L','L'};
    int width = 75;
    int height = width;
    int m_clicks = 0;
    QStack<CustomButton*> stack;
    QPushButton *resetButton;
    int trialNumber = 0;
    int pairNumber = 0;
    QPushButton *trials;
    QPushButton *pairs;

};

#endif // MAINWINDOW_H
