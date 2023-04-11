#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class car
{
public:
    //constructor
    car();
    car(QString licence_plate, QString brand, QString type, QString hp, QString batterycap, QString client_id,QString imagepath);

        //setters
        void setlc(QString);
        void setbrand(QString);
        void settype(QString);
        void sethp(QString);
        void setbatterycap(QString);
        void setclient_id(QString);
        void setimagepath(QString);

        //getters
        QString getlc();
        QString getbrand();
        QString gettype();
        QString gethp();
        QString getbatterycap();
        QString getclient_id();
        QString getimagepath();

        //CRUD features
        bool Create ();
        QSqlQueryModel * Read ();
        bool Delete (QString);
        bool update();
        QSqlQueryModel* sort(QString);
        QSqlQueryModel* search(QString, QString);
        int count_brand(QString brand);

    private:
        QString licence_plate,  brand,  type,  hp,  batterycap, client_id,imagepath;
};

#endif // CLIENT_H
