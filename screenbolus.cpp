#include "screenbolus.h"
#include "ui_screenbolus.h"

ScreenBolus::ScreenBolus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenBolus)
{
    ui->setupUi(this);

    connect(ui->backButton, SIGNAL(released()), this, SLOT(goToHome()));
}

ScreenBolus::~ScreenBolus()
{
    delete ui;
}

void ScreenBolus::goToHome(){
    emit sendToHome();
}
