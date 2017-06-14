#ifndef TRASHVIEWER_H
#define TRASHVIEWER_H

#include "note.h"

#include <QDialog>
#include <QTreeWidget>
#include "colleague.h"
#include "mainwindow.h"

namespace Ui {
class TrashViewer;
}

/*!
 * \brief La classe TrashViewer hérite de la classe Widget
 * la classe trashViewer permet de visualiser les éléments dans la corbeille
 */
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
    Note* n;
    NoteVersions* nv;

public slots:
    void quit();
    void restore();
    void select(QTreeWidgetItem* item, int i);
};

#endif // TRASHVIEWER_H
