#include "login.h"
#include "ui_login.h"
#include "employee.h"
#include "employeemanagement.h"
Login::Login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}


void Login::on_pushButton_clicked()
{
   Employee emp;
   emp.setFname(ui->lineEdit->text());
   emp.setFname(ui->lineEdit_2->text());
 EmployeeManagement d;

      d.exec();


}
