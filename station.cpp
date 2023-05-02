#include "station.h"
#include <QString>
#include <iostream>
#include <QSqlQuery>
#include <QSqlQueryModel>

   station::station(QString id_stat,QString nameStat,QString locaStat, int capacity,int nb_emp,QString availability)
    {
        this->id_stat=id_stat;
        this->nameStat=nameStat;
        this->locaStat=locaStat;
        this->capacity=capacity;
        this->nb_emp=nb_emp;
        this->availability=availability;


    }

    bool station::Create()
    {
        QSqlQuery  query;

        QString res1 = QString::number(capacity);
        QString res2 = QString::number(nb_emp);

        //prepare() takes the query as a parameter to prepare it for execution
        query.prepare("insert into station (id_stat, name_stat, location_stat,capacity,nb_emp,availability)" "values (:id_stat, :name_stat, :location_stat, :capacity, :nb_emp, :availability)");

        // Creating variables line edit takes varaible and put it in table
        query.bindValue(":capacity",res1);
        query.bindValue(":nb_emp",res2);
        query.bindValue(":name_stat",nameStat);
        query.bindValue(":location_stat",locaStat);
        query.bindValue(":id_stat",id_stat);
        query.bindValue(":nb_emp",nb_emp);
        query.bindValue(":availability",availability);

        return query.exec(); //exec() send request to be executed
    }

    QSqlQueryModel *station::Read()
    {
        QSqlQueryModel * model=new QSqlQueryModel();
// query select everything from station and display it in table view
        model->setQuery("select * from station");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("Location"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("Capacity"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("Nb. Emp"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("Availability"));
        return  model;
    }

    bool station::Delete(QString id_stat)
    {
        QSqlQuery query;

        query.prepare("Delete from station where id_stat= :id_stat");

        query.bindValue(":id_stat",id_stat);

        return  query.exec();

    }

    bool station::update()
    {
        QSqlQuery query;
            query.prepare ("update station SET id_stat = :id_stat, name_stat = :name_stat, location_stat = :location_stat, capacity = :capacity, nb_emp = :nb_emp, availability = :availability where id_stat=:id_stat" );

            QString res1 = QString::number(capacity);
            QString res2 = QString::number(nb_emp);

            // Creating variables
            query.bindValue(":capacity",res1);
            query.bindValue(":nb_emp",res2);
            query.bindValue(":name_stat",nameStat);
            query.bindValue(":location_stat",locaStat);
            query.bindValue(":id_stat",id_stat);
            query.bindValue(":nb_emp",nb_emp);
            query.bindValue(":availability",availability);

           return query.exec();
    }

    QSqlQueryModel * station::sort(QString option)
    {
        QSqlQueryModel * model=new QSqlQueryModel();

            if(option == "Station Location"){
                model->setQuery("SELECT * from station order by location_stat asc");
            }
            else if(option =="Station ID")
            {
                model->setQuery("SELECT * from station order by id_stat asc ");
            }
            else if(option =="Station Name")
            {
                model->setQuery("SELECT * from station order by name_stat asc ");
            }

            model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("Location"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("Capacity"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("Nb. Emp"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("Availability"));
            return model;
    }

    QSqlQueryModel * station::search(QString option, QString text)
    {
        QSqlQueryModel * model=new QSqlQueryModel();

            if(option == "Station Location"){
                model->setQuery("SELECT * from station where ( location_stat like '%"+text+"%' )");
            }
            else if(option =="Station ID")
            {
                model->setQuery("SELECT * from station where ( id_stat like '%"+text+"%' )");
            }
            else if(option =="Station Name")
            {
                model->setQuery("SELECT * from station where ( name_stat like '%"+text+"%' ) ");
            }

            model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
            model->setHeaderData(1,Qt::Horizontal,QObject::tr("Name"));
            model->setHeaderData(2,Qt::Horizontal,QObject::tr("Location"));
            model->setHeaderData(3,Qt::Horizontal,QObject::tr("Capacity"));
            model->setHeaderData(4,Qt::Horizontal,QObject::tr("Nb. Emp"));
            model->setHeaderData(5,Qt::Horizontal,QObject::tr("Availability"));
            return model;
    }

    int station::count_location(QString location_stat)
     {
       QSqlQuery qry;
       qry.prepare("select * from station where location_stat=:location_stat");
       qry.bindValue(":location_stat",location_stat);

       qry.exec();
       int total=0;
       while (qry.next()) total++;
       return total;

     }

