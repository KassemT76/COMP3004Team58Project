#include "secondwindow.h"
#include "ui_secondwindow.h"

SecondWindow::SecondWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(released()), this, SLOT(onSaveClicked()));
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::onSaveClicked() {
    emit profileSaved(); // 🔥 emit the signal
}
