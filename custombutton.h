#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QString>

class CustomButton : public QPushButton
{
public:
    QString offText = "X";
    QString onText = "E";
    CustomButton(char letter, QWidget* parent = 0 );
};

#endif // CUSTOMBUTTON_H
