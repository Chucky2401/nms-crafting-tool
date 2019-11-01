#include "settings.h"

settings::settings() {
    m_qsAppdataPath = qEnvironmentVariable("APPDATA");
    m_qsPathRoamingBdd = m_qsAppdataPath + "\\BlackWizard Company\\bdd\\";

}

void settings::initialisation(bool test) {
    iniParam = new QSettings(QSettings::IniFormat, QSettings::UserScope, "BlackWizard Company", "NMS Crafting Tool");

    imagePath = this->getIniImagePath();
    if (imagePath == settingDefaultString){
        this->setImagePath("./img/");
    }

    bddPath = this->getIniBddPath();
    if (bddPath == settingDefaultString){
        this->setBddPath(m_qsPathRoamingBdd);
    }

    if (test){
        this->setBddName("nms_database-TEST.db");
    } else {
        this->setBddName("nms_database.db");
    }
    //bddName = this->getIniBddName();

    farming = this->getIniFarming();
    this->setFarming(farming);

    autoExpand = this->getIniAutoExpand();
    this->setAutoExpand(autoExpand);

    restoreRecipe = this->getIniRestoreRecipe();
    this->setRestoreRecipe(restoreRecipe);

    lastRecipe = this->getIniLastRecipe();
    quantiteLastRecipe = this->getIniQteLastRecipe();

    geometrie = this->getIniGeometrie();
    etat = this->getIniEtat();
    restoreSizePos = this->getIniRestoreSizePos();
    this->setRestoreSizePos(restoreSizePos);
}

void settings::setImagePath(QString path){
    this->imagePath = path;
    iniParam->setValue("img/path", path);
}

QString settings::getImagePath(){
    return this->imagePath;
}

QString settings::getIniImagePath(){
    return iniParam->value("img/path", settingDefaultString).toString();
}

void settings::setBddPath(QString path){
    this->bddPath = path;
    iniParam->setValue("bdd/path", path);
}

QString settings::getBddPath(){
    return this->bddPath;
}

QString settings::getIniBddPath(){
    return iniParam->value("bdd/path", settingDefaultString).toString();
}

void settings::setBddName(QString name){
    this->bddName = name;
    //iniParam->setValue("bdd/name", name);
}

QString settings::getBddName(){
    return this->bddName;
}

//QString settings::getIniBddName(){
//    return iniParam->value("bdd/name", settingDefaultString).toString();
//}

void settings::setFarming(bool enabled){
    this->farming = enabled;
    iniParam->setValue("utilisateur/farming", enabled);
}

bool settings::getIniFarming(){
    return iniParam->value("utilisateur/farming", settingDefaultBool).toBool();
}

bool settings::getFarming(){
    return this->farming;
}

void settings::setAutoExpand(bool enabled){
    this->autoExpand = enabled;
    iniParam->setValue("utilisateur/autoExpand", enabled);
}

bool settings::getIniAutoExpand(){
    return iniParam->value("utilisateur/autoExpand", settingDefaultBool).toBool();
}

bool settings::getAutoExpand(){
    return this->autoExpand;
}

void settings::setRestoreRecipe(bool enabled){
    this->restoreRecipe = enabled;
    iniParam->setValue("utilisateur/restoreRecipe", enabled);
}

bool settings::getIniRestoreRecipe(){
    return iniParam->value("utilisateur/restoreRecipe", settingDefaultBool).toBool();
}

bool settings::getRestoreRecipe(){
    return this->restoreRecipe;
}

void settings::setLastRecipe(QList<QVariant> name){
    this->lastRecipe = name;
    iniParam->setValue("utilisateur/LastRecipe", name);
}

QList<QVariant> settings::getLastRecipe(){
    return this->lastRecipe;
}

QList<QVariant> settings::getIniLastRecipe(){
    return iniParam->value("utilisateur/LastRecipe", settingDefaultString).toList();
}

void settings::setQteLastRecipe(int quantite){
    this->quantiteLastRecipe = quantite;
    iniParam->setValue("utilisateur/quantiteLastRecipe", quantite);
}

int settings::getIniQteLastRecipe(){
    return iniParam->value("utilisateur/quantiteLastRecipe", settingDefaultInt).toInt();
}

int settings::getQteLastRecipe(){
    return this->quantiteLastRecipe;
}

void settings::setGeometrie(QByteArray geometrie){
    this->geometrie = geometrie;
    iniParam->setValue("fenetre/geometrie", geometrie);
}

void settings::setEtat(QByteArray etat){
    this->etat = etat;
    iniParam->setValue("fenetre/etat", etat);
}

void settings::setGeometrieEtat(QByteArray geometrie, QByteArray etat){
    this->geometrie = geometrie;
    this->etat = etat;
    iniParam->setValue("fenetre/geometry", geometrie);
    iniParam->setValue("fenetre/state", etat);
}

QByteArray settings::getIniGeometrie(){
    return iniParam->value("fenetre/geometry", settingDefaultByteArray).toByteArray();
}

QByteArray settings::getGeometrie(){
    return this->geometrie;
}

QByteArray settings::getIniEtat(){
    return iniParam->value("fenetre/state", settingDefaultByteArray).toByteArray();
}

QByteArray settings::getEtat(){
    return this->etat;
}

void settings::setRestoreSizePos(bool enabled){
    this->restoreSizePos = enabled;
    iniParam->setValue("fenetre/restoreSizePos", enabled);
}

bool settings::getIniRestoreSizePos(){
    return iniParam->value("fenetre/restoreSizePos", settingDefaultBool).toBool();
}

bool settings::getRestoreSizePos(){
    return this->restoreSizePos;
}
