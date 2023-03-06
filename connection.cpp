#include "connection.h"

connection::connection()
{

}
bool connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source_project2A");
    db.setUserName("youssef");//insert the user name
    db.setPassword("youssef");//inseret the password

    if (db.open())
        test=true;





    return  test;
}

void connection::closeconnect()
{
    db.close();
}
