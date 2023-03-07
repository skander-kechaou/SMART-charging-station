#include "client.h"

client::client()
{
    NIC="";
    fname="";
    lname="";
    mail="";
    phoneC="";
    credit="";
}

client::client(QString NIC, QString f, QString l, QString m, QString p, QString c)
{
this->NIC=NIC;
fname=f;
lname=l;
mail=m;
phoneC=p;
credit=c;
}

bool client::Create()
{
    QSqlQuery query;


        //prepare() takes the query as a parameter to prepare it for execution
        query.prepare("insert into client (NIC, fname, lname, phoneC, mail, credit)" "values (:NIC, :fname, :lname, :phoneC, :mail, :credit)");

        // Creating variables
        query.bindValue(":NIC",NIC);
        query.bindValue(":fname",fname);
        query.bindValue(":lname",lname);
        query.bindValue(":phoneC",phoneC);
        query.bindValue(":mail",mail);
        query.bindValue(":credit", credit);

        return query.exec(); //exec() send request to be executed
}

QSqlQueryModel * client::Read()
{
    QSqlQueryModel * model=new QSqlQueryModel();

        model->setQuery("select * from client");
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("NIC"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("First Name"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("Last Name"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("Phone"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("E-mail"));
        model->setHeaderData(5,Qt::Horizontal,QObject::tr("Credit"));

        return  model;
}

bool client::Delete(QString NIC)
{
    QSqlQuery query;

        query.prepare("Delete from client where NIC= :NIC");

        query.bindValue(":NIC",NIC);

        return  query.exec();
}

bool client::update()
{
    QSqlQuery query;
        query.prepare ("update client SET NIC = :NIC, fname = :fname, lname = :lname, phoneC = :phoneC, mail = :mail, credit = :credit" );

        // Creating variables
        query.bindValue(":NIC",NIC);
        query.bindValue(":fname",fname);
        query.bindValue(":lname",lname);
        query.bindValue(":phoneC",phoneC);
        query.bindValue(":mail",mail);
        query.bindValue(":credit", credit);

       return query.exec();
}

void client::setNIC(QString c){
    NIC=c;
}
void client::setFirstName(QString fn){
    fname=fn;
}
void client::setLastName(QString ln){
    lname=ln;
}
void client::setEmail(QString e){
    mail=e;
}
void client::setPhone(QString p){
    phoneC=p;
}
void client::setCredit(QString cr){
    credit=cr;
}
QString client::getNIC(){
    return NIC;
}
QString client::getFirstName(){
    return fname;
}
QString client::getLastName(){
    return lname;
}
QString client::getEmail(){
    return mail;
}
QString client::getPhone(){
    return phoneC;
}
QString client::getCredit(){
    return credit;
}
