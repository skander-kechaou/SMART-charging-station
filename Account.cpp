#include "Account.h"
#include <QSqlQuery>
#include<QDebug>
#include <QMessageBox>
#include "login.h"
#include <QFileDialog>
#include <QSqlRecord>
Account::Account()
{
}

Account::Account(QString username,QString pwd)
{
    this->username = username;
    this->pwd = pwd;
}


bool Account::connect(QString uname,QString p){
 QSqlQuery query;
    query.prepare("SELECT *FROM ACCOUNT WHERE username = :username AND pwd = :pwd  ");

    query.bindValue(":username", uname);
    query.bindValue(":pwd", p);


    return query.exec() && query.next();

    }
bool Account::sign_up(QString uname,QString pwd,QString role,QString idemp)
{
    QSqlQuery qry;
    qry.prepare("INSERT INTO ACCOUNT (pwd, username, idemp, role)"
                "VALUES (:pwd,:username,:idemp,:role)");
    qry.bindValue(":username",uname);
    qry.bindValue(":pwd",pwd);
    qry.bindValue(":role",role);
      qry.bindValue(":idemp",idemp);

    return qry.exec();
}
QStringList Account::liste()
{
QSqlQuery c;
c.prepare("select ID from EMPLOYEE");
c.exec();
QStringList l;
while(c.next()){
l<<c.value(0).toString();
}
return l;
}
bool Account::ajouter_image(QString username)
{
    QByteArray byte;
    QString filename=QFileDialog::getOpenFileName(0,"open image","D:\\",0);
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly))
    {
        byte=file.readAll();
        file.close();
    }

    QSqlQuery qry;
    qry.prepare("UPDATE ACCOUNT SET image=:image where username=:username");
    qry.bindValue(":image",byte,QSql::In | QSql::Binary);
    qry.bindValue(":username",username);

    return qry.exec();
}
QByteArray Account::fetch_image(QString uname)
{
    QSqlQuery qry;
    qry.prepare("Select * from ACCOUNT where username =:username");
    qry.bindValue(":username",uname);
    qry.exec();
    QSqlQueryModel * model = new QSqlQueryModel;
    model->setQuery(qry);
    QSqlRecord rec = model->record(0);
    QByteArray img=rec.value("image").toByteArray();
    return img;

}
/*
bool Account::reset_pwd(QString user,QString old_mdp,QString new_mdp)
{
    QSqlQuery qry;
    qry.prepare("UPDATE ACCOUNT SET password=:new_password WHERE (username=:user AND pwd=:old_password)");
    qry.bindValue(":user",user);
    qry.bindValue(":old_password",old_mdp);
    qry.bindValue(":new_password",new_mdp);

    return qry.exec();
}
bool Account::update_mpd_reset(QString uname,QString code)
{
    QSqlQuery qry;
    qry.prepare("UPDATE ACCOUNT SET pwd_reset=:pwd_reset WHERE (username=:username)");
    qry.bindValue(":username",uname);
    qry.bindValue(":pwd_reset",code);

    return qry.exec();
}*/
