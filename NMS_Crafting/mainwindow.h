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
    bool createConnection();
    void listeRecettes();
    void listerIngredients(QString recette);
    void pourTout(QAbstractItemModel* modele, QModelIndex parent = QModelIndex());
    bool getEtatFenAjouterRecette();
    void setEtatFenAjouterRecette(bool stated);

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
    void ouvrirFenAjouterRecette();
    void fenAjouterRecetteClose(int result);


private:
    ajouterRecette *fenAjouterRecette;
    bool fenAjouterRecetteOuverte;
    const QVariant settingDefaultString = "DNE";
    const QVariant settingDefaultInt = -1;

    Ui::MainWindow *ui;
    QSqlDatabase db;
    QString recetteSelectionne;
    QStandardItemModel *modele;
    QGraphicsPixmapItem itemImageRecette;
    QGraphicsScene imageRecette;
    bool viewWasExtended;
    QStringList itemExpanded;

    class settings param;
};

#endif // MAINWINDOW_H
