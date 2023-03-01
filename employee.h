#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>

class Employee
{
public:
    Employee();
    void setId(int ID);
     void setFname(QString fname);
     void setLname(QString lname);
     void setMail(QString mail);
     void setPhone(int Phone );
     void setRole(QString role);
     void setSalary(float salary);
     int getId();
     QString getFname();
     QString getLname();
     QString getMail();
     int  getPhone();
     QString getRole();
     float getSalary();


private :
    int ID;
   QString  fname;
   QString  lname;
   QString  mail;
   int  Phone  ;
  QString   role;
  float  salary;


};

#endif // EMPLOYEE_H
