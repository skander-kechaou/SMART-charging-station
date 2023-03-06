#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QApplication>
#include <QSqlQuery>
#include "login.h"

class Account
{


    QSqlQuery query;
public:
    QString pwd,username,role;
     Account();
     Account(QString username,QString pwd);
    bool connect(QString uname,QString p);
   bool reset_pwd(QString uname ,QString old_pwd,QString new_pwd);


};
#endif // ACCOUNT_H
