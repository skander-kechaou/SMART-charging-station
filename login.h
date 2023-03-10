#ifndef LOGIN_H
#define LOGIN_H
#include <QMainWindow>
#include "employee.h"
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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_login_clicked();

    void on_label_2_linkActivated(const QString &link);

private:
    Ui::Login *ui;
       Login *l;

};
#endif // LOGIN_H
