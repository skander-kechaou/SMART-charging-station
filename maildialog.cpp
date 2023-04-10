#include "maildialog.h"
#include "ui_maildialog.h"
#include "smtp.h"
#include <QSslSocket>
#include <QtNetwork>
#include "src/src/SmtpMime"
#include "src/src/smtpclient.h"
#include "src/src/emailaddress.h"
#include "src/src/mimemessage.h"
#include "src/src/mimetext.h"

mailDialog::mailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::mailDialog)
{
    ui->setupUi(this);
}

void mailDialog::setClient(client c)
{
    ui->recipient->setText(c.getEmail());
}

mailDialog::~mailDialog()
{
    delete ui;
}

void mailDialog::on_sendButton_clicked()
{
    smtp *s=new smtp("skander.kechaou.e@gmail.com","sfiprjelyxfpafed","smtp.gmail.com",465);
    s->sendMail("skander.kechaou.e@gmail.com",ui->recipient->text(),ui->subject->text(),ui->message->toPlainText());
}
