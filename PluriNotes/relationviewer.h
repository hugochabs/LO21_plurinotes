#ifndef RELATIONVIEWER_H
#define RELATIONVIEWER_H

#include <QDialog>
#include "relation.h"
#include "colleague.h"
#include "mainwindow.h"



namespace Ui {
class RelationViewer;
}

//!RelationViewer est hérité de la classe Widget pour pouvoir communiquer
//! avec le Mediator ainsi que ses collegues
class RelationViewer : public QDialog, public Widget
{
    Q_OBJECT

public:
    explicit RelationViewer( unsigned int i, QWidget *parent = 0);
    ~RelationViewer();
    void initialisation();
    void update(){}


private:
    Relation* r;
    Ui::RelationViewer *ui;
    void addChild(QTreeWidgetItem* parent, QString label);

public slots:
    void quit();
};

#endif // RELATIONVIEWER_H
