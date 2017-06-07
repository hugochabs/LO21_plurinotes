#ifndef RELATIONVIEWER_H
#define RELATIONVIEWER_H

#include <QDialog>
#include "relation.h"

namespace Ui {
class RelationViewer;
}

class RelationViewer : public QDialog
{
    Q_OBJECT

public:
    explicit RelationViewer(QWidget *parent = 0);
    ~RelationViewer();
    void initialisation();

private:
    Ui::RelationViewer *ui;
};

#endif // RELATIONVIEWER_H
