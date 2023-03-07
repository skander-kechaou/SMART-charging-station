#ifndef STATION_H
#define STATION_H


class station
{
    int id_stat;
    int capacity;
    QString nameStat, locaStat;

  public:

      //Constructors
      station(){}
      station(int,QString,QString);

      //Getters
      QString getnameStat(){return  nameStat;}
      QString getlocaStat(){return  locaStat;}
      int getid_stat(){return  id_stat;}
       int getcapacity(){return  capacity;}

      //Setters
      void setnameStat(QString n){nameStat=n;}
      void setlocaStat(QString p){locaStat=p;}
      void setid_Stat(int id_Stat){this->id_Stat=id_Stat;}
       void setcapacity(int capacity){this->capacity=capacity;}

      // Student base features
      bool Create ();
      QSqlQueryModel * Read ();
      bool Delete (int);

  };
public:
    station();
};

#endif // STATION_H
