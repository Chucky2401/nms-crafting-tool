#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
     * Définition des paramètres 'variable'
     * Un groupe pour la base de données
     * Un pour les images
     */
    settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "BlackWizard Company", "NMS Crafting Tool");
    imagePath = settings->value("img/path", settingDefaultString).toString();
    bddPath = settings->value("bdd/path", settingDefaultString).toString();
    bddName = settings->value("bdd/name", settingDefaultString).toString();
    farming = settings->value("utilisateur/farming", settingDefaultString).toString();
    autoExpand = settings->value("utilisateur/autoExpand", settingDefaultString).toString();

    if (imagePath == settingDefaultString){
        settings->setValue("img/path", "./img/");
        imagePath = "./img/";
    }

    if (bddPath == settingDefaultString){
        settings->setValue("bdd/path", "./bdd/");
        bddPath = "./bdd/";
    }

    if (bddName == settingDefaultString){
        settings->setValue("bdd/name", "nms_database-TEST.db");
        bddName = "nms_database-TEST.db";
    }

    if (farming == settingDefaultString){
        farming = "false";
    }

    if (farming == "true") {
        ui->cbFarming->setCheckState(Qt::Checked);
    } else {
        ui->cbFarming->setCheckState(Qt::Unchecked);
    }

    if (autoExpand == settingDefaultString){
        autoExpand = "false";
    }

    if (autoExpand == "true") {
        ui->cbAutoExpand->setCheckState(Qt::Checked);
    } else {
        ui->cbAutoExpand->setCheckState(Qt::Unchecked);
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    if (createConnection()){
        listeRecettes();
    }

    modele = new QStandardItemModel();

    connect(ui->qcbListeRecettes, SIGNAL(currentIndexChanged(int)), this, SLOT(recetteChoisis(int)));
    connect(ui->pbRecherche, SIGNAL(clicked()), this, SLOT(clickListerIngredients()));
    connect(ui->sbQuantite, SIGNAL(valueChanged(int)), this, SLOT(modifierQuantite(int)));
    connect(ui->cbFarming, SIGNAL(stateChanged(int)), this, SLOT(setFarming(int)));
    connect(ui->cbAutoExpand, SIGNAL(stateChanged(int)), this, SLOT(setAutoExpand(int)));
    connect(ui->aQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}

bool MainWindow::createConnection()
{
    db.setDatabaseName(bddPath+bddName);
    //db.setDatabaseName("./bdd/nms_database.db");
    if (!db.open()) {
        QSqlError error = db.lastError();
        QMessageBox::critical(this, "Connexion à la BDD", "Echec de la connexion à la Base de Données.\nDétails:\n"+error.text());
        return false;
    }
    return true;
}

void MainWindow::listeRecettes()
{
    QSqlQuery query;
    int recetteNiveau = 0;

    ui->qcbListeRecettes->addItem("*** Choisir une Recette ***", "NOTHING");
    if(query.exec("SELECT DISTINCT recette_nom_fr, recette_description_courte, recette_niveau, recette_icone FROM Recettes ORDER BY recette_niveau, recette_nom_fr")){
        while(query.next()){
            QString nomRecetteFr = query.value("recette_nom_fr").toString(), nomRecetteAffichage = "";
            int niveauRecette = query.value("recette_niveau").toInt();
            QString nomIcone = query.value("recette_icone").toString();
            QString descriptionCourte = query.value("recette_description_courte").toString();
            if (descriptionCourte != "") {
                nomRecetteAffichage = nomRecetteFr + " (" + query.value("recette_description_courte").toString() + ")";
            } else {
                nomRecetteAffichage = nomRecetteFr;
            }

            if (recetteNiveau != niveauRecette){
                recetteNiveau = niveauRecette;
                ui->qcbListeRecettes->addItem("--- Niveau "+QString::number(recetteNiveau)+" ---", "NOTHING");
            }


            ui->qcbListeRecettes->addItem(QIcon(imagePath+nomIcone), nomRecetteAffichage, nomRecetteFr);
        }
    }else{
        QMessageBox::critical(this, "Listing Recettes", "Erreur récupération des recettes.\nDétails:\n"+query.lastError().text());
    }
    ui->pbRecherche->setEnabled(false);
}

void MainWindow::recetteChoisis(int index){
    QSqlQuery query;
    QString recette = ui->qcbListeRecettes->currentData().toString();

    ui->qcbListeRecettes->setToolTip("");
    ui->teRecetteDescription->clear();
    ui->imageRecette->clear();

    if (recette == "NOTHING"){
        recetteSelectionne.clear();
        ui->pbRecherche->setEnabled(false);
    } else {
        recetteSelectionne.clear();
        recetteSelectionne.append(recette);
        ui->pbRecherche->setText("Lister Ingrédients");

        if(query.exec("SELECT DISTINCT recette_description, recette_icone FROM Recettes WHERE recette_nom_fr = \""+recette+"\"")){
            while(query.next()){
                QString nomIcone = query.value("recette_icone").toString();
                QString description = query.value("recette_description").toString();
                QPixmap image(imagePath+nomIcone);

                if (description == ""){
                    description = "<em>Pas de description</em>";
                }

                ui->teRecetteDescription->append(description);
                ui->imageRecette->setPixmap(image.scaled(100, 100));
                ui->qcbListeRecettes->setToolTip("<img src='"+imagePath+nomIcone+"' width='50' height='50' style=\"float:left;\"> <strong style=\"text-align:center;\">"+recette+"</strong> \
                                                <br /><br />"+description);
            }
        }
        ui->pbRecherche->setEnabled(true);
    }

}

/*
 * Fonction qui ne fait qu'appelé la fonction pour lister les ingrédients lors du clique sur le bouton
 */
void MainWindow::clickListerIngredients(){
    /*
     * On va d'abord chercher tous les éléments qui ont étais étendu par l'utilisateur
     * Si l'auto expand est off, cela ne sert à rien.
     */
    if (autoExpand == "false"){
        QModelIndex rootIndex = modele->index(0, 0);
        QVariant rootName = modele->data(rootIndex);
        itemExpanded.clear();

        if (rootName.toString() == recetteSelectionne){
            pourTout(modele);
        }
    }

    // On appel la fonction pour lister les ingrédients
    listerIngredients(recetteSelectionne);


}

/*
 * On liste les ingrédients dans la vue avec la hiérarchie
 */
void MainWindow::listerIngredients(QString recette){
    /*
     * On définis les variables
     */
    modele->clear();
    QStandardItem *rootNom = new QStandardItem(recette);
    QStandardItem *rootQuantite = new QStandardItem();
    QList<QStandardItem*> root;
    QStringList header;

    QSqlQuery query;
    QString sql = "", quantiteSql, nomIcone;

    QVector<QString> recettes, recettesTemp, ressourcesNom, ressourcesIcone, ressourcesID;
    QVector<int> niveaux, niveauxTemp, ressourcesQuantite;

    int niveau = 1, i = 0, sizeToRemove = 0, quantiteRecette = ui->sbQuantite->value();

    quantiteSql = QString::number(quantiteRecette);
    rootQuantite->setText(quantiteSql);

    /*
     * On va chercher le niveau et l'icone de la recette
     */
    query.exec("SELECT DISTINCT recette_niveau, recette_icone FROM Recettes WHERE recette_nom_fr =  \""+recette+"\"");
    while(query.next()){
        niveau = query.value("recette_niveau").toInt();
        nomIcone = query.value("recette_icone").toString();
    }

    // On ajoute la recette et le niveau dans deux QVector
    recettes.push_back(recette);
    niveaux.push_back(niveau);

    // On ajoute notre recette à notre modèle
    rootNom->setEditable(false);
    rootQuantite->setEditable(false);
    rootNom->setIcon(QIcon(imagePath+nomIcone));
    root << rootNom << rootQuantite;
    modele->appendRow(root);

    /*
     * Boucle Do/While pour rentrer au moins une fois, ce qui arrive même dans une boucle While
     * On boucle le niveau tant qu'il n'est pas égale à zéro.
     */
    do {
        /*
         *  On parcours sur le nombre d'éléments dans le QVector Recettes
         */
        for(i = 0; i < recettes.size(); i++){
            /*
             * On définis les variables
             * On définis aussi la requête à effectuer suivant le niveau de la recette
             */
            QString racine = recettes.at(i);
            QList<QStandardItem *> rootList;

            if (niveaux.at(i) > 1){
                sql = "SELECT DISTINCT \
                            r1.recette_nom_fr \
                          , r1.recette_niveau \
                          , r1.recette_quantitee_obtenue \
                          , r1.recette_quantitee_composant \
                          , r1.recette_icone \
                          , r2.recette_nom_fr Composant \
                          , r2.recette_niveau Niveau_composant \
                          , r2.recette_icone NomIcone \
                      FROM \
                          Recettes r1 \
                      LEFT JOIN Recettes r2 ON r2.id = r1.recette_composant_id \
                      WHERE \
                          r1.recette_nom_fr = \""+recettes.at(i)+"\"";
            } else {
                sql = "SELECT DISTINCT \
                      re.recette_nom_fr \
                    , re.recette_niveau \
                    , re.recette_quantitee_obtenue \
                    , re.recette_quantitee_composant \
                    , rl.ressources_nom_fr Composant \
                    , \"0\" Niveau_composant \
                    , rl.ressources_icone NomIcone \
                    , rl.id ID_Ressources \
                FROM \
                    Recettes re \
                LEFT JOIN Ressources_Listes rl ON rl.id = re.recette_composant_id \
                WHERE \
                    re.recette_nom_fr = \""+recettes.at(i)+"\"";
            }

            /*
             * On exécute la requête et on boucle sur les résultats
             */
            query.exec(sql);
            while(query.next()){
                /*
                 * Variables
                 */
                QStandardItem *composantNom = new QStandardItem();
                QStandardItem *composantQuantite = new QStandardItem();
                composantNom->setEditable(false);
                composantQuantite->setEditable(false);
                QString nomComposant = query.value("Composant").toString();
                int niveauComposant = query.value("Niveau_composant").toInt();
                QString iconeComposant = query.value("NomIcone").toString();

                // On va chercher le parents de notre futur entrée
                rootList = modele->findItems(racine, Qt::MatchRecursive);

                /*
                 * Si le composant n'est pas de niveau 0 on l'ajoute dans un tableau temporaire.
                 *  Cela car on va le mettre dans le tableau dans lequel on boucle  (for).
                 * Dans le sinon, on va chercher la quantité final, les ressources n'ayant pas le même ratio.
                 */
                if (niveauComposant != 0) {
                    recettesTemp.push_back(nomComposant);
                    niveauxTemp.push_back(niveauComposant);

                    composantNom->setText(nomComposant);
                    composantNom->setIcon(QIcon(imagePath+iconeComposant));
                    composantQuantite->setText(quantiteSql);
                } else {
                    /*
                     * Variables
                     */
                    QString quantite;
                    int intQuantite = 0;
                    double floatQuantite = 0.0;
                    int quantiteObtenu = query.value("recette_quantitee_obtenue").toInt();
                    int quantiteNecessaire = query.value("recette_quantitee_composant").toInt();

                    /*
                     * Suivant le resultat de la requête pour la quantite obtenue, le calcul diffère
                     */
                    if (quantiteObtenu > 1){
                        floatQuantite = static_cast<double>(quantiteRecette) / quantiteObtenu * static_cast<double>(quantiteNecessaire);
                    } else {
                        floatQuantite = quantiteObtenu * quantiteRecette * quantiteNecessaire;
                    }

                    /*
                     * On définis une quantite dans un entier
                     */
                    floatQuantite = ceil(floatQuantite);
                    intQuantite = static_cast<int>(floatQuantite);
                    quantite = QString::number(intQuantite);

                    /*
                     * Ici, on va chercher dans le QVector reesourcesNom, si le composant est présent.
                     *      Présent     : On ajoute la quantité obtenue à la précédente
                     *      Non-Présent : On ajoute dans le QVector
                     */
                    int positionVecteur = ressourcesNom.indexOf(nomComposant);
                    if (positionVecteur == -1) {
                        ressourcesNom.append(nomComposant);
                        ressourcesQuantite.append(intQuantite);
                        ressourcesIcone.append(iconeComposant);
                        ressourcesID.append(query.value("ID_Ressources").toString());
                    } else {
                        ressourcesQuantite[positionVecteur] = ressourcesQuantite[positionVecteur] + intQuantite;
                    }

                    composantNom->setText(nomComposant);
                    composantNom->setIcon(QIcon(imagePath+iconeComposant));
                    composantQuantite->setText(quantite);
                }
                // On ajoute nos résultats au parents
                QList<QStandardItem*> composant;
                composant << composantNom << composantQuantite;
                rootList.value(0)->appendRow(composant);

            }
        }

        /*
         * Ici on transfert les QVectors temporaire dans le principal (boucle for)
         * 3 étapes :
         *      1. On vide le principal (boucle for)
         *  Si la taille du temporaire est différente de zéro
         *      2. On copie chaque item du temporaire dans le principal
         *      3. On vide le temporaire
         * Si le temporaire fait 0, alors on définis niveau à zéro, on a finis.
         */
        sizeToRemove = recettes.size();
        for (i = 0; i < sizeToRemove; i++){
            recettes.remove(0);
            niveaux.remove(0);
        }

        if (recettesTemp.size() != 0) {
            for (i = 0; i < recettesTemp.size(); i++) {
                recettes.push_back(recettesTemp.at(i));
                niveaux.push_back(niveauxTemp.at(i));
            }

            sizeToRemove = recettesTemp.size();
            for (i = 0; i < sizeToRemove; i++) {
                recettesTemp.remove(0);
                niveauxTemp.remove(0);
            }

        } else {
            niveau = 0;
        }
    } while (niveau != 0);

    /*
     * Ici, on va traiter les ressources (matière première).
     * On commence par ajouter une ligne vierge ainsi qu'un "titre"
     */
    QStandardItem *ligneTotal = new QStandardItem("Total Matières Premières :");
    QStandardItem *vierge = new QStandardItem("");
    ligneTotal->setEditable(false);
    vierge->setEditable(false);
    modele->appendRow(vierge);
    modele->appendRow(ligneTotal);

    /*
     * On boucle sur le QVector ressourcesNom
     */
    for (i = 0; i < ressourcesNom.size(); i++){
        /*
         * Variables
         */
        QStandardItem *composantNom = new QStandardItem();
        QStandardItem *composantQuantite = new QStandardItem();
        QStandardItem *composantNombrePlants = new QStandardItem();
        QStandardItem *composantNombreDome = new QStandardItem();
        composantNom->setEditable(false);
        composantQuantite->setEditable(false);
        composantNombrePlants->setEditable(false);
        composantNombreDome->setEditable(false);
        QList<QStandardItem*> composant;

        if (farming == "true"){
            QString nomPlante = "";
            double nombrePlant, nombrePlantParDome = 13;
            int nombrePlantEntier, nombreDomeEntier, quantiteeParPlant = 0;

            // On récupère l'info sur le farming
            sql = "SELECT DISTINCT \
                          quantitee_par_plant \
                        , nom_plante \
                    FROM \
                          Ressources_Farm \
                    WHERE \
                        id_ressource = "+ressourcesID.at(i);

            query.exec(sql);
            while (query.next()) {
                nomPlante = query.value("nom_plante").toString();
                quantiteeParPlant = query.value("quantitee_par_plant").toInt();
            }
            // Quantite par plante sous forme d'entier
            if (quantiteeParPlant != 0){
                nombrePlant = ceil(ressourcesQuantite.at(i)/quantiteeParPlant);
                nombrePlantEntier = static_cast<int>(nombrePlant);
            } else {
                nombrePlantEntier = 0;
            }

            // Quantite de dome pour le nombre de plant
            nombreDomeEntier = static_cast<int>(ceil(nombrePlantEntier/nombrePlantParDome));

            composantNombrePlants->setText(QString::number(nombrePlantEntier));
            composantNombreDome->setText(QString::number(nombreDomeEntier));
            composantNom->setText(ressourcesNom.at(i)+" ("+nomPlante+")");
        } else {
            composantNom->setText(ressourcesNom.at(i));
        }
        // On définis nos Items
        composantNom->setIcon(QIcon(imagePath+ressourcesIcone.at(i)));
        composantQuantite->setText(QString::number(ressourcesQuantite.at(i)));

        // On ajoute dans le modele
        if (farming == "true"){
            composant << composantNom << composantQuantite << composantNombrePlants << composantNombreDome;
        } else {
            composant << composantNom << composantQuantite;
        }
        ligneTotal->appendRow(composant);
    }

    // On définis l'en-tête de la vue et lui définis son modèle
    if (farming == "true"){
        header << "Nom" << "Quantité" << "Nombre Plant" << "Nombre Dome";
    } else {
        header << "Nom" << "Quantité";
    }
    modele->setHorizontalHeaderLabels(header);
    ui->vue->setModel(modele);

    /*
     * Pour faire propre, on définis la taille mini
     * Mais comme on a des décalages, on force une taille mini à la première colonne.
     */
    int nombreColonne = modele->columnCount();
    for(int i = 0; i < nombreColonne; i++) {
        ui->vue->resizeColumnToContents(i);
    }
    ui->vue->setColumnWidth(0, 250);

    /*
     * Si on avait des items agrandis, alors on boucle sur cette liste. Pour :
     *      1. On recherche l'item par son nom
     *      2. On récupère son idex
     *      3. S'il n'est pas vide, on l'agrandi.
     */
    if (itemExpanded.count() != 0 && autoExpand == "false"){
        QList<QStandardItem *> rootList;
        for (int item = 0; item < itemExpanded.count(); item++){
            rootList = modele->findItems(itemExpanded.at(item), Qt::MatchRecursive);
            //QModelIndexList Items = modele->match(modele->index(0, 0), Qt::DisplayRole, QVariant::fromValue(itemExpanded.at(item)));
            QModelIndexList Items = modele->match(modele->indexFromItem(rootList.first()), Qt::DisplayRole, QVariant::fromValue(itemExpanded.at(item)));
            if (!Items.isEmpty())
                ui->vue->setExpanded(Items.first(), true);
        }
    } else if (autoExpand == "true") {
        ui->vue->expandAll();
    }

}

/*
 * Fonction qui met le texte du bouton à 'Actualiser' si on change la quantité et qu'il y a des items dans le modele
 */
void MainWindow::modifierQuantite(int valeur){
    if (recetteSelectionne != "" && modele->hasChildren()){
        ui->pbRecherche->setText("Actualiser");
    }
}

/*
 * Fonction pour la case à cocher si on veut les données de farming (Plant + Dome) ou pas.
 */
void MainWindow::setFarming(int state){
    if (state == 0){
        //unchecked
        settings->setValue("utilisateur/farming", "false");
        farming = "false";
    } else if (state == 2) {
        //checked
        settings->setValue("utilisateur/farming", "true");
        farming = "true";
    }
}


/*
 * Fonction pour la case à cocher si on veut l'étendu automatique ou pas.
 */
void MainWindow::setAutoExpand(int state){
    if (state == 0){
        //unchecked
        settings->setValue("utilisateur/autoExpand", "false");
        autoExpand = "false";
    } else if (state == 2) {
        //checked
        settings->setValue("utilisateur/autoExpand", "true");
        autoExpand = "true";
    }
}

/*
 * Fonction qui parcours tout le modele de la vue pour trouver les objets agrandis
 */
void MainWindow::pourTout(QAbstractItemModel* modele, QModelIndex parent){
    for(int r = 0; r < modele->rowCount(parent); ++r) {
        QModelIndex index = modele->index(r, 0, parent);
        QVariant name = modele->data(index);

        if (ui->vue->isExpanded(index)){
            itemExpanded << index.data(Qt::DisplayRole).toString();
        }

        // Si l'item a des enfants, on rappel la même fonction pour boucler.
        if(modele->hasChildren(index) ) {
            pourTout(modele, index);
        }
    }
}
