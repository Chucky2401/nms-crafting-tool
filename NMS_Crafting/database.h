#ifndef DATABASE_H
#define DATABASE_H

#include <QFile>
#include <QString>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

#include "settings.h"


class database// : public QSqlDatabase
{
public:
    database();
    ~database();
    bool createConnection(QString name);
    void closeConnection(QString name);
    bool isOpen(QString name);
    QSqlDatabase getBase();
    void resetAll();
    void resetError();
    QString getError();
    void setError(QString error);

    QVariant requete(QString sql);

private:
    QSqlDatabase base;
    QString lastBddError;
    QSqlQuery query;

    class settings param;
};

#endif // DATABASE_H
