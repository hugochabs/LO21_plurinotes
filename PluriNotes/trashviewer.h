#ifndef TRASHVIEWER_H
#define TRASHVIEWER_H

#include "note.h"

#include <QDialog>
#include <QTreeWidget>
#include "colleague.h"

namespace Ui {
class TrashViewer;
}

//!TrashViewer est hérité de la classe Widget pour pouvoir communiquer
//! avec le Mediator ainsi que ses collegues
class TrashViewer : public QDialog, public Widget
{
    Q_OBJECT

public:
    explicit TrashViewer( unsigned int i, QWidget *parent = 0);
    ~TrashViewer();
    void initialisationTrash();
    void update(){}

private:
    Ui::TrashViewer *ui;

    QTreeWidgetItem* addRoot(QTreeWidget* parent, QString id, QString type);
    void addChild(QTreeWidgetItem* parent, QString title,QString type);
};

#endif // TRASHVIEWER_H
