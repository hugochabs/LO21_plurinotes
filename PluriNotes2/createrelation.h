#ifndef CREATERELATION_H
#define CREATERELATION_H

#include <QDialog>
#include "colleague.h"
#include "relation.h"
#include "alertviewer.h"

namespace Ui {
class CreateRelation;
}
/*!
 * \brief la classe CreateRelation est responsable de l'affichage de le fenêtre pour créer une nouvlle relation.
 */
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

class EnrichRelation : public QDialog, public Widget{
    Q_OBJECT
private :
    QLabel* label;
    QLineEdit* labelEdit;
    QLabel* note1;
    QLabel* note2;
    QLineEdit* note1Edit;
    QLineEdit* note2Edit;
    QPushButton* cancel;
    QPushButton* ok;

public:
    EnrichRelation(unsigned int i, QWidget* parent=0);
    //~EnrichRelation();
    Mediator* mediator;
    void update(){}

public slots:

};

#endif // CREATERELATION_H
