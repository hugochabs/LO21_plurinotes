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

    /*!
     * \brief initialisationTrash est une fonction qui initialise et met à jour l'affichage du trashViewer
     */
    void initialisationTrash();

    /*!
     * \brief update est une fonction virtuelle héritée de la classe Widget
     */
    void update(){}

private:
    Ui::TrashViewer *ui;
    Note* n;
    NoteVersions* nv;

public slots:
    /*!
     * \brief quit slot appelé à la sortie de la fenetre, il envoie un message à Mainwindow pour notifier que NoteManager a peut etre changer
     */
    void quit();

    /*!
     * \brief restore permet de restaurer la note selectionnée
     */
    void restore();

    /*!
     * \brief select
     * \param item
     * \param i
     */
    void select(QTreeWidgetItem* item, int i);
};

#endif // TRASHVIEWER_H
