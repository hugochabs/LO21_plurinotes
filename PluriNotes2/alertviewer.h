#ifndef ALERTVIEWER_H
#define ALERTVIEWER_H

#include <QMessageBox>


/*!
 * \brief la classe AlertViewer est une fenêtre qui affiche des messages de validation, confirmation de l'utilisateur
 */
class AlertViewer : public QMessageBox
{
public:
    /*!
     * \brief AlertViewer constructeur
     * \param title est le titre donné à la fentre de message
     * \param message affiché dans la fenetre
     */
    AlertViewer(const QString& title, const QString &message);
};

#endif // ALERTVIEWER_H
