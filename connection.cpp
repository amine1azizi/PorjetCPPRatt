#include "connection.h"
#include <QDebug>

Connection::Connection(){}

bool Connection::createconnection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("Source_Project2A");
    db.setUserName("amine");
    db.setPassword("key");
    if (db.open())
    test=true;




        return  test;
}

void Connection::closeConnection(){ db.close(); }
