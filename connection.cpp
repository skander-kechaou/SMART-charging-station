
#include "connection.h"

Connection::Connection(){}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("projet2a");// insert the name of data source ODBC
    db.setUserName("noura");//insert username
    db.setPassword("projetcpp");//insert passeword

    if (db.open()) ;

        return  test;
    return true;
}

void Connection::closeConnection(){ db.close(); }
