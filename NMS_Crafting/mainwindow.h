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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, bool m_test = false);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void downloaded(bool ecrireFichierUpdate);
    void fermeture();

public slots:
    void clickListerIngredients();
    void recetteChoisis(int index);
    void modifierQuantite(int valeur);
    void setFarmingFromButton(int state);
    void setFarmingFromMenu(bool state);
    void setAutoExpandFromButton(int state);
    void setAutoExpandFromMenu(bool state);
    void setRestoreRecipeFromMenu(bool state);
    void setRestoreSizePosFromMenu(bool state);

    void ouvrirFenAjouterRecette();
    void fenAjouterRecetteClose(int result);

    void ouvrirAPropos();

    void verifierMiseAJour();

private slots:
    void fichierTelecharge(QNetworkReply* pReply);
    void comparaisonVersion(bool ecrireFichier);

    void fonctionPourTest();


private:
    const QVariant settingDefaultString = "DNE";
    const QString defaultString = "NOTHING";
    const QVariant settingDefaultInt = -1;
    const QString connectionName = "principal";

    bool m_test;
    ajouterRecette *fenAjouterRecette;
    bool fenAjouterRecetteOuverte;
    bool ouvertureEnCours;
    DIA_apropos *diaAPropos;

    Ui::MainWindow *ui;
    QSqlDatabase db;
    QList<QVariant> recetteSelectionne;
    QStandardItemModel *modele;
    QGraphicsPixmapItem itemImageRecette;
    QGraphicsScene imageRecette;
    bool viewWasExtended;
    QStringList itemExpanded;

    QNetworkAccessManager *m_qnamManager;
    QByteArray m_qbaDonneesTelechargees;

    class settings param;
    class database bdd;

    bool createConnection();
    void listeRecettes();
    void listerIngredients(QList<QVariant> recette);
    void parcourirToutLeModele(QAbstractItemModel* modele, QModelIndex parent = QModelIndex());
    bool getEtatFenAjouterRecette();
    void setEtatFenAjouterRecette(bool stated);
    void restaurerDerniereRecette();
};

#endif // MAINWINDOW_H
