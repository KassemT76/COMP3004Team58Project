#include "homescreen.h"
#include "ui_homescreen.h"

homescreen::homescreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::homescreen)
{
    ui->setupUi(this);
}

homescreen::~homescreen()
{
    delete ui;
}
