#include "connection.h"

connection::connection()
{

}
bool connection::createconnect()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
       bool test=false;
    db.setDatabaseName("source_project2A");
    db.setUserName("nada");//insert the user name
    db.setPassword("nada");//inseret the password

    if (db.open())
        test=true;





    return  test;
    return true;
}
void connection::closeconnection()
{
    db.close();
}
