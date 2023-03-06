#ifndef CAR_H
#define CAR_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>

class car
{
public:
    car();
    car(QString,QString,QString,float);
    void setlicenceplate(QString);
    void setbrand(QString);
    void setbatterycap(float);
    void setownerid(QString);
    QString getlicenceplate();
    QString getbrand();
    float getbatterycap();
    QString getownerid();
    bool createcar();
    QSqlQueryModel * readcar();
    bool deletecar (QString);

private:
    QString licence_plate,brand,client_id;
    float battery;

};

#endif // CAR_H
