#ifndef AJOUTERRECETTE_H
#define AJOUTERRECETTE_H

#include <QDialog>
#include <QDebug>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QList>
#include <QMetaEnum>

#include "database.h"
#include "settings.h"

namespace Ui {
class ajouterRecette;
}

class ajouterRecette : public QDialog
{
    Q_OBJECT
    Q_ENUMS(eTypeComposant)
    Q_ENUMS(eCombo)

public:
    explicit ajouterRecette(QWidget *parent = nullptr, bool test = false);
    ~ajouterRecette();
    enum eTypeComposant {
        RESSOURCE, RECETTE
    };
    enum eCombo {
        COMPOSANT1, COMPOSANT2, COMPOSANT3
    };

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void chooseImage();
    void titreEdited(QString titre);
    void sousTitreEdited(QString sousTitre);
    void verifierTitreSousTitre();
    void listerRessourcesComposant1(bool checked);
    void listerRessourcesComposant2(bool checked);
    void listerRessourcesComposant3(bool checked);
    void listerRecettesComposant1(bool checked);
    void listerRecettesComposant2(bool checked);
    void listerRecettesComposant3(bool checked);
    void cliqueSurValider();

private:
    bool m_test;
    Ui::ajouterRecette *ui;
    const QString connectionName = "ajoutRecette";
    const QString defaultString = "NOTHING";
    bool sauvegardeReussi = false;

    QFileDialog *fileDialog;
    QString fileNameComplete;

    class Settings param;
    class database bdd;

    void listerComposants(QString typeComposant, QString combo = "Composant1");
    QList<QVariant> listeIdRecette(QString nomComposant, QString descriptionCourte);
};

#endif // AJOUTERRECETTE_H

