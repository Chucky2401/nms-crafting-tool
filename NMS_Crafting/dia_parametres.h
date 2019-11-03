#ifndef DIA_PARAMETRES_H
#define DIA_PARAMETRES_H

#include <QDialog>
#include "settings.h"

namespace Ui {
class DIA_Parametres;
}

class DIA_Parametres : public QDialog
{
    Q_OBJECT

public:
    explicit DIA_Parametres(QWidget *parent = nullptr, bool m_test = false);
    ~DIA_Parametres();

private:
    Ui::DIA_Parametres *ui;
    // Divers
    bool m_test;
    // Classe complémentaires
    class settings param;

signals:
    void visibiliteFarming(bool visible);
    void visibiliteDeploiementAuto(bool visible);

private slots:
    void setRestoreRecipe(bool state);
    void setRestoreSizePos(bool state);
    void setVisibiliteFarming(bool visible);
    void setVisibiliteDeploiementAuto(bool visible);
    void setMiseAJourAuto(bool enabled);
    void setNombreJourMiseAJour(int nombreJour);
};

#endif // DIA_PARAMETRES_H
