#ifndef SQLITECONNECTION_H
#define SQLITECONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QCoreApplication>
static bool createConnection(QSqlDatabase* db)
{
    db->setDatabaseName(QCoreApplication::applicationDirPath() + "/obi-wan-sqlite_v0_2.db");
    if (!db->open()) {
        QMessageBox::critical(nullptr, QObject::tr("Cannot open database"),
            QObject::tr("Unable to establish a database connection.\n"
                        "This example needs SQLite support. Please read "
                        "the Qt SQL driver documentation for information how "
                        "to build it.\n\n"
                        "Click Cancel to exit."), QMessageBox::Cancel);
        return false;
    }

    QSqlQuery query;
    query.exec("create table job (id integer primary key,"
               "name text,"
               "height integer,"
               "measure integer,"
               "quantity integer,"
               "state integer,"
               "remaining_quantity,"
               "date integer,"
               "priority integer)");

    query.exec("insert into job values(1, 'saraza', 30, 0, 100, 0, 100, 10000, 0)");


    return true;
}

#endif // SQLITECONNECTION_H
