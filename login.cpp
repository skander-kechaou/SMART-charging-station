#include "login.h"
#include "ui_login.h"
#include "ui_reset.h"
#include "employee.h"
#include "employeemanagement.h"
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

    //arduino
                int ret=A.connect_arduino();
                switch(ret){
                  case(0):qDebug()<< "arduino is availble and connected to :"<< A.getarduino_port_name();

                    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(readData()));

                      break;
                  case(1):qDebug()<< "arduino is availble but not connected to :"<< A.getarduino_port_name();
                      break;
                  case(-1):qDebug()<< "arduino is not availble";
                  }




QMediaPlayer *music =new QMediaPlayer();
music->setMedia(QUrl("C:/Users/nadal/OneDrive/Documents/Smart_charging_station/inspiring-emotional-uplifting-piano-112623.mp3"));
music->play();

ui->lineEditoldpwd->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}


void Login::on_login_clicked()
{

       QString username = ui->lineEditoldname->text();
       QString pwd = ui->lineEditoldpwd->text();

  if((username !="")&&(pwd!="")) {
         Account a(username,pwd);
          bool test=a.connect(username,pwd);

          if(test)
                {

              QPixmap outPixmap = QPixmap();
              outPixmap.loadFromData(a.fetch_image(username),"JPG");
              /*outPixmap = outPixmap.scaledToWidth(ui->image_pos->width(),Qt::SmoothTransformation);
             ui->image_pos->setPixmap(outPixmap.scaled(outPixmap.width(),outPixmap.height(),Qt::KeepAspectRatio));
*/
              ui->lineEditoldname->setText(username);
                 Employee emp;
                 EmployeeManagement d;
                 d.exec();

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
         EmployeeManagement d;
         d.exec();
    }
    else
    {
           A.write_to_arduino("access denied!");
    }

}

}
