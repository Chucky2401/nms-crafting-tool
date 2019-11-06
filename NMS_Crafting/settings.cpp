#include "settings.h"

Settings::Settings() {
    m_qsAppdataPath = qEnvironmentVariable("APPDATA");
    m_qsPathRoamingBdd = m_qsAppdataPath + "\\BlackWizard Company\\bdd\\";

}

void Settings::initialisation(bool test) {
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

    m_derniereVerificationMiseAJour = this->getIniDerniereVerificationMiseAJour();
    if (m_derniereVerificationMiseAJour == QDate(1900, 01, 01)){
        m_derniereVerificationMiseAJour = QDate::currentDate();
        this->setDerniereVerificationMiseAJour(m_derniereVerificationMiseAJour);
    }

    m_messageConfirmationFermeture = this->getIniMessageConfirmationFermeture();
    this->setMessageConfirmationFermeture(m_messageConfirmationFermeture);
}

void Settings::setImagePath(QString path){
    this->imagePath = path;
    iniParam->setValue("img/path", path);
}

QString Settings::getImagePath(){
    return this->imagePath;
}

QString Settings::getIniImagePath(){
    return iniParam->value("img/path", settingDefaultString).toString();
}

void Settings::setBddPath(QString path){
    this->bddPath = path;
    iniParam->setValue("bdd/path", path);
}

QString Settings::getBddPath(){
    return this->bddPath;
}

QString Settings::getIniBddPath(){
    return iniParam->value("bdd/path", settingDefaultString).toString();
}

void Settings::setBddName(QString name){
    this->bddName = name;
    //iniParam->setValue("bdd/name", name);
}

QString Settings::getBddName(){
    return this->bddName;
}

//QString Settings::getIniBddName(){
//    return iniParam->value("bdd/name", settingDefaultString).toString();
//}

void Settings::setFarming(bool enabled){
    this->farming = enabled;
    iniParam->setValue("utilisateur/farming", enabled);
}

bool Settings::getIniFarming(){
    return iniParam->value("utilisateur/farming", settingDefaultBool).toBool();
}

bool Settings::getFarming(){
    return this->farming;
}

void Settings::setAutoExpand(bool enabled){
    this->autoExpand = enabled;
    iniParam->setValue("utilisateur/autoExpand", enabled);
}

bool Settings::getIniAutoExpand(){
    return iniParam->value("utilisateur/autoExpand", settingDefaultBool).toBool();
}

bool Settings::getAutoExpand(){
    return this->autoExpand;
}

void Settings::setRestoreRecipe(bool enabled){
    this->restoreRecipe = enabled;
    iniParam->setValue("utilisateur/restoreRecipe", enabled);
}

bool Settings::getIniRestoreRecipe(){
    return iniParam->value("utilisateur/restoreRecipe", settingDefaultBool).toBool();
}

bool Settings::getRestoreRecipe(){
    return this->restoreRecipe;
}

void Settings::setLastRecipe(QList<QVariant> name){
    this->lastRecipe = name;
    iniParam->setValue("utilisateur/LastRecipe", name);
}

QList<QVariant> Settings::getLastRecipe(){
    return this->lastRecipe;
}

QList<QVariant> Settings::getIniLastRecipe(){
    return iniParam->value("utilisateur/LastRecipe", settingDefaultString).toList();
}

void Settings::setQteLastRecipe(int quantite){
    this->quantiteLastRecipe = quantite;
    iniParam->setValue("utilisateur/quantiteLastRecipe", quantite);
}

int Settings::getIniQteLastRecipe(){
    return iniParam->value("utilisateur/quantiteLastRecipe", settingDefaultInt).toInt();
}

int Settings::getQteLastRecipe(){
    return this->quantiteLastRecipe;
}

void Settings::setGeometrie(QByteArray geometrie){
    this->geometrie = geometrie;
    iniParam->setValue("fenetre/geometrie", geometrie);
}

void Settings::setEtat(QByteArray etat){
    this->etat = etat;
    iniParam->setValue("fenetre/etat", etat);
}

void Settings::setGeometrieEtat(QByteArray geometrie, QByteArray etat){
    this->geometrie = geometrie;
    this->etat = etat;
    iniParam->setValue("fenetre/geometry", geometrie);
    iniParam->setValue("fenetre/state", etat);
}

QByteArray Settings::getIniGeometrie(){
    return iniParam->value("fenetre/geometry", settingDefaultByteArray).toByteArray();
}

QByteArray Settings::getGeometrie(){
    return this->geometrie;
}

QByteArray Settings::getIniEtat(){
    return iniParam->value("fenetre/state", settingDefaultByteArray).toByteArray();
}

QByteArray Settings::getEtat(){
    return this->etat;
}

void Settings::setRestoreSizePos(bool enabled){
    this->restoreSizePos = enabled;
    iniParam->setValue("fenetre/restoreSizePos", enabled);
}

bool Settings::getIniRestoreSizePos(){
    return iniParam->value("fenetre/restoreSizePos", settingDefaultBool).toBool();
}

bool Settings::getRestoreSizePos(){
    return this->restoreSizePos;
}

void Settings::setVisibiliteFarming(bool visible){
    this->m_visibiliteFarming = visible;
    iniParam->setValue("affichage/boutonFarmVisible", visible);
}

bool Settings::getIniVisibiliteFarming(){
    return iniParam->value("affichage/boutonFarmVisible", true).toBool();
}

bool Settings::getVisibiliteFarming(){
    return this->m_visibiliteFarming;
}

void Settings::setVisibiliteDeploiementAuto(bool visible){
    this->m_visibiliteDeploiementAuto = visible;
    iniParam->setValue("affichage/boutonDeploiementAuto", visible);
}

bool Settings::getIniVisibiliteDeploiementAuto(){
    return iniParam->value("affichage/boutonDeploiementAuto", true).toBool();
}

bool Settings::getVisibiliteDeploiementAuto(){
    return this->m_visibiliteDeploiementAuto;
}

void Settings::setVerificationAutoMiseAJour(bool enabled){
    this->m_verificationAutoMiseAJour = enabled;
    iniParam->setValue("miseAJour/automatique", enabled);
}

bool Settings::getIniVerificationAutoMiseAJour(){
    return iniParam->value("miseAJour/automatique", settingDefaultBool).toBool();
}

bool Settings::getVerificationAutoMiseAJour(){
    return this->m_verificationAutoMiseAJour;
}

void Settings::setNombreJourMiseAJour(int nombreJour){
    this->m_nombreJourMiseAJour = nombreJour;
    iniParam->setValue("miseAJour/nombreJour", nombreJour);
}

int Settings::getIniNombreJourMiseAJour(){
    return iniParam->value("miseAJour/nombreJour", 7).toInt();
}

int Settings::getNombreJourMiseAJour(){
    return m_nombreJourMiseAJour;
}

void Settings::setDerniereVerificationMiseAJour(QDate date){
    this->m_derniereVerificationMiseAJour = date;
    qDebug() << "\tsetDerniereVerificationMiseAjour - Date : " << date;
    iniParam->setValue("miseAJour/derniereVerification", date);
}

QDate Settings::getIniDerniereVerificationMiseAJour(){
    return iniParam->value("miseAJour/derniereVerification", QDate(1900, 01, 01)).toDate();
}

QDate Settings::getDerniereVerificationMiseAJour(){
    return m_derniereVerificationMiseAJour;
}

QDate Settings::getProchaineVerificationMiseAjour() {
    return m_derniereVerificationMiseAJour.addDays(this->m_nombreJourMiseAJour);
}

void Settings::setMessageConfirmationFermeture(bool enabled){
    this->m_messageConfirmationFermeture = enabled;
    iniParam->setValue("fenetre/confirmationFermeture", enabled);
}

bool Settings::getIniMessageConfirmationFermeture(){
    return iniParam->value("fenetre/confirmationFermeture", true).toBool();
}

bool Settings::getMessageConfirmationFermeture(){
    return m_messageConfirmationFermeture;
}
