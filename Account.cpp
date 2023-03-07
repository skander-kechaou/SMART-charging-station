#include "Account.h"
#include <QSqlQuery>
#include<QDebug>
#include <QMessageBox>
#include "login.h"

Account::Account()
{
    this->username = "";
    this->pwd = "";
   // this->role= "";
}

Account::Account(QString username,QString pwd)
{
    this->username = username;
    this->pwd = pwd;
   //this->role = role;

}


bool Account::connect(QString uname,QString p){

    query.prepare("SELECT *FROM ACCOUNT WHERE username = :username AND pwd = :pwd  ");

    query.bindValue(":username", uname);
    query.bindValue(":pwd", p);
    return query.exec() && query.next();

    }
 bool Account::reset_pwd(QString uname ,QString old_pwd,QString new_pwd)
 {

     QSqlQuery query;
         query.prepare("UPDATE ACCOUNT SET pwd=:new_pwd WHERE (username=:uname AND pwd=:old_pwd)");
         query.bindValue(":user",uname);
         query.bindValue(":old_pwd",old_pwd);
         query.bindValue(":new_pwd", new_pwd);

         return query.exec();
 }


