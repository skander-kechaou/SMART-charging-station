#include "login.h"
#include "ui_login.h"
#include "employee.h"
#include "management.h"
#include "Account.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <QtSql/QSqlQueryModel>
#include <QVideoWidget>
#include <QMessageBox>
#include <QMediaPlayer>
#include "sign_up.h"
#include "ui_sign_up.h"
#include "arduino.h"

Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
    QPixmap bg("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/car.png");
    QIcon sync("C:/Users/Skander/Desktop/Final Integration/Integration/IMG/synchronize.png");
    ui->label_2->setPixmap(bg);
    ui->loginbtn->setIcon(sync);

    //arduino
               /* int ret=A.connect_arduino();
                switch(ret){
                  case(0):qDebug()<< "arduino is availble and connected to :"<< A.getarduino_port_name();

                    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(readData()));

                      break;
                  case(1):qDebug()<< "arduino is availble but not connected to :"<< A.getarduino_port_name();
                      break;
                  case(-1):qDebug()<< "arduino is not availble";
                  }*/




QMediaPlayer *music =new QMediaPlayer();
music->setMedia(QUrl("C:/Users/Skander/Desktop/Final Integration/Integration/startup-sfx.mp3"));
music->setVolume(80);
music->play();

ui->lineEditoldpwd->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}


void Login::on_login_clicked()
{

       button_sound();
       QString username = ui->lineEditoldname->text();
       QString pwd = ui->lineEditoldpwd->text();

  if((username !="")&&(pwd!="")) {
         Account a(username,pwd);
          bool test=a.connect(username,pwd);

          if(test)
                {

              QPixmap outPixmap = QPixmap();
              outPixmap.loadFromData(a.fetch_image(username),"JPG");

              ui->lineEditoldname->setText(username);
                 Employee emp;
                 Management m;
                 m.exec();

                 ui->lineEditoldname->setText(" ");
                 ui->lineEditoldpwd->setText(" ");

               }
            else
                 QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("username and  password is not correct\n"
                                    "OK."), QMessageBox::Cancel);
}

}


void Login::on_loginbtn_clicked()
{
    Sign_up d;
    d.exec();
    button_sound();
}

void Login::readData()
{
 QString uid;
  QString  data;
  data=A.read_from_arduino();
   qDebug() << "Received account from Arduino: " << data;

      if (data!="#")
       {
           uid+=data;

       }
       else {

           bool exist= acc.checkEmp(uid);
           qDebug() << "Employee exists in database: " << exist;
           qDebug()<<exist;
    if(exist)
    {
         A.write_to_arduino("you may access !");
         Management m;
         m.exec();
    }
    else
    {
           A.write_to_arduino("access denied!");
    }

}

}
