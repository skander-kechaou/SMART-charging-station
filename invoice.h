#ifndef INVOICE_H
#define INVOICE_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDate>

class invoice
{
public:
    invoice();                                         //constructor initialization
    invoice(QString, QString, QString, QString, int, QDate);  //constructor

    //setters
     void setreference(QString);
     void setNIC(QString);
     void setidstat(QString);
     void setlicensepl(QString);
     void setcost(int);
     void setdate_inv(QDate);

     //getters
     QString getreference();
     QString getNIC();
     QString getidstat();
     QString getlicensepl();
     int getcost();
     QDate getdate_inv();

     //CRUD FEATURES
     bool Create ();
     QSqlQueryModel * Read ();
     bool Delete (QString);
     bool update();
     QSqlQueryModel* sort(QString);
     QSqlQueryModel* search(QString, QString);
     int count_stat(QString idstat);
private:                                          //attributes not to be modified only by constructor,set ,get
    QString reference,NIC,idstat,licensepl;
    int cost;
    QDate date_inv;

};

#endif // INVOICE_H
