#include "screenhome.h"
#include "ui_screenhome.h"

ScreenHome::ScreenHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenHome)
{
    ui->setupUi(this);

    connect(ui->settingsButton, SIGNAL(released()), this, SLOT(goToProfile()));
    connect(ui->bolusButton, SIGNAL(released()), this, SLOT(goToBolus()));
}

ScreenHome::~ScreenHome()
{
    delete ui;
}

void ScreenHome::goToProfile(){
    emit sendToProfile();
}
void ScreenHome::goToBolus(){
    emit sendToBolus();
}
