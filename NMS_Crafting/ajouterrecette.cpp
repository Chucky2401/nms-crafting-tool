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

    ui->lRecetteExiste->setVisible(false);
    ui->pbValiderComposant->setEnabled(false);

    ui->cbComposant1->addItem(" Choisir le type                                                                 ↑↑↑", defaultString);
    ui->cbComposant2->addItem(" Choisir le type                                                                 ↑↑↑", defaultString);
    ui->cbComposant3->addItem(" Choisir le type                                                                 ↑↑↑", defaultString);
    ui->cbComposant1->setEditable(false);
    ui->cbComposant2->setEditable(false);
    ui->cbComposant3->setEditable(false);

    connect(ui->pbSelectImage, SIGNAL(clicked()), this, SLOT(chooseImage()));
    connect(ui->leTitre, SIGNAL(textEdited(QString)), this, SLOT(titreEdited(QString)));
    connect(ui->leSousTitre, SIGNAL(textEdited(QString)), this, SLOT(sousTitreEdited(QString)));
    connect(ui->leTitre, SIGNAL(editingFinished()), this, SLOT(verifierTitreSousTitre()));
    connect(ui->leSousTitre, SIGNAL(editingFinished()), this, SLOT(verifierTitreSousTitre()));
    connect(ui->pbValiderComposant, SIGNAL(clicked()), this, SLOT(cliqueSurValider()));

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
    QString titre = ui->leTitre->text();
    QString descriptionCourte = ui->leSousTitre->text();
    QString composant1 = ui->cbComposant1->currentData().toString();
    QString composant2 = ui->cbComposant2->currentData().toString();
    QString composant3 = ui->cbComposant3->currentData().toString();

    if ((titre != "" || descriptionCourte != "" || composant1 != defaultString || composant2 != defaultString || composant3 != defaultString) && !sauvegardeReussi){
        if (QMessageBox::warning(this, "Annuler l'ajout", "Voulez-vous fermer la fenêtre ?\nAttention ! Toutes vos modifications seront perdues !", QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes){
            if (bdd.isOpen(connectionName))
                bdd.closeConnection(connectionName);
            emit finished(0);
            event->accept();
        } else {
            event->ignore();
        }
    } else {
        if (bdd.isOpen(connectionName))
            bdd.closeConnection(connectionName);
        emit finished(0);
        event->accept();
    }
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

void ajouterRecette::verifierTitreSousTitre(){
    QString titre = ui->leTitre->text();
    QString sousTitre = ui->leSousTitre->text();
    QString sql;
    QSqlQuery query(bdd.getBase());
    int nbrRecetteEnBase = 0;

    if (!titre.isEmpty()){

        sql = "SELECT \
                COUNT(1) AS NbrRecette \
                FROM \
                Recettes \
                WHERE \
                recette_nom_fr = ? \
                    AND recette_description_courte = ?";

                                                      query.prepare(sql);
        query.bindValue(0, titre);
        query.bindValue(1, sousTitre);
        if (query.exec()){
            while(query.next()){
                nbrRecetteEnBase = query.value("NbrRecette").toInt();
            }
            if(nbrRecetteEnBase > 0){
                ui->lRecetteExiste->setText("La recette existe déjà. Modifié le titre ou le sous-titre.");
                ui->lRecetteExiste->setStyleSheet("QLabel {color: red;}");
                ui->lRecetteExiste->setVisible(true);
                ui->pbValiderComposant->setEnabled(false);
            } else {
                ui->lRecetteExiste->setVisible(false);
                ui->pbValiderComposant->setEnabled(true);
            }
        }
    } else {
        ui->pbValiderComposant->setEnabled(false);
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

    switch (meComposant.keyToValue(valeurCombo.toLatin1())) {
    case COMPOSANT1:
        ui->cbComposant1->setEditable(true);
        break;
    case COMPOSANT2:
        ui->cbComposant2->setEditable(true);
        break;
    case COMPOSANT3:
        ui->cbComposant3->setEditable(true);
        break;
    }


    switch (meType.keyToValue(valeurComposant.toLatin1())) {
        case RESSOURCE:{
            //TODO
            sql = "SELECT id, ressources_nom_fr, ressources_icone FROM Ressources_Listes";
            if (query.exec(sql)){
                while(query.next()){
                    typeEtId.clear();
                    typeEtId << "RESSOURCE";
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
                            typeEtId.clear();
                            typeEtId << "RECETTE";
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
        AND recette_description_courte = \""+descriptionCourte+"\" \
        ORDER BY \
            id ASC";

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
        listerComposants("Recette", "Composant2");
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
        listerComposants("Recette", "Composant3");
    }
}

void ajouterRecette::cliqueSurValider(){
    const QString sqlRecette = "SELECT recette_niveau FROM Recettes WHERE id IN (:ids) ORDER BY id ASC";
    /*const QString sqlRecetteInsert = "INSERT INTO Recettes_Test_INSERT \
    (recette_nom_fr, recette_description_courte, recette_description, recette_niveau, recette_composant_id, recette_quantitee_composant, \
    recette_quantitee_obtenue, recette_icone) \
    VALUES(:nom, :descriptionCourte, :description, :niveau, :idComposant, :qteComposant, :qteObtenu, :icone)";*/
    const QString sqlRecetteInsert = "INSERT INTO Recettes \
    (recette_nom_fr, recette_description_courte, recette_description, recette_niveau, recette_composant_id, recette_quantitee_composant, \
    recette_quantitee_obtenue, recette_icone) \
    VALUES(:nom, :descriptionCourte, :description, :niveau, :idComposant, :qteComposant, :qteObtenu, :icone)";

    QString titre = ui->leTitre->text();
    QString descriptionCourte = ui->leSousTitre->text();
    QString description = ui->teDescription->toPlainText();
    QString cheminImage = ui->leFilePath->text();
    int quantiteObtenue = ui->sbQteObtenu->value();
    QList<QVariant> composant1 = ui->cbComposant1->currentData().toList();
    QList<QVariant> composant2 = ui->cbComposant2->currentData().toList();
    QList<QVariant> composant3 = ui->cbComposant3->currentData().toList();
    int quantiteComposant1 = ui->sbQteComposant1->value();
    int quantiteComposant2 = ui->sbQteComposant2->value();
    int quantiteComposant3 = ui->sbQteComposant3->value();

    bdd.startTransaction();
    bool erreurInsert = false, composantDefinis = false;

    QList<int> intIdsComposant1, intIdsComposant2, intIdsComposant3;
    QList<int> intNiveauxComposant1, intNiveauxComposant2, intNiveauxComposant3;
    QString typeComposant1, typeComposant2, typeComposant3;
    QString sqlIdsComposant1 = "", sqlIdsComposant2 = "", sqlIdsComposant3 = "";
    QString sqlComposant1, sqlComposant2, sqlComposant3;
    QSqlQuery queryComposant1(bdd.getBase()), queryComposant2(bdd.getBase()), queryComposant3(bdd.getBase());

    QString tempSql, sqlInsertRecette, derniereErreur;
    QList<QString> sqlInsertsRecette;
    QSqlQuery queryInsertRecette(bdd.getBase());

    titre.replace("'", "''");
    descriptionCourte.replace("'", "''");
    description.replace("'", "''");

    //qDebug() << "=============================================";
    //qDebug() << "Titre                : " << titre;
    //qDebug() << "Description courte   : " << descriptionCourte;
    //qDebug() << "Description          : " << description;
    //qDebug() << "Chemin image         : " << cheminImage;
    //qDebug() << "Quanite Obtenue      : " << quantiteObtenue;
    //qDebug() << "Composant 1          : " << composant1;
    //qDebug() << "    Quantitee        : " << quantiteComposant1;
    //qDebug() << "Composant 2          : " << composant2;
    //qDebug() << "    Quantitee        : " << quantiteComposant2;
    //qDebug() << "Composant 3          : " << composant3;
    //qDebug() << "    Quantitee        : " << quantiteComposant3;
    qDebug() << "-----";

    if(composant1.count() > 1){
        composantDefinis = true;
        typeComposant1 = composant1.at(0).toString();
        composant1.removeFirst();
        for (int i = 0; i < composant1.size(); ++i) {
            int identifiant = composant1.at(i).toInt();
            if (i != composant1.size()-1){
                sqlIdsComposant1 += QString::number(identifiant) + ", ";
            } else {
                sqlIdsComposant1 += QString::number(identifiant);
            }
            intIdsComposant1 << identifiant;
            if(typeComposant1 == "RESSOURCE"){
                intNiveauxComposant1 << 1;
            }
        }

        if(typeComposant1 == "RECETTE"){
            sqlComposant1 = sqlRecette;
            sqlComposant1.replace(":ids", sqlIdsComposant1);
            queryComposant1.prepare(sqlComposant1);
            if(queryComposant1.exec()){
                while(queryComposant1.next()){
                    int niveau = queryComposant1.value("recette_niveau").toInt();
                    intNiveauxComposant1 << niveau+1;
                }
            } else {
                QMessageBox::critical(this, "Error", queryComposant1.lastError().text());
            }
        }

        //qDebug() << "sqlRecette           : " << sqlRecette;
        //qDebug() << "sqlComposant1        : " << sqlComposant1;
        //qDebug() << "sqlIdsComposant1     : " << sqlIdsComposant1;
        //qDebug() << "intIdsComposant1     : " << intIdsComposant1;
        //qDebug() << "intNiveauxComposant1 : " << intNiveauxComposant1;
        //qDebug() << "-----";

        if ((intIdsComposant1.size() != 0 && intNiveauxComposant1.size() != 0) && intIdsComposant1.size() == intNiveauxComposant1.size()){
            for (int i = 0; i < intIdsComposant1.size(); i++){
                tempSql.clear();
                tempSql = sqlRecetteInsert;
                tempSql.replace(":nom", "'"+titre+"'");
                tempSql.replace(":descriptionCourte", "'"+descriptionCourte+"'");
                tempSql.replace(":description", "'"+description+"'");
                tempSql.replace(":niveau", QString::number(intNiveauxComposant1.at(i)));
                tempSql.replace(":idComposant", QString::number(intIdsComposant1.at(i)));
                tempSql.replace(":qteComposant", QString::number(quantiteComposant1));
                tempSql.replace(":qteObtenu", QString::number(quantiteObtenue));
                tempSql.replace(":icone", "'"+cheminImage.replace("./img/", "")+"'");

                sqlInsertsRecette << tempSql;
            }
        }
    }

    if(composant2.count() > 1){
        composantDefinis = true;
        typeComposant2 = composant2.at(0).toString();
        composant2.removeFirst();
        for (int i = 0; i < composant2.size(); ++i) {
            int identifiant = composant2.at(i).toInt();
            if (i != composant2.size()-1){
                sqlIdsComposant2 += QString::number(identifiant) + ", ";
            } else {
                sqlIdsComposant2 += QString::number(identifiant);
            }
            intIdsComposant2 << identifiant;
            if(typeComposant2 == "RESSOURCE"){
                intNiveauxComposant2 << 1;
            }
        }

        if(typeComposant2 == "RECETTE"){
            sqlComposant2 = sqlRecette;
            sqlComposant2.replace(":ids", sqlIdsComposant2);
            queryComposant2.prepare(sqlComposant2);
            if(queryComposant2.exec()){
                while(queryComposant2.next()){
                    int niveau = queryComposant2.value("recette_niveau").toInt();
                    intNiveauxComposant2 << niveau+1;
                }
            } else {
                QMessageBox::critical(this, "Error", queryComposant2.lastError().text());
            }
        }

        //qDebug() << "sqlRecette           : " << sqlRecette;
        //qDebug() << "sqlComposant2        : " << sqlComposant2;
        //qDebug() << "sqlIdsComposant2     : " << sqlIdsComposant2;
        //qDebug() << "intIdsComposant2     : " << intIdsComposant2;
        //qDebug() << "intNiveauxComposant2 : " << intNiveauxComposant2;
        //qDebug() << "-----";

        if ((intIdsComposant2.size() != 0 && intNiveauxComposant2.size() != 0) && intIdsComposant2.size() == intNiveauxComposant2.size()){
            for (int i = 0; i < intIdsComposant2.size(); i++){
                tempSql.clear();
                tempSql = sqlRecetteInsert;
                tempSql.replace(":nom", "'"+titre+"'");
                tempSql.replace(":descriptionCourte", "'"+descriptionCourte+"'");
                tempSql.replace(":description", "'"+description+"'");
                tempSql.replace(":niveau", QString::number(intNiveauxComposant2.at(i)));
                tempSql.replace(":idComposant", QString::number(intIdsComposant2.at(i)));
                tempSql.replace(":qteComposant", QString::number(quantiteComposant2));
                tempSql.replace(":qteObtenu", QString::number(quantiteObtenue));
                tempSql.replace(":icone", "'"+cheminImage.replace("./img/", "")+"'");

                sqlInsertsRecette << tempSql;
            }
        }
    }

    if(composant3.count() > 1){
        composantDefinis = true;
        typeComposant3 = composant3.at(0).toString();
        composant3.removeFirst();
        for (int i = 0; i < composant3.size(); ++i) {
            int identifiant = composant3.at(i).toInt();
            if (i != composant3.size()-1){
                sqlIdsComposant3 += QString::number(identifiant) + ", ";
            } else {
                sqlIdsComposant3 += QString::number(identifiant);
            }
            intIdsComposant3 << identifiant;
            if(typeComposant3 == "RESSOURCE"){
                intNiveauxComposant3 << 1;
            }
        }

        if(typeComposant3 == "RECETTE"){
            sqlComposant3 = sqlRecette;
            sqlComposant3.replace(":ids", sqlIdsComposant3);
            queryComposant3.prepare(sqlComposant3);
            if(queryComposant3.exec()){
                while(queryComposant3.next()){
                    int niveau = queryComposant3.value("recette_niveau").toInt();
                    intNiveauxComposant3 << niveau+1;
                }
            } else {
                QMessageBox::critical(this, "Error", queryComposant3.lastError().text());
            }
        }

        //qDebug() << "sqlRecette           : " << sqlRecette;
        //qDebug() << "sqlComposant3        : " << sqlComposant3;
        //qDebug() << "sqlIdsComposant3     : " << sqlIdsComposant3;
        //qDebug() << "intIdsComposant3     : " << intIdsComposant3;
        //qDebug() << "intNiveauxComposant3 : " << intNiveauxComposant3;
        //qDebug() << "-----";

        if ((intIdsComposant3.size() != 0 && intNiveauxComposant3.size() != 0) && intIdsComposant3.size() == intNiveauxComposant3.size()){
            for (int i = 0; i < intIdsComposant3.size(); i++){
                tempSql.clear();
                tempSql = sqlRecetteInsert;
                tempSql.replace(":nom", "'"+titre+"'");
                //tempSql.replace(":nom", titre);
                tempSql.replace(":descriptionCourte", "'"+descriptionCourte+"'");
                tempSql.replace(":description", "'"+description+"'");
                tempSql.replace(":niveau", QString::number(intNiveauxComposant3.at(i)));
                tempSql.replace(":idComposant", QString::number(intIdsComposant3.at(i)));
                tempSql.replace(":qteComposant", QString::number(quantiteComposant3));
                tempSql.replace(":qteObtenu", QString::number(quantiteObtenue));
                tempSql.replace(":icone", "'"+cheminImage.replace("./img/", "")+"'");

                sqlInsertsRecette << tempSql;
            }
        }
    }

    qDebug() << "sqlInsertsRecette     : " << sqlInsertsRecette;
    qDebug() << "-----";

    if (sqlInsertsRecette.size() != 0 && composantDefinis){
        for (int i = 0; i < sqlInsertsRecette.size(); i++){
            if(!erreurInsert){
                sqlInsertRecette.clear();
                sqlInsertRecette = sqlInsertsRecette.at(i);

                if(queryInsertRecette.exec(sqlInsertRecette)){
                    qDebug() << "Insert " << i << "              : Réussie !";
                } else {
                    qDebug() << "Insert " << i << "              : Echoue !!";
                    qDebug() << "Erreur                : " << queryInsertRecette.lastError().text();
                    derniereErreur = queryInsertRecette.lastError().text();
                    erreurInsert = true;
                }
            }
        }
    }

    if(erreurInsert){
        bdd.stopTransaction(true);
        QMessageBox::critical(this, "Erreur", "Une erreur est survenu lors de la création de la recette.\nErreur : " + derniereErreur);
    } else if(!composantDefinis) {
        bdd.stopTransaction(true);
        QMessageBox::critical(this, "Aucun composant", "Vous n'avez définis aucun composant pour la recette !");
    } else if(sqlInsertsRecette.size() == 0) {
        bdd.stopTransaction(true);
        QMessageBox::critical(this, "Erreur", "Une erreur est survenu lors de la sauvegarde de la nouvelle recette.\nErreur : Génération list inserts.");
    } else {
        bdd.stopTransaction(false);
        sauvegardeReussi = true;
        QMessageBox::information(this, "Recette ajouté", "La recette a été ajoutée !");
        this->close();
    }
}
