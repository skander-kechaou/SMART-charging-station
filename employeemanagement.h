#ifndef EMPLOYEEMANAGEMENT_H
#define EMPLOYEEMANAGEMENT_H
#include "Account.h"
#include <QDialog>
#include "employee.h"
#include <QWidget>
#include <QTcpSocket>
#include <QTextStream>
namespace Ui {
class EmployeeManagement;
}

class EmployeeManagement : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeManagement(QWidget *parent = nullptr);
    ~EmployeeManagement();
    QString hostname() const;
      quint16 port() const;
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



    void on_stat_clicked();

    void on_excel_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_logout_clicked();

private:
    Ui::EmployeeManagement *ui;
    Employee e;
Account a;
   /* QString mHostname="localhost";
       quint16 mPort=3333;

       QTcpSocket *mSocket;
*/
};
/*inline QString EmployeeManagement::hostname() const
{
   return mHostname;
}
inline quint16 EmployeeManagement::port() const
{
   return mPort;
}*/
#endif // EMPLOYEEMANAGEMENT_H
