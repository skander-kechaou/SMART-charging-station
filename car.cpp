#include "car.h"

car::car(QString licence_plate,QString brand,QString client_id,float battery)
{
    this->battery=battery;
    this->licence_plate=licence_plate;
    this->brand=brand;
    this->client_id=client_id;

}
car::car()
{
    battery=0;
    licence_plate="";
    brand="";
    client_id="";

}
void car::setlicenceplate(QString c){
    licence_plate=c;
}
void car::setbrand(QString b){
    brand=b;
}
void car::setownerid(QString id){
    client_id=id;
}
void car::setbatterycap(float e){
    battery=e;
}
QString car::getlicenceplate(){
    return licence_plate;
}
QString car::getbrand(){
    return brand;
}
float car::getbatterycap(){
    return battery;
}
QString car::getownerid(){
    return client_id;
}

bool car::createcar()
{
    QSqlQuery query;

    QString res = QString::number(battery);
    query.prepare("insert into car (licence_plate,brand,battery,client_id)" "values (:licence_plate,:brand,:battery,:client_id");

    query.bindValue(":licence_plate",licence_plate);
    query.bindValue(":brand",brand);
    query.bindValue(":battery",res);
    query.bindValue(":client_id",client_id);


    return query.exec();

}
QSqlQueryModel * car::readcar()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from CAR");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("licence_plate"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("brand"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("battery"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("client_id"));

    return  model;
}
bool car::deletecar(QString licence_plate)
{
    QSqlQuery query;

    query.prepare("Delete from car where licence_plate= :licence_plate");

    query.bindValue(":licence_plate",licence_plate);

    return  query.exec();
}

