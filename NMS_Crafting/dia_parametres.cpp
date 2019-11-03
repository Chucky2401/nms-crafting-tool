#include "dia_parametres.h"
#include "ui_dia_parametres.h"

DIA_Parametres::DIA_Parametres(QWidget *parent, bool m_test) :
    QDialog(parent),
    ui(new Ui::DIA_Parametres)
{
    ui->setupUi(this);
    param.initialisation(m_test);

    /*
     * Définitions de l'état des objets en fonction des paramètres INI
     */
    // CheckBox
    ui->cbRestoreSizePos->setChecked(param.getRestoreSizePos());
    ui->cbRestoreRecipe->setChecked(param.getRestoreRecipe());
    ui->cbFarmingVisible->setChecked(param.getVisibiliteFarming());
    ui->cbEtendreVisible->setChecked(param.getVisibiliteDeploiementAuto());
    // SpinBox
    ui->sbNombreJourMiseAJour->setValue(param.getNombreJourMiseAJour());

    /*
     * Connections !
     */
    // Général
    connect(ui->cbMiseAJourAuto, SIGNAL(toggled(bool)), this, SLOT(setMiseAJourAuto(bool)));
    connect(ui->sbNombreJourMiseAJour, SIGNAL(valueChanged(int)), this, SLOT(setNombreJourMiseAJour(int)));
    connect(ui->cbRestoreRecipe, SIGNAL(toggled(bool)), this, SLOT(setRestoreRecipe(bool)));
    connect(ui->cbRestoreSizePos, SIGNAL(toggled(bool)), this, SLOT(setRestoreSizePos(bool)));
    //Affichage
    connect(ui->cbFarmingVisible, SIGNAL(toggled(bool)), this, SLOT(setVisibiliteFarming(bool)));
    connect(ui->cbEtendreVisible, SIGNAL(toggled(bool)), this, SLOT(setVisibiliteDeploiementAuto(bool)));

    /*
     * Définitions de l'état des objets en fonction des paramètres INI
     * Cette partie doit être fait après connexion pour mise à jour d'autres champs
     */
    // CheckBox
    ui->cbMiseAJourAuto->setChecked(param.getVerificationAutoMiseAJour());
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
    param.setRestoreRecipe(state);
}

void DIA_Parametres::setRestoreSizePos(bool state){
    param.setRestoreSizePos(state);
}

void DIA_Parametres::setVisibiliteFarming(bool visible){
    param.setVisibiliteFarming(visible);
    emit visibiliteFarming(visible);
}

void DIA_Parametres::setVisibiliteDeploiementAuto(bool visible){
    param.setVisibiliteDeploiementAuto(visible);
    emit visibiliteDeploiementAuto(visible);
}

void DIA_Parametres::setMiseAJourAuto(bool enabled){
    param.setVerificationAutoMiseAJour(enabled);
    ui->lMiseAJour1->setEnabled(enabled);
    ui->sbNombreJourMiseAJour->setEnabled(enabled);
    ui->lMiseAJour2->setEnabled(enabled);
}

void DIA_Parametres::setNombreJourMiseAJour(int nombreJour){
    param.setNombreJourMiseAJour(nombreJour);
    if(nombreJour == 1) {
        ui->lMiseAJour2->setText("jour");
    } else {
        ui->lMiseAJour2->setText("jours");
    }
    qDebug() << "Mise a jour INI date prochaine Mise à jour";
    param.setProchaineVerificationMiseAJour(QDate::currentDate().addDays(nombreJour));
}
