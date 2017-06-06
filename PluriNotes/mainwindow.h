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
//#include "strategy.h
#include "trashviewer.h"


using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class NoteEditeur;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /*static MainWindow& getMainWindow();
    static void freeMainWindow();*/
    void initialisationNA();
    void initialisationT();
    void initialisationArchive();



    //!Fonctions pour remplir QTreeWidget
    QTreeWidgetItem* addRoot(QTreeWidget* parent, QString id, QString type);
    void addChild(QTreeWidgetItem* parent, QString title, QString type);
    void fillNote(Note* n)const;
    void fillA(Article& a)const;
    void fillT(Task &t)const;
    void fillTWD(TaskWithDeadline& t)const;
    void fillTWP(TaskWithPriority& t)const;
    void fillON(OtherNote &on)const;
    void setAffichage(NoteType nt, Note& n);








    //void affichage(QTreeWidgetItem *item, int i);
    //Slots modification affichage principal
private:
    Ui::MainWindow *ui;
    int ind;
    Note* n;
    NoteVersions* nv;



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
    void update();
    void updateAff();
    void archive();
    void delete2();
    void chooseFile();
    void restore();
    void goToTrash();
};




#endif // MAINWINDOW_H
