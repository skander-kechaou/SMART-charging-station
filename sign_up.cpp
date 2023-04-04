#include "sign_up.h"
#include "ui_sign_up.h"

Sign_up::Sign_up(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sign_up)
{
    ui->setupUi(this);
}

Sign_up::~Sign_up()
{
    delete ui;
}
