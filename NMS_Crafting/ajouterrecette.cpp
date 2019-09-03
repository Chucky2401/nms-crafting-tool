#include "ajouterrecette.h"
#include "ui_ajouterrecette.h"

ajouterRecette::ajouterRecette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterRecette)
{
    ui->setupUi(this);

    bool test = bdd.createConnection(connectionName);
    if(!test){
        QString lastBddError = bdd.getError();
        QMessageBox::critical(this, "Connexion à la BDD", "Echec de la connexion à la Base de Données.\nDétails:\n"+bdd.getError());
    }

    connect(ui->pbSelectImage, SIGNAL(clicked()), this, SLOT(chooseImage()));
    connect(ui->leTitre, SIGNAL(textEdited(QString)), this, SLOT(titreEdited(QString)));
    connect(ui->leSousTitre, SIGNAL(textEdited(QString)), this, SLOT(sousTitreEdited(QString)));
    connect(ui->rbComposant1Ressources, SIGNAL(toggled(bool)), this, SLOT(listerRessourcesComposant1(bool)));
    connect(ui->rbComposant1Recettes, SIGNAL(toggled(bool)), this, SLOT(listerRecettesComposant1(bool)));
    connect(ui->rbComposant2Ressources, SIGNAL(toggled(bool)), this, SLOT(listerRessourcesComposant2(bool)));
    connect(ui->rbComposant2Recettes, SIGNAL(toggled(bool)), this, SLOT(listerRecettesComposant2(bool)));
    connect(ui->rbComposant3Ressources, SIGNAL(toggled(bool)), this, SLOT(listerRessourcesComposant3(bool)));
    connect(ui->rbComposant3Recettes, SIGNAL(toggled(bool)), this, SLOT(listerRecettesComposant3(bool)));

    ui->tabWidget->setCurrentIndex(0);
}

ajouterRecette::~ajouterRecette()
{
    if (bdd.isOpen(connectionName))
        bdd.closeConnection(connectionName);
    delete ui;
}

void ajouterRecette::closeEvent(QCloseEvent *event){
//    if (QMessageBox::question(this, "Fermeture", "Voulez-vous fermer le programme ?") == QMessageBox::Yes){
        if (bdd.isOpen(connectionName))
            bdd.closeConnection(connectionName);
        emit finished(0);
        event->accept();
//    } else {
//        event->ignore();
//    }
}

void ajouterRecette::titreEdited(QString titre){
    int intNbCaractere = titre.length();
    QString nbCaractere = QString::number(intNbCaractere);
    ui->lNbCaractereTitre->setText(nbCaractere+"/50");

    if (intNbCaractere < 45) {
        ui->lNbCaractereTitre->setStyleSheet("QLabel {color: black;}");

    } else if (intNbCaractere >= 45 && intNbCaractere != 50) {
        ui->lNbCaractereTitre->setStyleSheet("QLabel {color: gold;}");

    } else {
        ui->lNbCaractereTitre->setStyleSheet("QLabel {color: red;}");
    }
}

void ajouterRecette::sousTitreEdited(QString sousTitre){
    int intNbCaractere = sousTitre.length();
    QString nbCaractere = QString::number(intNbCaractere);
    ui->lNbCarSousTitre->setText(nbCaractere+"/50");

    if (intNbCaractere < 45) {
        ui->lNbCarSousTitre->setStyleSheet("QLabel {color: black;}");

    } else if (intNbCaractere >= 45 && intNbCaractere != 50) {
        ui->lNbCarSousTitre->setStyleSheet("QLabel {color: gold;}");

    } else {
        ui->lNbCarSousTitre->setStyleSheet("QLabel {color: red;}");
    }
}

void ajouterRecette::chooseImage(){
//    qDebug() << QDir::currentPath();
    fileDialog = new QFileDialog(this, "Choisir une image", param.getImagePath(), tr("Fichier PNG (*.png)"));
    fileNameComplete = fileDialog->getOpenFileName(this);
    if (!fileNameComplete.contains(QDir::currentPath())){
        QStringList list = fileNameComplete.split('/');
        QString fileName = list.at(list.count()-1);
        QFile::copy(fileNameComplete, param.getImagePath()+fileName);
        fileNameComplete = "./img/"+fileName;
        QMessageBox::information(this, "Fichier Copié", "L'image a été copié dans le répertoire du programme");
    }

    fileNameComplete.replace(QDir::currentPath(), ".");
    QPixmap image(fileNameComplete);
    ui->imageRecette->setPixmap(image.scaled(100, 100));

    ui->leFilePath->setText(fileNameComplete);
//    qDebug() << QDir::currentPath();
}

void ajouterRecette::listerComposants(QString typeComposant, QString combo){
    QMetaObject moType = this->staticMetaObject;
    QMetaEnum meType = moType.enumerator(moType.indexOfEnumerator("eTypeComposant"));
    QMetaObject moComposant = this->staticMetaObject;
    QMetaEnum meComposant = moComposant.enumerator(moComposant.indexOfEnumerator("eCombo"));
    QString valeurComposant = typeComposant.toUpper(), valeurCombo = combo.toUpper();

    QList<QVariant> typeEtId;

    QString sql, sql2;
    QSqlQuery query(bdd.getBase()), query2(bdd.getBase());

    switch (meType.keyToValue(valeurComposant.toLatin1())) {
        case RESSOURCE:{
            //TODO
            typeEtId << "RESSOURCE";
            sql = "SELECT id, ressources_nom_fr, ressources_icone FROM Ressources_Listes";
            if (query.exec(sql)){
                while(query.next()){
                    QString nomRessource = query.value("ressources_nom_fr").toString();
                    int idRessource = query.value("id").toInt();
                    typeEtId << idRessource;
                    QString nomIcone = query.value("ressources_icone").toString();
                    switch (meComposant.keyToValue(valeurCombo.toLatin1())) {
                    case COMPOSANT1:
                        ui->cbComposant1->addItem(QIcon(param.getImagePath()+nomIcone), nomRessource, typeEtId);
                        break;
                    case COMPOSANT2:
                        ui->cbComposant2->addItem(QIcon(param.getImagePath()+nomIcone), nomRessource, typeEtId);
                        break;
                    case COMPOSANT3:
                        ui->cbComposant3->addItem(QIcon(param.getImagePath()+nomIcone), nomRessource, typeEtId);
                        break;
                    }
                }
            }
        }
        break;

        case RECETTE:{
            //TODO
            int recetteNiveau = 0;

            typeEtId << "RECETTE";
            sql = "SELECT DISTINCT recette_nom_fr, recette_niveau, recette_icone FROM Recettes GROUP BY recette_nom_fr ORDER BY recette_niveau, recette_nom_fr";
            if (query.exec(sql)){
                while(query.next()){
                    QString nomRecetteFr = query.value("recette_nom_fr").toString(), nomRecetteAffichage = "";
                    int niveauRecette = query.value("recette_niveau").toInt();
                    QString nomIcone = query.value("recette_icone").toString();

                    if (recetteNiveau != niveauRecette){
                        recetteNiveau = niveauRecette;
                        switch (meComposant.keyToValue(valeurCombo.toLatin1())) {
                        case COMPOSANT1:
                            ui->cbComposant1->addItem("--- Niveau "+QString::number(recetteNiveau)+" ---", defaultString);
                            break;
                        case COMPOSANT2:
                            ui->cbComposant2->addItem("--- Niveau "+QString::number(recetteNiveau)+" ---", defaultString);
                            break;
                        case COMPOSANT3:
                            ui->cbComposant3->addItem("--- Niveau "+QString::number(recetteNiveau)+" ---", defaultString);
                            break;
                        }
                        //ui->qcbListeRecettes->addItem("--- Niveau "+QString::number(recetteNiveau)+" ---", "NOTHING");
                    }

                    sql2 = "SELECT DISTINCT recette_description_courte FROM Recettes WHERE recette_nom_fr = \""+nomRecetteFr+"\" ORDER BY recette_description_courte ASC";
                    if(query2.exec(sql2)){
                        while(query2.next()){
                            QString descriptionCourte = query2.value("recette_description_courte").toString();

                            if (descriptionCourte != "") {
                                nomRecetteAffichage = nomRecetteFr + " (" + descriptionCourte + ")";
                            } else {
                                nomRecetteAffichage = nomRecetteFr;
                            }
                            QList<QVariant> listeId = listeIdRecette(nomRecetteFr, descriptionCourte);
                            typeEtId << listeId;
                            switch (meComposant.keyToValue(valeurCombo.toLatin1())) {
                            case COMPOSANT1:
                                ui->cbComposant1->addItem(QIcon(param.getImagePath()+nomIcone), nomRecetteAffichage, typeEtId);
                                break;
                            case COMPOSANT2:
                                ui->cbComposant2->addItem(QIcon(param.getImagePath()+nomIcone), nomRecetteAffichage, typeEtId);
                                break;
                            case COMPOSANT3:
                                ui->cbComposant3->addItem(QIcon(param.getImagePath()+nomIcone), nomRecetteAffichage, typeEtId);
                                break;
                            }
                        }
                    }
                }
            }
        }
        break;

        default:
            //TODO
            break;
    }
}

QList<QVariant> ajouterRecette::listeIdRecette(QString nomComposant, QString descriptionCourte){
    QList<QVariant> idsRecette;
    QString sql;
    QSqlQuery query(bdd.getBase());

    sql = "SELECT \
            id \
        FROM \
            Recettes \
        WHERE \
            recette_nom_fr = \""+nomComposant+"\" \
        AND recette_description_courte = \""+descriptionCourte+"\"";

    if (query.exec(sql)){
        while(query.next()){
            int id = query.value("id").toInt();
            idsRecette << id;
        }
    }
    //TODO
    return idsRecette;
}

void ajouterRecette::listerRessourcesComposant1(bool checked){
    if(checked) {
        ui->cbComposant1->clear();
        ui->cbComposant1->addItem("*** Choisir Ressources ***", defaultString);
        listerComposants("Ressource", "Composant1");
    }
}

void ajouterRecette::listerRecettesComposant1(bool checked){
    if(checked){
        ui->cbComposant1->clear();
        ui->cbComposant1->addItem("***  Choisir Recettes  ***", defaultString);
        listerComposants("Recette", "Composant1");
    }
}

void ajouterRecette::listerRessourcesComposant2(bool checked){
    if(checked) {
        ui->cbComposant2->clear();
        ui->cbComposant2->addItem("*** Choisir Ressources ***", defaultString);
        listerComposants("Ressource", "Composant2");
    }
}

void ajouterRecette::listerRecettesComposant2(bool checked){
    if(checked){
        ui->cbComposant2->clear();
        ui->cbComposant2->addItem("***  Choisir Recettes  ***", defaultString);
    }
}

void ajouterRecette::listerRessourcesComposant3(bool checked){
    if(checked) {
        ui->cbComposant3->clear();
        ui->cbComposant3->addItem("*** Choisir Ressources ***", defaultString);
        listerComposants("Ressource", "Composant3");
    }
}

void ajouterRecette::listerRecettesComposant3(bool checked){
    if(checked){
        ui->cbComposant3->clear();
        ui->cbComposant3->addItem("***  Choisir Recettes  ***", defaultString);
    }
}
