#include "connection.h"

connection::connection()
{

}
bool connection::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source_project2A");
    db.setUserName("Skander");//insert the user name
    db.setPassword("skan2308");//inseret the password

    if (db.open())
        test=true;





    return  test;
}
