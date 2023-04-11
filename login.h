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

private:
    Ui::Login *ui;
       Login *l;
Account *a;
QByteArray data;
Arduino A;

};
#endif // LOGIN_H
