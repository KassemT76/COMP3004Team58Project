#include "screenkeypad.h"
#include "ui_screenkeypad.h"

ScreenKeypad::ScreenKeypad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenKeypad)
{
    ui->setupUi(this);
}

ScreenKeypad::~ScreenKeypad()
{
    delete ui;
}
