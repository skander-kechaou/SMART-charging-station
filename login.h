#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include "employee.h"
#include "Account.h"
#include<QWidget>
#include "arduino.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE


class Login : public QMainWindow
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:


    void on_login_clicked();

    void on_label_2_linkActivated(const QString &link);

    void on_sign_up_clicked();

    void on_loginbtn_clicked();

    void on_mdp_oublie_label_linkActivated(const QString &link);

    void on_arduino_clicked();
     void readSerial();
     QString readRFID();
void readData();
void on_AdminAccess_clicked();
void process_data(QByteArray data);

private:
    Ui::Login *ui;
       Login *l;
        bool AdminAccess;
Account *a;
QByteArray data;
Arduino A;
 QSerialPort *ard;
 QString arduino_port_name;
 bool arduino_available;
 QByteArray serialData;
 QString serialBuffer;
 QString parsed_data;
 QString UID;
Account acc;
QList<QString> rfidUids;
Account aa;
QString c="";
QString dat;
     bool test=false;
     Employee emp;

};
#endif // LOGIN_H
