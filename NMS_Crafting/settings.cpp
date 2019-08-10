#include "settings.h"

settings::settings()
{
    iniParam = new QSettings(QSettings::IniFormat, QSettings::UserScope, "BlackWizard Company", "NMS Crafting Tool");

    imagePath = this->getIniImagePath();
    if (imagePath == settingDefaultString){
        this->setImagePath("./img/");
    }

    bddPath = this->getIniBddPath();
    if (bddPath == settingDefaultString){
        this->setBddPath("./bdd/");
    }

    bddName = this->getIniBddName();
    if (bddName == settingDefaultString){
        this->setBddName("nms_database-TEST.db");
    }

    farming = this->getIniFarming();
    this->setFarming(farming);

    autoExpand = this->getIniAutoExpand();
    this->setAutoExpand(autoExpand);

    this->restoreRecipe = this->getIniRestoreRecipe();
    this->setRestoreRecipe(restoreRecipe);

    lastRecipe = this->getIniLastRecipe();
    quantiteLastRecipe = this->getIniQteLastRecipe();
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
    iniParam->setValue("bdd/name", name);
}

QString settings::getBddName(){
    return this->bddName;
}

QString settings::getIniBddName(){
    return iniParam->value("bdd/name", settingDefaultString).toString();
}

void settings::setFarming(bool enabled){
    this->farming = enabled;
    iniParam->setValue("utilisateur/farming", enabled);
}

bool settings::getIniFarming(){
    return iniParam->value("utilisateur/farming").toBool();
}

bool settings::getFarming(){
    return this->farming;
}

void settings::setAutoExpand(bool enabled){
    this->autoExpand = enabled;
    iniParam->setValue("utilisateur/autoExpand", enabled);
}

bool settings::getIniAutoExpand(){
    return iniParam->value("utilisateur/autoExpand").toBool();
}

bool settings::getAutoExpand(){
    return this->autoExpand;
}

void settings::setRestoreRecipe(bool enabled){
    this->restoreRecipe = enabled;
    iniParam->setValue("utilisateur/restoreRecipe", enabled);
}

bool settings::getIniRestoreRecipe(){
    return iniParam->value("utilisateur/restoreRecipe").toBool();
}

bool settings::getRestoreRecipe(){
    return this->restoreRecipe;
}

void settings::setLastRecipe(QString name){
    this->lastRecipe = name;
    iniParam->setValue("utilisateur/LastRecipe", name);
}

QString settings::getLastRecipe(){
    return this->lastRecipe;
}

QString settings::getIniLastRecipe(){
    return iniParam->value("utilisateur/LastRecipe", settingDefaultString).toString();
}

void settings::setQteLastRecipe(int quantite){
    this->quantiteLastRecipe = quantite;
    iniParam->setValue("utilisateur/quantiteLastRecipe", quantite);
}

int settings::getIniQteLastRecipe(){
    return iniParam->value("utilisateur/quantiteLastRecipe", settingDefaultInt).toInt();
}

int settings::getQteLastRecipe(){
    return iniParam->value("utilisateur/quantiteLastRecipe", settingDefaultInt).toInt();
}
