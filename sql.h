#ifndef SQL_H
#define SQL_H

#include <QSqlQuery>
#include <QSqlDriver>
#include <QDebug>
#include <QSqlError>
#include <cmath>

class sql
{
public:
    sql();
    QSqlDatabase database;
    static void initialize();
};

// package the sql statements to avoid
bool INSERT(QString table, QString* pointer, int length);
QSqlQuery SELECT_ALL(QString table);
QSqlQuery SELECT(QString table, QString items, QString conditions);
bool UPDATE(QString table, QString columnName, QString value, QString conditions);
bool DELETE(QString table, QString conditions);
bool ALTER(QString table, QString operation, QString conditions);

#endif // SQL_H
