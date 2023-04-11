#include "sign_up.h"
#include "ui_sign_up.h"
#include "ui_login.h"
#include "login.h"
#include "Account.h"
#include "employee.h"
#include <QMessageBox>
#include <QFileDialog>

#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
Sign_up::Sign_up(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Sign_up)
{
    ui->setupUi(this);





ui->pwd->setEchoMode(QLineEdit::Password);
ui->confirm->setEchoMode(QLineEdit::Password);
}

Sign_up::~Sign_up()
{
    delete ui;
}

void Sign_up::on_signup_clicked()
{
    QString username = ui->name->text();
    QString pwd = ui->pwd->text();
     QString role = ui->role->text();
 QString idemp = ui->idemp->text();

Account a(username,pwd);



     bool confirm_pwd=ui->pwd->text()==ui->confirm->text();
     if( confirm_pwd)
     {       bool test=a.sign_up(username, pwd, role,idemp);
               a.ajouter_image(a.username);
                /*  QPixmap outPixmap = QPixmap();
                     outPixmap.loadFromData(a.fetch_image(username),"JPG");
                    outPixmap = outPixmap.scaledToWidth(ui->label_2->width(),Qt::SmoothTransformation);

                   ui->label_2->setPixmap(outPixmap.scaled(outPixmap.width(),outPixmap.height(),Qt::KeepAspectRatio));
                */
         Login l;
         l.show();
         QMessageBox::information(nullptr, QObject::tr("ok"),
                     QObject::tr("Welcome to our desktop application!\n"
                                 "Click ok to exit."), QMessageBox::Ok);


           ui->name->setText("");
           ui->pwd->setText("");
           ui->confirm->setText("");
           ui->role->setText("");
           ui->idemp->setText("");
 }
     else
     {
         if (!confirm_pwd)
         {
           ui->confirm->setStyleSheet("color: red");


     QMessageBox::critical(nullptr, QObject::tr("not ok"),
                  QObject::tr("the two passwords are not identical\n"
                              "Click Cancel to exit."), QMessageBox::Cancel);

          }
     }
}

