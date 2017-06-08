#include "relationviewer.h"
#include "ui_relationviewer.h"

RelationViewer::RelationViewer(unsigned int i, QWidget *parent) :
    Widget(i),
    QDialog(parent),
    ui(new Ui::RelationViewer)
{
    ui->setupUi(this);
    setWindowTitle(tr("Ensemble des relations"));
}

RelationViewer::~RelationViewer()
{
    delete ui;
}

RelationManager& rm = RelationManager::getRelationManager();
void RelationViewer::initialisation(){

}
