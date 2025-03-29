#include "screenaddprofile.h"
#include "ui_screenaddprofile.h"

ScreenAddProfile::ScreenAddProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScreenAddProfile)
{
    ui->setupUi(this);

    connect(ui->backButton, SIGNAL(released()), this, SLOT(goToProfile()));
}

ScreenAddProfile::~ScreenAddProfile()
{
    delete ui;
}

void ScreenAddProfile::goToProfile(){
    emit sendToProfile();
}

