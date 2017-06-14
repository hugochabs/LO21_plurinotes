#ifndef CREATERELATION_H
#define CREATERELATION_H

#include <QDialog>
#include <QBoxLayout>
#include <QComboBox>
#include "colleague.h"
#include "relation.h"
#include "alertviewer.h"

namespace Ui {
class CreateRelation;
}
/*!
 * \brief la classe CreateRelation est responsable de l'affichage de le fenêtre pour créer une nouvelle relation.
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

/*!
 * \brief La classe EnrichRelation permet d'enrichier une relation graphiquement
 * on rentre le label du couple, et on sélectionne les deux Notes du couple
 */
class EnrichRelation : public QDialog, public Widget{
    Q_OBJECT
private :
    QLabel* label;
    QLineEdit* labelEdit;
    QLabel* note1;
    QLabel* note2;
//    QLineEdit* note1Edit;
//    QLineEdit* note2Edit;
    QComboBox* choice1;
    QComboBox* choice2;
    QPushButton* cancel;
    QPushButton* ok;
    QHBoxLayout* labels;
    QHBoxLayout* noteX;
    QHBoxLayout* noteY;
    QHBoxLayout* buttons;
    QVBoxLayout* vertical;
    Relation* r;

public:
    EnrichRelation(unsigned int i, Relation* rel,QWidget* parent=0);
    //~EnrichRelation();
    Mediator* mediator;
    void update(){}

    Relation* getRelation(){return r;}

public slots:
    /*!
     * \brief addC Ajoute un couple à la relation selectionnée dansle RelationViewer
     */
    void addC();
    /*!
     * \brief activeOK rend le bouton ok active quand le label est rentré
     */
    void activeOK();

};

#endif // CREATERELATION_H
