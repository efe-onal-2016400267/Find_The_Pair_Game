#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "custombutton.h"
#include <iostream>
#include <string>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(width*8,width*7);

    resetButton = new QPushButton("R  E  S  E  T", this);
    resetButton->setGeometry(width*5, width*5, width*2, width);
    trials = new QPushButton("Trials: 0",this);
    trials->setGeometry(width,width*5,width,width);
    pairs = new QPushButton("Pairs: 0", this);
    pairs->setGeometry(width*2,width*5,width,width);
    trials->setEnabled(false);
    pairs->setEnabled(false);
    connect(resetButton, SIGNAL(clicked()), this, SLOT(slotReboot()));

    srand(time(0));
    std::random_shuffle(std::begin(letters),std::end(letters));
    for (int i = 0; i < 24; ++i) {
        int horizontal = ((i % 6) + 1) * width;
        int vertical = ((i / 6) + 1) * width;
        buttons[i] = new CustomButton(letters[i], this);
        buttons[i]->setGeometry(horizontal, vertical, width, height);
        buttons[i]->setCheckable(true);
        connect(buttons[i], SIGNAL(clicked(bool)), this, SLOT(buttonClicked(bool)));
    }
}


void MainWindow::buttonClicked(bool checked)
{
 CustomButton *button = (CustomButton *)sender();

 if (checked)
 {
    stack.push(button);
    button->setText(button->onText);
    button->setEnabled(false);

    m_clicks++;
 }
 else
 {
    button->setText(button->offText);
    m_clicks--;
 }

 if(m_clicks == 2)
 {
     trialNumber++;
     QString new_trials = "Trials: "  + QString::number(trialNumber);
     trials->setText(new_trials);
     checkAndDestroy();
 }
}

void MainWindow::checkAndDestroy()
{
        CustomButton *secondButton = stack.pop();
        CustomButton *firstButton = stack.pop();

        if(QString::compare(firstButton->onText, secondButton->onText) == 0){
            pairNumber++;
            QString new_pairs = "Pairs: "  + QString::number(pairNumber);
            pairs->setText(new_pairs);
            m_clicks = 0;
        }
        else
        {
            m_clicks = 0;
            QEventLoop loop;
            QTimer::singleShot(1000, &loop, SLOT(quit()));
              loop.exec();

            firstButton->setEnabled(true);
            firstButton->setChecked(false);
            firstButton->setText(firstButton->offText);
            secondButton->setEnabled(true);
            secondButton->setChecked(false);
            secondButton->setText(secondButton->offText);
        }
}

void MainWindow::slotReboot()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

MainWindow::~MainWindow()
{
    delete ui;
}
