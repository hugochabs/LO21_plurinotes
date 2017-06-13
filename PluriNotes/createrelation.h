#ifndef CREATERELATION_H
#define CREATERELATION_H

#include <QDialog>
#include "colleague.h"
#include "relation.h"
#include "alertviewer.h"

namespace Ui {
class CreateRelation;
}

class CreateRelation : public QDialog, public Widget
{
    Q_OBJECT

public:
    explicit CreateRelation(unsigned int i, QWidget *parent = 0);
    ~CreateRelation();
    void update(){}

private:
    Ui::CreateRelation *ui;
    Mediator* mediator;

public slots:
    void activeOK();
    void addRelation();
};

#endif // CREATERELATION_H
