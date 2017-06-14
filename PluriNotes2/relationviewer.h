#ifndef RELATIONVIEWER_H
#define RELATIONVIEWER_H

#include <QDialog>
#include "relation.h"
#include "colleague.h"
#include "mainwindow.h"
#include "createrelation.h"



namespace Ui {
class RelationViewer;
}

/*!
 * \brief La classe RelationViewer hérite de Widget pour pouvoir communiquer avec Mediator
 * Cette classe permet de visualiser toutes les relations
 */
class RelationViewer : public QDialog, public Widget
{
    Q_OBJECT

public:
    explicit RelationViewer( unsigned int i, QWidget *parent = 0);
    ~RelationViewer();
    void initialisation();
    void update();
    void fillRelation(Relation& r);
    void fillCouple(Couple& c);


private:
    Relation* r;
    Couple* c;
    Ui::RelationViewer *ui;
    void addChild(QTreeWidgetItem* parent, QString label);

public slots:
    void quit();
    void affichageRelation(QTreeWidgetItem* item, int i=0);
    void affichageCouple(QTreeWidgetItem* item, int i);
    void addRel();
    void enrichRel();
    Relation* getRelation(){return r;}
};

#endif // RELATIONVIEWER_H
