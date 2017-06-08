#ifndef RELATIONVIEWER_H
#define RELATIONVIEWER_H

#include <QDialog>
#include "relation.h"
#include "colleague.h"



namespace Ui {
class RelationViewer;
}

class RelationViewer : public QDialog, public Widget
{
    Q_OBJECT

public:
    explicit RelationViewer( unsigned int i, QWidget *parent = 0);
    ~RelationViewer();
    void initialisation();
    void update(){}

private:
    Ui::RelationViewer *ui;
};

#endif // RELATIONVIEWER_H
