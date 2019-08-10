#include "database.h"

database::database()
{

}

database::~database(){
    this->base.close();
}

/*
 * Fonction d'ouverture de la connexion à la Base de données
 */
bool database::createConnection(QString name)
{
    this->base = QSqlDatabase::addDatabase("QSQLITE", name);
    this->resetAll();

    if(QFile::exists(param.getBddPath()+param.getBddName())){
        this->base.setDatabaseName(param.getBddPath()+param.getBddName());
        if (!this->base.open()) {
            setError(this->base.lastError().text());
            return false;
        }
        return true;
    } else {
        setError("La base n'existe pas !");
        return false;
    }

}

void database::closeConnection(QString name){
    QSqlDatabase::database(name);
    this->base.close();
    this->base.removeDatabase(name);
}

bool database::isOpen(QString name){
    QSqlDatabase::database(name);
    return base.isOpen();
}

QSqlDatabase database::getBase(){
    return this->base;
}

void database::resetAll(){
    resetError();
}

void database::resetError(){
    this->lastBddError = "";
}

QString database::getError(){
    return this->lastBddError;
}

void database::setError(QString error){
    this->lastBddError = error;
}

QVariant database::requete(QString sql){
    this->query.exec(sql);
}
