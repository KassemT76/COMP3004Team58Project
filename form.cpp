#include "form.h"
#include "ui_form.h"
#include <QLabel>
#include <QVBoxLayout>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    setWindowTitle("Second Window");
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("This is another screen!"));
    setLayout(layout);
}

Form::~Form()
{
    delete ui;
}
