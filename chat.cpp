#include "chat.h"
#include "ui_chat.h"
#include <QTcpSocket>
#include <QUdpSocket>
#include <QTextStream>
#include<QTextEdit>
#include <QSqlRecord>
#include "employeemanagement.h"
Chat::Chat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Chat)
{

       ui->setupUi(this);
       mSocket=new QUdpSocket(this);
      // mSocket->bind()
      /* mSocket= new QTcpSocket(this);
          connect(mSocket,&QTcpSocket::readyRead,[&](){
              QTextStream T(mSocket);
             auto text =T.readAll();
             ui->textEdit->append(text);
          });
          EmployeeManagement D(this);

        mSocket->connectToHost(D.hostname(), D.port());*/
}

Chat::~Chat()
{
    delete ui;
}

void Chat::on_sendbutton_clicked()
{
  auto  datagrama=ui->msj->text().toLatin1();
mSocket->writeDatagram(datagrama,QHostAddress::Broadcast,ui->port->value());
   /* mHostname = ui->hostname_2->text();
       mPort = ui->port->value();
       accept();*/
   /* EmployeeManagement m;
    Employee em;
    QString test;
    QSqlQueryModel* model=em.searchID(idemp);
    QTextStream T(mSocket);
    T<< model->record(0).value(2).toString() <<":"<<ui->lineEdit_3->text(); //utilisateur
    mSocket->flush(); //envoyer le msg au serveur
    ui->lineEdit_3->clear();
    QTextStream T(mSocket);
    T<< "nada"<<":"<<ui->lineEdit_2->text(); //utilisateur
    mSocket->flush(); //envoyer le msg au serveur
    ui->lineEdit_2->clear();*/
}

void Chat::on_cancelbutton_clicked()
{
 reject();
}
