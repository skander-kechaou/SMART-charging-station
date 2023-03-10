#include "employee.h"
#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
#include <QListView>
#include <QtDebug>
#include <QMessageBox>
Employee::Employee()
{
    ID=" ";
    fname=" ";
   lname=" ";
    mail=" ";
   role=" ";
   Phone=0;
   salary=0.0;


}
Employee::Employee( QString ID,QString  mail,QString fname ,int Phone, QString lname, float salary, QString idstat, QString role)



{
    this->ID=ID;
    this->fname=fname;
    this->lname=lname;
    this->mail=mail;
    this->role=role;
    this->Phone=Phone;
    this->salary=salary;
     this->idstat=idstat;
}
void Employee::setId(QString ID)
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
 void Employee::setidstat(QString idstat)
 {
     this->idstat=idstat;
 }
QString Employee::getId()
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
 QString Employee::getidstat()
  {

      return idstat;
  }
bool Employee::addEmp()
{
     QSqlQuery query;
     QString salary_string =QString::number(salary);
     QString Phone_string =QString::number(Phone);


     query.prepare("INSERT INTO EMPLOYEE( ID, MAIL, FNAME, PHONE, LNAME, SALARY, IDSTAT, ROLE) "
                   "VALUES( : ID,: MAIL, :FNAME,: PHONE,: LNAME, :SALARY, :IDSTAT,: ROLE)");

    // Creating variables
      query.bindValue(0,ID);
      query.bindValue(1,mail);
      query.bindValue(2,fname);
      query.bindValue(3,Phone_string);
      query.bindValue(4,lname);
      query.bindValue(5,salary_string);
      query.bindValue(6,idstat);
      query.bindValue(7,role);




    return query.exec(); //exec() send request to be executed
}
QSqlQueryModel * Employee::view()
{

    QSqlQueryModel *model=new QSqlQueryModel();


      model->setQuery(QString("Select * from employee"));
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("   ID  "));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr(" First Name  "));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("  Last Name  "));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Phone Num  "));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr(" Mail   "));
      model->setHeaderData(7, Qt::Horizontal, QObject::tr("Role  "));
      model->setHeaderData(5, Qt::Horizontal, QObject::tr(" Salary  "));
      model->setHeaderData(6, Qt::Horizontal, QObject::tr("  IDstat "));




      return model;
}
bool Employee::deleteEmp(QString ID)
{
    QSqlQuery query;


    query.prepare("Delete FROM EMPLOYEE WHERE ID= :ID");

    query.bindValue(":ID",ID);

    return  query.exec();

}

bool Employee::modify()
{
    QSqlQuery query;

      QString stringsalary= QString ::number(salary);
      QString stringphone= QString ::number(Phone);

   query.prepare("UPDATE EMPLOYEE SET ID=:ID, mail=:mail,fname=:fname,Phone=:Phone,lname=:lname, salary=:salary,idstat=:idstat,role=:role WHERE ID=:ID" );

   query.bindValue(0,ID);
   query.bindValue(1,mail);
   query.bindValue(2,fname);
   query.bindValue(3,stringphone);
   query.bindValue(4,lname);
   query.bindValue(5,stringsalary);
   query.bindValue(6,idstat);
   query.bindValue(7,role);

  return  query.exec();
}




QSqlQueryModel *  Employee::sort_name()
{

    QSqlQueryModel * model= new QSqlQueryModel();

             model->setQuery("SELECT * FROM EMPLOYEE ORDER BY fname ");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("   ID  "));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr(" First Name  "));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("  Last Name  "));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Phone Num  "));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr(" Mail   "));
             model->setHeaderData(7, Qt::Horizontal, QObject::tr("Role  "));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr(" Salary  "));
             model->setHeaderData(6, Qt::Horizontal, QObject::tr("  IDstat "));
       return model;



}
QSqlQueryModel *  Employee::sort_ID()
{
 QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("SELECT * FROM EMPLOYEE ORDER BY ID ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("   ID  "));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr(" First Name  "));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("  Last Name  "));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Phone Num  "));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr(" Mail   "));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("Role  "));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr(" Salary  "));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("  IDstat "));
    return model;
}
QSqlQueryModel * Employee::sort_Role()
{
  QSqlQueryModel * model= new QSqlQueryModel();

           model->setQuery("SELECT * FROM EMPLOYEE ORDER BY ROLE");
           model->setHeaderData(0, Qt::Horizontal, QObject::tr("   ID  "));
           model->setHeaderData(2, Qt::Horizontal, QObject::tr(" First Name  "));
           model->setHeaderData(4, Qt::Horizontal, QObject::tr("  Last Name  "));
           model->setHeaderData(3, Qt::Horizontal, QObject::tr("Phone Num  "));
           model->setHeaderData(1, Qt::Horizontal, QObject::tr(" Mail   "));
           model->setHeaderData(7, Qt::Horizontal, QObject::tr("Role  "));
           model->setHeaderData(5, Qt::Horizontal, QObject::tr(" Salary  "));
           model->setHeaderData(6, Qt::Horizontal, QObject::tr("  IDstat "));
     return model;
}
QSqlQueryModel* Employee::searchname(QString na)
  {

  QSqlQueryModel * model= new QSqlQueryModel();

          model->setQuery("select * from EMPLOYEE where FNAME ='"+na+"' ");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("   ID  "));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr(" First Name  "));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("  Last Name  "));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Phone Num  "));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr(" Mail   "));
          model->setHeaderData(7, Qt::Horizontal, QObject::tr("Role  "));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr(" Salary  "));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("  IDstat "));
          return model;
  }
 QSqlQueryModel* Employee::searchID(QString id)
 {
     QSqlQueryModel * model= new QSqlQueryModel();

             model->setQuery("select * from EMPLOYEE where ID ='"+id+"' ");
             model->setHeaderData(0, Qt::Horizontal, QObject::tr("   ID  "));
             model->setHeaderData(2, Qt::Horizontal, QObject::tr(" First Name  "));
             model->setHeaderData(4, Qt::Horizontal, QObject::tr("  Last Name  "));
             model->setHeaderData(3, Qt::Horizontal, QObject::tr("Phone Num  "));
             model->setHeaderData(1, Qt::Horizontal, QObject::tr(" Mail   "));
             model->setHeaderData(7, Qt::Horizontal, QObject::tr("Role  "));
             model->setHeaderData(5, Qt::Horizontal, QObject::tr(" Salary  "));
             model->setHeaderData(6, Qt::Horizontal, QObject::tr("  IDstat "));
             return model;
 }
QSqlQueryModel*  Employee::searchRole(QString r)
{


    QSqlQueryModel * model= new QSqlQueryModel();

            model->setQuery("select * from EMPLOYEE where ROLE ='"+r+"' ");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("   ID  "));
            model->setHeaderData(2, Qt::Horizontal, QObject::tr(" First Name  "));
            model->setHeaderData(4, Qt::Horizontal, QObject::tr("  Last Name  "));
            model->setHeaderData(3, Qt::Horizontal, QObject::tr("Phone Num  "));
            model->setHeaderData(1, Qt::Horizontal, QObject::tr(" Mail   "));
            model->setHeaderData(7, Qt::Horizontal, QObject::tr("Role  "));
            model->setHeaderData(5, Qt::Horizontal, QObject::tr(" Salary  "));
            model->setHeaderData(6, Qt::Horizontal, QObject::tr("  IDstat "));
            return model;

}

void Employee::statistics(QVector<double>* ticks,QVector<QString> *labels)
{
    QSqlQuery q;
    int i=0;
    q.exec("select salary from EMPLOYEE");
    while (q.next())
    {
        QString identifiant = q.value(0).toString();
        i++;
        *ticks<<i;
        *labels <<identifiant;
    }
}
