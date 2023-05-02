#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <QApplication>
#include <QSqlQuery>
#include <QSerialPort>
#include <QSerialPort>
#include "arduino.h"
#include <QSqlQueryModel>
class Account
{


    QSqlQuery query;
public:
    arduino a;
    QString pwd,username,role;
     Account();
     Account(QString username,QString pwd);
    bool connect(QString uname,QString p);
  // bool reset_pwd(QString uname ,QString old_pwd,QString new_pwd);
    bool sign_up(QString uname,QString pwd,QString role,QString idemp);
QStringList liste();
bool ajouter_image(QString username);
QByteArray fetch_image(QString uname);
bool reset_pwd(QString user,QString old_mdp,QString new_mdp);

bool checkEmp(QString ui);
QString getEmployeCarte(QString ui);
};
#endif // ACCOUNT_H
