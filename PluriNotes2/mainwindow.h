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
    void fillNote(Note* n)const;
    void fillA(Article& a)const;
    void fillT(Task &t)const;
    void fillTWD(TaskWithDeadline& t)const;
    void fillTWP(TaskWithPriority& t)const;
    void fillON(OtherNote &on)const;
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
    Note* n;
    NoteVersions* nv;
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
    //!slot quand on clique sur une note dans l'arbre de gauche
    void affichage(QTreeWidgetItem *item, int i);

    //Slots modification affichage principal
    void add();
    void slotA();
    void slotT();
    void slotON();

    //!Permet l'enregistrement d'e note'une nouvelle version de note
    void updateN();
    //!Met à jour les différents widges de la fenêtre
    void updateAff();

    void archive();
    void delete2();
    void chooseFile();
    //void open();
    void restore();
    void goToTrash();
    void goToRelation();
    void emptyTrash();
    void quit();
};




#endif // MAINWINDOW_H
