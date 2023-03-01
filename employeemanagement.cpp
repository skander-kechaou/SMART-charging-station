#include "employeemanagement.h"
#include "ui_employeemanagement.h"
#include "employee.h"

EmployeeManagement::EmployeeManagement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmployeeManagement)
{
    ui->setupUi(this);
}

EmployeeManagement::~EmployeeManagement()
{
    delete ui;
}


