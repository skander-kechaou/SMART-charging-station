#include "station.h"

   station::Station(int id_stat,int capacity ,QString nameStat,QString locaStat)
    {
        this->id_stat=id_stat;
        this->nameStat=nameStat;
        this->locaStat=locaStat;

    }

    bool Station::Create()
    {
        QSqlQuery  query;

        QString res = QString::number(id_stat);

        //prepare() takes the query as a parameter to prepare it for execution
        query.prepare("insert intostation (id_stat, nameStat, locaStat)" "values (:id_stat, :nameStat, :locaStat)");

        // Creating variables
        query.bindValue(":id_stat",res);
        query.bindValue(":nameStat",nameStat);
        query.bindValue(":locaStat",locaStat);

        return query.exec(); //exec() send request to be executed
    }

    QSqlQueryModel *station::Read()
    {
        QSqlQueryModel * model=new QSqlQueryModel();

        model->setQuery("select * from station");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("id_stat"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("nameStat"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("locaStat"));

        return  model;
    }

    boolstation::Delete(int id_stat)
    {
        QSqlQuery query;
        QString res=QString::number(id_stat);

        query.prepare("Delete fromstation where id_stat= :id_stat");

        query.bindValue(":id_stat",res);

        return  query.exec();

    }
}
