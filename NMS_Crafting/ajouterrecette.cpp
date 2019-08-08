#include "ajouterrecette.h"
#include "ui_ajouterrecette.h"

#include "mainwindow.h"

ajouterRecette::ajouterRecette(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ajouterRecette)
{
    ui->setupUi(this);
}

ajouterRecette::~ajouterRecette()
{
    delete ui;
}
