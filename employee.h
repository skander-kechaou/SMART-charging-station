#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
class Employee
{
public:
    //constructors
    Employee();
   Employee( QString ID,QString  mail,QString fname ,int Phone, QString lname, float salary, QString idstat, QString role);

    //setters
    void setId(QString ID);
     void setFname(QString fname);
     void setLname(QString lname);
     void setMail(QString mail);
     void setPhone(int Phone );
     void setRole(QString role);
     void setSalary(float salary);
      void setidstat(QString idstat);

     //getters
      QString  getId();
     QString getFname();
     QString getLname();
     QString getMail();
     int  getPhone();
     QString getRole();
     float getSalary();
   QString  getidstat();

     //CRUD
     bool addEmp();
     QSqlQueryModel *view();
     bool deleteEmp(QString ID);
     bool modify();
     QSqlQueryModel * sort_name();
     QSqlQueryModel * sort_ID();
     QSqlQueryModel * sort_Role();
     QSqlQueryModel* searchname(QString na);
     QSqlQueryModel* searchID(QString id);
     QSqlQueryModel* searchRole(QString r);
      void  statistics(QVector<double>* ticks,QVector<QString> *labels);

private :
   QString   ID;
   QString  fname;
   QString  lname;
   QString  mail;
   int  Phone  ;
   QString   role;
   float  salary;
   QString idstat;


};

#endif // EMPLOYEE_H
