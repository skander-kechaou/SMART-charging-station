#include "maildialog.h"
#include "ui_maildialog.h"

mailDialog::mailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mailDialog)
{
    ui->setupUi(this);
}

mailDialog::~mailDialog()
{
    delete ui;
}
