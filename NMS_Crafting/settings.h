#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>
#include <QVariant>
#include <QDebug>


class settings
{
public:
    settings();
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

    void setLastRecipe(QString name);
    QString getIniLastRecipe();
    QString getLastRecipe();

    void setQteLastRecipe(int quantite);
    int getIniQteLastRecipe();
    int getQteLastRecipe();

private:
    const QVariant settingDefaultString = "DNE";
    const QVariant settingDefaultInt = -1;
    const QVariant settingDefaultBool = false;

    QSettings *iniParam;
    QString imagePath;
    QString bddPath;
    QString bddName;
    bool farming;
    bool autoExpand;
    bool restoreRecipe;
    QString lastRecipe;
    int quantiteLastRecipe;
};

#endif // SETTINGS_H
