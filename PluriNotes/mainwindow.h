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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initialisationNA(NoteManager &nm);
    void initialisationT(NoteManager &nm);

    //!Fonctions pour remplir QTreeWidget
    QTreeWidgetItem* addRoot(QString id, QString type);
    void addChild(QTreeWidgetItem* parent, QString id, QString type);

    void fillA(Article& a) const;
    void fillT(Task& t)const;
    void fillTWD(TaskWithDeadline& t)const;
    void fillTWP(TaskWithPriority& t)const;
    void fillON(OtherNote& on)const;

private:
    Ui::MainWindow *ui;
    int ind;

signals:
    //!Signaux pour modifier affichage principal
    void  signalA();
    void  signalT();
    void  signalTWD();
    void  signalTWP();
    void  signalON();


public slots:
    //!slot quand on clique sur une note dans l'arbre de gauche
    void affichage(QTreeWidgetItem *item, int i);
    //Slots modification affichage principal
    void add();
    void slotA();
    void slotT();
    void slotON();



};

#endif // MAINWINDOW_H
