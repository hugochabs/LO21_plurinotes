#ifndef NOTEEDITEUR_H
#define NOTEEDITEUR_H

#include <QMainWindow>
#include <QString>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QBoxLayout>
#include <QFileDialog>
#include <QObject>
#include <QRadioButton>
#include <QComboBox>
#include "notefille.h"
#include "exception.h"
#include "mainwindow.h"
#include "colleague.h"
#include "alertviewer.h"


//!NoteEditeur est hérité de la classe Widget pour pouvoir communiquer
//! avec le Mediator ainsi que ses collegues
class NoteEditeur : public QDialog, public Widget {

    Q_OBJECT

    friend class MainWindow;

    QVBoxLayout* layoutv;
    QHBoxLayout* layouth1;
    QHBoxLayout* layouth2;
    QHBoxLayout* layouth3;
    QHBoxLayout* layouthbutton;
    QLabel* idl;
    QLabel* titre1;

    QLineEdit* id;
    QLineEdit* titre;
    QPushButton* save;
    QPushButton* quit;
    QRadioButton* task;
    QRadioButton* article;
    QRadioButton* other;


    //propriétés notefille
    unsigned int ind;
    QLabel* prop1L;
    QLineEdit* prop1;
    QTextEdit* art;
    QLabel* prop2L;
    QLineEdit* prop2;
    QLabel* prop3L;
    QLineEdit* prop3;
    QLabel* prop4L;
    QLineEdit* prop4;
    QComboBox* menu;
    //layout
    QHBoxLayout* layout1;
    QHBoxLayout* layout2;
    QHBoxLayout* layout3;
    QHBoxLayout* layout4;
    //Article* article;



public:
    NoteEditeur(unsigned int i, QWidget *parent=0);
    void changed();
    void update(){

    }


public slots :
    /*void saveArticle();*/
    void activerSave();
    void changeTask();
    void changeArticle();

    void changeOther();
    void addN();
signals:
    // modify();


};

#endif // NOTEEDITEUR_H
