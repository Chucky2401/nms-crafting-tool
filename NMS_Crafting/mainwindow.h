#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <cmath>

#include <QMainWindow>
#include <QMessageBox>

#include <QString>
#include <QList>

#include <QStandardItemModel>
#include <QModelIndex>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QIcon>

#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtXml>
#include <QProcess>

#include <QDebug>

#include "settings.h"
#include "database.h"
#include "ajouterrecette.h"
#include "dia_apropos.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr, bool m_test = false);
        ~MainWindow();

    protected:
        void closeEvent(QCloseEvent *event);

    private:
        // Constantes
        const QVariant settingDefaultString = "DNE";
        const QString defaultString = "NOTHING";
        const QVariant settingDefaultInt = -1;
        const QString connectionName = "principal";
        // GUI
        Ui::MainWindow *ui;
        // Divers
        bool m_test;
        // Classe complèmentaire
        class settings param;
        class database bdd;
        // Fenêtres complémentaires
        ajouterRecette *fenAjouterRecette;
        DIA_apropos *diaAPropos;
        bool fenAjouterRecetteOuverte;
        bool ouvertureEnCours;
        // Recettes
        QSqlDatabase db;
        QList<QVariant> recetteSelectionne;
        QStandardItemModel *modele;
        QGraphicsPixmapItem itemImageRecette;
        QGraphicsScene imageRecette;
        bool viewWasExtended;
        QStringList itemExpanded;
        // Mise à jour
        QNetworkAccessManager *m_qnamManager;
        QByteArray m_qbaDonneesTelechargees;
        // Fonctions
        bool createConnection();
        void listeRecettes();
        void listerIngredients(QList<QVariant> recette);
        bool getEtatFenAjouterRecette();
        void setEtatFenAjouterRecette(bool stated);
        void parcourirToutLeModele(QAbstractItemModel* modele, QModelIndex parent = QModelIndex());
        void restaurerDerniereRecette();

    signals:
        void downloaded(bool ecrireFichierUpdate);
        void fermeture();

    public slots:

    private slots:
        // Recette et quantités
        void recetteChoisis(int index);
        void modifierQuantite(int valeur);
        void clickListerIngredients();
        // Options
        void setFarmingFromButton(int state);
        void setFarmingFromMenu(bool state);
        void setAutoExpandFromButton(int state);
        void setAutoExpandFromMenu(bool state);
        void setRestoreRecipeFromMenu(bool state);
        void setRestoreSizePosFromMenu(bool state);
        // Fenêtre complémentaires
        void ouvrirFenAjouterRecette();
        void fenAjouterRecetteClose(int result);
        void ouvrirAPropos();
        // Mise à jour
        void verifierMiseAJour();
        void fichierTelecharge(QNetworkReply* pReply);
        void comparaisonVersion(bool ecrireFichier);
        // TEST
        void fonctionPourTest();
};

#endif // MAINWINDOW_H
