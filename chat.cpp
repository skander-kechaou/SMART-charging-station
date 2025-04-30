#include "chat.h"
#include "ui_chat.h"
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTextStream>
#include<QTextEdit>
#include <QSqlRecord>
#include "management.h"

Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{

       ui->setupUi(this);
       mSocket=new QUdpSocket(this);

}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_sendbutton_clicked()
{
  auto  datagrama= ui->msj->text().toLatin1();
mSocket->writeDatagram(datagrama,QHostAddress::Broadcast,ui->port->value());

}

void Chat::on_cancelbutton_clicked()
{
 reject();
}
