#ifndef TRASHVIEWER_H
#define TRASHVIEWER_H

#include "note.h"

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class TrashViewer;
}

class TrashViewer : public QDialog
{
    Q_OBJECT

public:
    explicit TrashViewer(QWidget *parent = 0);
    ~TrashViewer();
    void initialisationTrash();

private:
    Ui::TrashViewer *ui;

    QTreeWidgetItem* addRoot(QTreeWidget* parent, QString id, QString type);
    void addChild(QTreeWidgetItem* parent, QString title,QString type);
};

#endif // TRASHVIEWER_H
