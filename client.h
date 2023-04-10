#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class client
{
public:
    //constructor
    client();
    client(QString NIC, QString f, QString l, QString m, QString p, QString c);

        //setters
        void setNIC(QString);
        void setFirstName(QString);
        void setLastName(QString);
        void setEmail(QString);
        void setPhone(QString);
        void setCredit(QString);

        //getters
        QString getNIC();
        QString getFirstName();
        QString getLastName();
        QString getEmail();
        QString getPhone();
        QString getCredit();

        //CRUD features
        bool Create ();
        QSqlQueryModel * Read ();
        bool Delete (QString);
        bool update();
        QSqlQueryModel* sort(QString);
        QSqlQueryModel* search(QString, QString);
        int count_credit(QString credit);

    private:
        QString NIC, fname, lname, mail, phoneC, credit;
};

#endif // CLIENT_H
