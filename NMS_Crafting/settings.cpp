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

    m_visibiliteFarming = this->getIniVisibiliteFarming();
    this->setVisibiliteFarming(m_visibiliteFarming);

    m_visibiliteDeploiementAuto = this->getIniVisibiliteDeploiementAuto();
    this->setVisibiliteDeploiementAuto(m_visibiliteDeploiementAuto);

    m_verificationAutoMiseAJour = this->getIniVerificationAutoMiseAJour();
    this->setVerificationAutoMiseAJour(m_verificationAutoMiseAJour);

    m_nombreJourMiseAJour = this->getIniNombreJourMiseAJour();
    this->setNombreJourMiseAJour(m_nombreJourMiseAJour);
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

void settings::setVisibiliteFarming(bool visible){
    this->m_visibiliteFarming = visible;
    iniParam->setValue("affichage/boutonFarmVisible", visible);
}

bool settings::getIniVisibiliteFarming(){
    return iniParam->value("affichage/boutonFarmVisible", true).toBool();
}

bool settings::getVisibiliteFarming(){
    return this->m_visibiliteFarming;
}

void settings::setVisibiliteDeploiementAuto(bool visible){
    this->m_visibiliteDeploiementAuto = visible;
    iniParam->setValue("affichage/boutonDeploiementAuto", visible);
}

bool settings::getIniVisibiliteDeploiementAuto(){
    return iniParam->value("affichage/boutonDeploiementAuto", true).toBool();
}

bool settings::getVisibiliteDeploiementAuto(){
    return this->m_visibiliteDeploiementAuto;
}

void settings::setVerificationAutoMiseAJour(bool enabled){
    this->m_verificationAutoMiseAJour = enabled;
    iniParam->setValue("miseAJour/automatique", enabled);
}

bool settings::getIniVerificationAutoMiseAJour(){
    return iniParam->value("miseAJour/automatique", settingDefaultBool).toBool();
}

bool settings::getVerificationAutoMiseAJour(){
    return this->m_verificationAutoMiseAJour;
}

void settings::setNombreJourMiseAJour(int nombreJour){
    this->m_nombreJourMiseAJour = nombreJour;
    iniParam->setValue("miseAJour/nombreJour", nombreJour);
}

int settings::getIniNombreJourMiseAJour(){
    return iniParam->value("miseAJour/nombreJour", 7).toInt();
}

int settings::getNombreJourMiseAJour(){
    return m_nombreJourMiseAJour;
}

void settings::setProchaineVerificationMiseAJour(QDate date){
    this->m_prochaineVerificationMiseAJour = date;
    qDebug() << date;
    iniParam->setValue("miseAJour/prochaineVerification", date);
}

QDate settings::getIniProchaineVerificationMiseAJour(){
    return iniParam->value("miseAJour/prochaineVerification", QDate::currentDate()).toDate();
}

QDate settings::getProchaineVerificationMiseAJour(){
    return m_prochaineVerificationMiseAJour;
}
