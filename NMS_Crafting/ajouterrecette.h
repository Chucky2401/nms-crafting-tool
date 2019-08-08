#ifndef AJOUTERRECETTE_H
#define AJOUTERRECETTE_H

#include <QDialog>

namespace Ui {
class ajouterRecette;
}

class ajouterRecette : public QDialog
{
    Q_OBJECT

public:
    explicit ajouterRecette(QWidget *parent = nullptr);
    ~ajouterRecette();

private:
    Ui::ajouterRecette *ui;
};

#endif // AJOUTERRECETTE_H
