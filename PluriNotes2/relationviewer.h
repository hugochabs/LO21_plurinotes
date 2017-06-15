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

    /*!
     * \brief initialisation initialise tous les objets de la classe RelationViewer
     */
    void initialisation();

    /*!
     * \brief update est une méthode virtuelle héritée de la classe Widget, ici l'affichage est mis à jour
     */
    void update();

    /*!
     * \brief fillRelation remplit les champs présents sur la droite de la fenetre quand on clique sur une relation
     * \param r est la Relation à afficher
     */
    void fillRelation(Relation& r);

    /*!
     * \brief fillCouple remplit les champs sur la droite de la fenetre quand on double-clique sur un couple
     * \param c est le couplle à afficher
     */
    void fillCouple(Couple& c);


private:
    Relation* r;
    Couple* c;
    Ui::RelationViewer *ui;
    void addChild(QTreeWidgetItem* parent, QString label);

public slots:
    /*!
     * \brief quit est un slot appelé à la sortie de la fenetre
     */
    void quit();

    /*!
     * \brief affichageRelation slot appelé quand on clique sur une relation
     * \param item
     * \param i
     */
    void affichageRelation(QTreeWidgetItem* item, int i=0);

    /*!
     * \brief affichageCouple appelé quand on clique sur un couple
     * \param item
     * \param i
     */
    void affichageCouple(QTreeWidgetItem* item, int i);

    /*!
     * \brief addRel permet d'ajouter une relation
     */
    void addRel();

    /*!
     * \brief enrichRel permet d'enrichir une relation, c'est-a-dire qu'on peut rajouter un couple dans cette relation
     */
    void enrichRel();
    Relation* getRelation()const{return r;}
};

#endif // RELATIONVIEWER_H
