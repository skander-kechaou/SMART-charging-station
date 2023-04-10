#include "qrdialog.h"
#include "ui_qrdialog.h"

qrDialog::qrDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qrDialog)
{
    ui->setupUi(this);
}

qrDialog::~qrDialog()
{
    delete ui;
}
