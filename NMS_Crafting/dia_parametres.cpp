#include "dia_parametres.h"
#include "ui_dia_parametres.h"

DIA_Parametres::DIA_Parametres(Settings *set, QWidget *parent, bool m_test) :
    QDialog(parent),
    ui(new Ui::DIA_Parametres), param(set)
{
    ui->setupUi(this);
    set->initialisation(m_test);

    /*
     * Définitions de l'état des objets en fonction des paramètres INI
     */
    // CheckBox
    ui->cbRestoreSizePos->setChecked(set->getRestoreSizePos());
    ui->cbRestoreRecipe->setChecked(set->getRestoreRecipe());
    ui->cbMessageFermeture->setChecked(set->getMessageConfirmationFermeture());
    ui->cbFarmingVisible->setChecked(set->getVisibiliteFarming());
    ui->cbEtendreVisible->setChecked(set->getVisibiliteDeploiementAuto());

    /*
     * Connections !
     */
    // Général
    connect(ui->cbMiseAJourAuto, SIGNAL(toggled(bool)), this, SLOT(setMiseAJourAuto(bool)));
    connect(ui->sbNombreJourMiseAJour, SIGNAL(valueChanged(int)), this, SLOT(setNombreJourMiseAJour(int)));
    connect(ui->cbRestoreRecipe, SIGNAL(toggled(bool)), this, SLOT(setRestoreRecipe(bool)));
    connect(ui->cbRestoreSizePos, SIGNAL(toggled(bool)), this, SLOT(setRestoreSizePos(bool)));
    connect(ui->cbMessageFermeture, SIGNAL(toggled(bool)), this, SLOT(setMessageConfirmationFermeture(bool)));
    //Affichage
    connect(ui->cbFarmingVisible, SIGNAL(toggled(bool)), this, SLOT(setVisibiliteFarming(bool)));
    connect(ui->cbEtendreVisible, SIGNAL(toggled(bool)), this, SLOT(setVisibiliteDeploiementAuto(bool)));

    /*
     * Définitions de l'état des objets en fonction des paramètres INI
     * Cette partie doit être fait après connexion pour mise à jour d'autres champs
     */
    // CheckBox
    ui->cbMiseAJourAuto->setChecked(set->getVerificationAutoMiseAJour());
    // SpinBox
    ui->sbNombreJourMiseAJour->setValue(set->getNombreJourMiseAJour());

    if(set->getNombreJourMiseAJour() == 1) {
        ui->lMiseAJour2->setText("jour");
    } else {
        ui->lMiseAJour2->setText("jours");
    }
}

DIA_Parametres::~DIA_Parametres()
{
    delete ui;
}

/*       *
 * SLOTS *
 *       *
 */
void DIA_Parametres::setRestoreRecipe(bool state){
    param->setRestoreRecipe(state);
}

void DIA_Parametres::setRestoreSizePos(bool state){
    param->setRestoreSizePos(state);
}

void DIA_Parametres::setMessageConfirmationFermeture(bool state){
    param->setMessageConfirmationFermeture(state);
}

void DIA_Parametres::setVisibiliteFarming(bool visible){
    param->setVisibiliteFarming(visible);
    emit visibiliteFarming(visible);
}

void DIA_Parametres::setVisibiliteDeploiementAuto(bool visible){
    param->setVisibiliteDeploiementAuto(visible);
    emit visibiliteDeploiementAuto(visible);
}

void DIA_Parametres::setMiseAJourAuto(bool enabled){
    param->setVerificationAutoMiseAJour(enabled);
    ui->lMiseAJour1->setEnabled(enabled);
    ui->sbNombreJourMiseAJour->setEnabled(enabled);
    ui->lMiseAJour2->setEnabled(enabled);
}

void DIA_Parametres::setNombreJourMiseAJour(int nombreJour){
    param->setNombreJourMiseAJour(nombreJour);
    if(nombreJour == 1) {
        ui->lMiseAJour2->setText("jour");
    } else {
        ui->lMiseAJour2->setText("jours");
    }
}
