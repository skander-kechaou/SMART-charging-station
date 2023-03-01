#include "employee.h"

Employee::Employee()
{

}

void Employee::setId(int ID)
{
    this->ID=ID;
}
 void Employee::setFname(QString fname)
 {
      this->fname=fname;
 }
 void Employee::setLname(QString lname)
 {
      this->lname=lname;
 }
 void Employee::setMail(QString mail)
 {
      this->mail=mail;
 }
 void Employee::setPhone(int Phone)
 {
       this->Phone=Phone;
 }
 void Employee::setRole(QString role)
 {
      this->role=role;
 }
 void Employee::setSalary(float salary)
 {
      this->salary=salary;

 }
 int Employee::getId()
 {

     return ID;
 }
 QString Employee::getFname()
 {
     return fname;
 }
 QString Employee::getLname()
 {
     return lname;
 }
 QString Employee::getMail()
 {
     return mail;
 }
 int  Employee::getPhone()
 {

     return Phone;
 }
 QString Employee::getRole()
 {
     return role;
 }
 float Employee::getSalary()
 {
     return salary ;
 }
