#include "connection.h"

Connection::Connection()
{

}
bool Connection::createconnection()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source_project2A");
    db.setUserName("noura");//insert the user name
    db.setPassword("noura");//inseret the password

    if (db.open())
        test=true;





    return  test;
}
