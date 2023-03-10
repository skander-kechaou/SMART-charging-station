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


    //void on_pushButton_clicked();

    void on_add_clicked();
    void on_buttonDelete_clicked();
    void on_pushButton12_clicked();
    void on_sort_clicked();
    void on_search_clicked();
    void on_PDF_clicked();
    void on_tableView_clicked(const QModelIndex &index);

    void on_edit_clicked();

private:
    Ui::EmployeeManagement *ui;
    Employee e;
};

#endif // EMPLOYEEMANAGEMENT_H
