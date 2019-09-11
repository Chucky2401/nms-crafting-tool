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

#include <QSettings>

#include <QDebug>

#include "settings.h"
#include "database.h"
#include "ajouterrecette.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);

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


private:
    ajouterRecette *fenAjouterRecette;
    bool fenAjouterRecetteOuverte;
    bool ouvertureEnCours;
    const QVariant settingDefaultString = "DNE";
    const QString defaultString = "NOTHING";
    const QVariant settingDefaultInt = -1;
    const QString connectionName = "principal";

    Ui::MainWindow *ui;
    QSqlDatabase db;
    //QString recetteSelectionne; // <--- QList<QVariant>
    QList<QVariant> recetteSelectionne;
    QStandardItemModel *modele;
    QGraphicsPixmapItem itemImageRecette;
    QGraphicsScene imageRecette;
    bool viewWasExtended;
    QStringList itemExpanded;

    bool createConnection();
    void listeRecettes();
    void listerIngredients(QList<QVariant> recette);
    void parcourirToutLeModele(QAbstractItemModel* modele, QModelIndex parent = QModelIndex());
    bool getEtatFenAjouterRecette();
    void setEtatFenAjouterRecette(bool stated);
    void restaurerDerniereRecette();

    class settings param;
    class database bdd;
};

#endif // MAINWINDOW_H
