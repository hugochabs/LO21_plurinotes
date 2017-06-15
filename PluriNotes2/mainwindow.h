#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QListWidgetItem>
#include <QTreeWidget>

#include <QFileDialog>
#include <QObject>

#include "notefille.h"
#include "noteediteur.h"
#include "relation.h"

#include "trashviewer.h"
#include "relationviewer.h"
#include "alertviewer.h"


using namespace std;


namespace Ui {
class MainWindow;
}

/*!
 * \brief La classe MainWindow est la fenêtre principale
 * c'est ici que sont disposés tous les widgets de l'interface principale
 * elle hérite de la classe Widget pour pouvoir communiiquer avec les autres fenêtres
 */
class MainWindow : public QMainWindow, public Widget
{
    Q_OBJECT

    friend class NoteEditeur;

public:
    explicit MainWindow(unsigned int i, QWidget *parent = 0);
    ~MainWindow();

    //! Fonctions qui permettent l'initialisation et MaJ de l'affichage des différents QWidgets d'affichage
    void initialisationNA();
    void initialisationT();
    void initialisationArchive();


    //! Getters element MainWindow
    QTreeWidget* getTreeNote();
    QTreeWidget* getTreeArchived();

    //!Fonctions pour remplir QTreeWidget
    static QTreeWidgetItem* addRoot(QTreeWidget* parent, QString id, QString type);
    static QTreeWidgetItem* addRootBis(QTreeWidget* parent, QString id);
    static void addChild(QTreeWidgetItem* parent, QString title, QString type);
    static QTreeWidgetItem* addChildBis(QTreeWidgetItem* parent, QString title);

    void fillNote(Note* n)const;//!affiche les propriétés de la note selectionnée sur l'affichage principal
    void fillA(Article& a)const;//!affiche les propriétés de l'article selectionné sur l'affichage principal
    void fillT(Task &t)const;//!affiche les propriétés de la tâche selectionnée sur l'affichage principal
    void fillTWD(TaskWithDeadline& t)const;//!affiche les propriétés de la note selectionnée sur l'affichage principal
    void fillTWP(TaskWithPriority& t)const;//!affiche les propriétés de la note selectionnée sur l'affichage principal
    void fillON(OtherNote &on)const;//!affiche les propriétés de la note selectionnée sur l'affichage principal
    void setAffichage(NoteType nt, Note& n);
    void clearAffichage();
    void addElementsInWidgets(map<Note *, int>& N, QTreeWidget* widget);

    /*!
     * \brief update est une méthode virtuelle pure qui est définie ici, héritée de la classe Widget
     */
    void update();


private:
    Ui::MainWindow *ui;
    int ind;
    Note* n;//! on enregistre l'adresse de la note sélectionnée
    NoteVersions* nv;//! on enregistre le noteVersions de la note sélectionnée
    QString dir;



signals:
    //!Signaux pour modifier affichage principal
    void  signalA();
    void  signalT();
    void  signalTWD();
    void  signalTWP();
    void  signalON();
    void  modify();



public slots:
    //!slot quand on clique sur une note active dans l'arbre de gauche
    void affichage(QTreeWidgetItem *item, int i);

    //!Slots modification affichage principal
    void add();
    void slotA();
    void slotT();
    void slotON();

    //!Permet l'enregistrement de note dans une nouvelle version de note
    void updateN();
    //!Met à jour les différents widges de la fenêtre
    void updateAff();



    void delete2();//! SLOT activé quand on on veut supprimer une note
    void chooseFile();//! permet de sélectionner un fichier pour OtherNote
    //void open();
    void restore();//! permet de restaurer une note archivée
    void goToTrash();//! permet d'ouvrir la corbeille
    void goToRelation();//! permet d'ouvrir la fenêtre de visualisation des relations
    void emptyTrash();//! SLOT activé à la sortie de l'application, vide la corbeille.
    void quit();//! demande à l'utilisateur si'il veut vider la corbeille.
};




#endif // MAINWINDOW_H
