#include "ajouterrecette.h"
#include "ui_ajouterrecette.h"

//#include "mainwindow.h"

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
