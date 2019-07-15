#include "custombutton.h"
#include "algorithm"

CustomButton::CustomButton(char letter, QWidget* parent )
    : QPushButton(parent )
{
    this->setText(this->offText);
    this->onText = letter;
}
