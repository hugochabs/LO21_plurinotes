#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
     ui(new Ui::MainWindow),ind(-1), n(0), nv(0)

{
    ui->setupUi(this);




    QStringList labels1, labels2,labels3;
    labels1<<"Task"<<"Deadline"<<"Priority";
    ui->listTask->setColumnCount(3);
    ui->listTask->setHorizontalHeaderLabels(labels1);

    labels2<<"ID"<<"Type";
    ui->ListNotes->setColumnCount(2);
    ui->ListNotes->setHeaderLabels(labels2);

    labels3<<"ID"<<"Titre";
    ui->listArchived->setColumnCount(2);
    ui->listArchived->setHeaderLabels(labels3);

    ui->id->setReadOnly(true);


    //Différentes propriétés des class filles de note qu'on affiche dans la fenetre centrale
    ui->prop1L->setVisible(false);
    ui->prop1->setVisible(false);
    ui->text->setVisible(false);
    ui->prop2L->setVisible(false);
    ui->prop2->setVisible(false);
    ui->prop3L->setVisible(false);
    ui->prop3->setVisible(false);
    ui->prop4L->setVisible(false);
    ui->prop4->setVisible(false);
    ui->typeON->setVisible(false);
    ui->directoryFile->setVisible(false);

    //on connecte les différents signaux et slots
    QObject::connect(ui->ListNotes, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(affichage(QTreeWidgetItem*, int)));
    QObject::connect(ui->addNote, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(this, SIGNAL(signalA()), this, SLOT(slotA()));
    connect(this, SIGNAL(signalT()), this, SLOT(slotT()));
    connect(this, SIGNAL(signalON()), this, SLOT(slotON()));
    connect(ui->saveMW, SIGNAL(clicked()), this, SLOT(update()));
    connect(this, SIGNAL(modify()), this, SLOT(updateAff()));
    connect(ui->archiver, SIGNAL(clicked()), this, SLOT(archive()));
    connect(ui->directoryFile, SIGNAL(clicked()), this, SLOT(chooseFile()));
    connect(ui->restoreButton, SIGNAL(clicked()), this, SLOT(restore()));

}


//!Destructeur
MainWindow::~MainWindow()
{
    delete ui;
}





