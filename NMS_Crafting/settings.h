#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>
#include <QVariant>
#include <QByteArray>
#include <QDebug>


class settings
{
public:
    settings();

    void initialisation(bool test = false);

    void setImagePath(QString path);
    QString getImagePath();
    QString getIniImagePath();

    void setBddPath(QString path);
    QString getBddPath();
    QString getIniBddPath();

    void setBddName(QString name);
    QString getIniBddName();
    QString getBddName();

    void setFarming(bool enabled);
    bool getIniFarming();
    bool getFarming();

    void setAutoExpand(bool enabled);
    bool getIniAutoExpand();
    bool getAutoExpand();

    void setRestoreRecipe(bool enabled);
    bool getIniRestoreRecipe();
    bool getRestoreRecipe();

    void setLastRecipe(QList<QVariant> name);
    QList<QVariant> getIniLastRecipe();
    QList<QVariant> getLastRecipe();

    void setQteLastRecipe(int quantite);
    int getIniQteLastRecipe();
    int getQteLastRecipe();

    void setGeometrie(QByteArray geometrie);
    void setEtat(QByteArray etat);
    void setGeometrieEtat(QByteArray geometrie, QByteArray etat);
    QByteArray getIniGeometrie();
    QByteArray getGeometrie();
    QByteArray getIniEtat();
    QByteArray getEtat();

    void setRestoreSizePos(bool enabled);
    bool getIniRestoreSizePos();
    bool getRestoreSizePos();

private:
    const QVariant settingDefaultString = "DNE";
    const QVariant settingDefaultInt = -1;
    const QVariant settingDefaultBool = false;
    const QVariant settingDefaultByteArray = "DNE";

    QSettings *iniParam;
    QString imagePath;
    QString bddPath;
    QString bddName;
    bool farming;
    bool autoExpand;
    bool restoreRecipe;
    //QString lastRecipe;
    QList<QVariant> lastRecipe;
    int quantiteLastRecipe;
    QByteArray geometrie;
    QByteArray etat;
    bool restoreSizePos;
};

#endif // SETTINGS_H
