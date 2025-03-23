#include "screenbolus.h"
#include "ui_screenbolus.h"

ScreenBolus::ScreenBolus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenBolus)
{
    ui->setupUi(this);
}

ScreenBolus::~ScreenBolus()
{
    delete ui;
}
