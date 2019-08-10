#ifndef AJOUTERRECETTE_H
#define AJOUTERRECETTE_H

#include <QDialog>
#include <QDebug>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>

#include "database.h"
#include "settings.h"

namespace Ui {
class ajouterRecette;
}

class ajouterRecette : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterRecette(QWidget *parent = nullptr);
    ~ajouterRecette();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void chooseImage();
    void titreEdited(QString titre);
    void sousTitreEdited(QString sousTitre);

private:
    Ui::ajouterRecette *ui;
    const QString connectionName = "ajoutRecette";

    QFileDialog *fileDialog;
    QString fileNameComplete;

    class database bdd;
    class settings param;
};

#endif // AJOUTERRECETTE_H
