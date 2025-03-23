#include "screenlock.h"
#include "ui_screenlock.h"

ScreenLock::ScreenLock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenLock)
{
    ui->setupUi(this);
}

ScreenLock::~ScreenLock()
{
    delete ui;
}
