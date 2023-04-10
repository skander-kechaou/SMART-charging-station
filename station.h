#ifndef STATION_H
#define STATION_H
#include <QtCore/QString>
#include <iostream>
#include <QSqlQuery>
#include <QSqlQueryModel>

class station
{
private:
      QString id_stat;
     QString nameStat;
     QString  locaStat;
     int capacity;
     int nb_emp;
     QString availability;

  public:

      //Constructors
      station(){}
      station( QString,QString,QString,int,int,QString);

      //Getters
       QString getid_stat(){return  id_stat;}
      QString getnameStat(){return  nameStat;}
      QString getlocaStat(){return  locaStat;}
       int getcapacity(){return  capacity;}
       int getnb_emp(){return  nb_emp;}
       QString getavailability(){return availability;}
      //Setters
       void setid_stat( QString id_stat){this->id_stat=id_stat;}
      void setnameStat(QString n){nameStat=n;}
      void setlocaStat(QString p){locaStat=p;}
       void setcapacity(int capacity){this->capacity=capacity;}
       void setnb_emp(int nb_emp){this->nb_emp=nb_emp;}
       void setavailability(QString availability){this->availability=availability;}

      // Student base features
      bool Create();
      QSqlQueryModel * Read();
      bool Delete( QString);
      bool update();
       QSqlQueryModel* sort(QString);
       QSqlQueryModel* search(QString, QString);
       int count_location(QString location_stat);

  };

#endif // STATION_H
