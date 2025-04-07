#include "screenbolus.h"
#include "ui_screenbolus.h"

ScreenBolus::ScreenBolus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenBolus)
{
    ui->setupUi(this);

    connect(ui->backButton, SIGNAL(released()), this, SLOT(goToHome()));
    connect(ui->confirmButton, &QPushButton::released, this, &ScreenBolus::confirmBolus);
    connect(ui->viewCalculationButton, &QPushButton::released, this, &ScreenBolus::calcUnits);
    connect(ui->viewUnitsButton, &QPushButton::released, this, &ScreenBolus::calcExtended);
}

ScreenBolus::~ScreenBolus()
{
    delete ui;
}

void ScreenBolus::goToHome(){
    emit sendToHome();
}
void ScreenBolus::confirmBolus(){
    emit sendConfirmBolus();
}
void ScreenBolus::calcUnits(){
    emit sendCalcUnits();
}
void ScreenBolus::calcExtended(){
    emit sendCalcExtended();
}
