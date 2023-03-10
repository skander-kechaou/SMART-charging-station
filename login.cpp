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
Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
QMediaPlayer *music =new QMediaPlayer();
music->setMedia(QUrl("C:/Users/nadal/OneDrive/Documents/Smart_charging_station/inspiring-emotional-uplifting-piano-112623.mp3"));
music->play();
}

Login::~Login()
{
    delete ui;
}


void Login::on_login_clicked()
{

       QString username = ui->lineEditoldname->text();
       QString pwd = ui->lineEditoldpwd->text();

  if((username !=  "")&&(pwd!="")) {
         Account a(username,pwd);
          bool test=a.connect(username,pwd);

          if(test)
                {
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
/*

void Login::on_pushButton_2_clicked()
{
    if (ui->lineEditoldpwd->text()==ui->confirmpwd->text())
           {
               if (ui->lineEditoldpwd->text()!="" && ui->confirmpwd->text()!="")
               {
                   bool test=modifier_mdp(current_user,ui->ancienMotDePasseLineEdit->text(),ui->nouveauMotDePasseLineEdit->text());

                   if (!test)
                       QMessageBox::warning(this,tr("Changement du MDP"),tr("Erreur lors du changement du MDP"));
                   else
                   {
                       ui->ancienMotDePasseLineEdit->clear();
                       ui->nouveauMotDePasseLineEdit->clear();
                       ui->confirmerNouveauMotDePasseLineEdit->clear();
                   }
               }
               else
                   QMessageBox::warning(this,tr("Changement du MDP"),tr("Veuillez remplir tous les champs"));
           }
           else
               QMessageBox::warning(this,tr("Changement du MDP"),tr("Les deux mots de passe ne sont pas identiques"));
}
*/
