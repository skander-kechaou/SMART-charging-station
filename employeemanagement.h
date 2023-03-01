#ifndef EMPLOYEEMANAGEMENT_H
#define EMPLOYEEMANAGEMENT_H

#include <QDialog>
#include "employee.h"

namespace Ui {
class EmployeeManagement;
}

class EmployeeManagement : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeManagement(QWidget *parent = nullptr);
    ~EmployeeManagement();

private slots:


    void on_pushButton_clicked();

private:
    Ui::EmployeeManagement *ui;
};

#endif // EMPLOYEEMANAGEMENT_H
