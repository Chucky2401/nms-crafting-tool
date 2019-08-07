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

public slots:
    void clickListerIngredients();
    void recetteChoisis(int index);
    void modifierQuantite(int valeur);
    void setFarming(int state);
    void setAutoExpand(int state);


private:
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

    QSettings *settings;
    QString imagePath;
    QString bddPath;
    QString bddName;
    QString farming;
    QString autoExpand;
};

#endif // MAINWINDOW_H
