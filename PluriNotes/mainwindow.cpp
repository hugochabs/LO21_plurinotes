#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(unsigned int i, QWidget *parent) :
    QMainWindow(parent),
     ui(new Ui::MainWindow),ind(-1), n(0), nv(0), Widget(i)

{
    ui->setupUi(this);
    setWindowTitle(tr("PluriNote"));

    ui->dc->setReadOnly(true);
    ui->dm->setReadOnly(true);


    ui->dc->setReadOnly(true);
    ui->dm->setReadOnly(true);

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
    ui->dateTimeEdit->setVisible(false);

    //on connecte les différents signaux et slots
    QObject::connect(ui->ListNotes, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(affichage(QTreeWidgetItem*, int)));
    QObject::connect(ui->addNote, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(this, SIGNAL(signalA()), this, SLOT(slotA()));
    connect(this, SIGNAL(signalT()), this, SLOT(slotT()));
    connect(this, SIGNAL(signalON()), this, SLOT(slotON()));
    connect(ui->saveMW, SIGNAL(clicked()), this, SLOT(updateN()));
    connect(this, SIGNAL(modify()), this, SLOT(updateAff()));
    connect(ui->delete_2, SIGNAL(clicked()), this, SLOT(delete2()));

    connect(ui->directoryFile, SIGNAL(clicked()), this, SLOT(chooseFile()));
    connect(ui->restoreButton, SIGNAL(clicked()), this, SLOT(restore()));
    connect(ui->trashButton, SIGNAL(clicked()), this, SLOT(goToTrash()));
    connect(ui->relationButton, SIGNAL(clicked(bool)), this ,SLOT(goToRelation()));
    connect(ui->quit, SIGNAL(clicked(bool)), this, SLOT(quit()));

}


//!Destructeur
MainWindow::~MainWindow()
{
    delete ui;
}

QTreeWidget* MainWindow::getTreeNote(){
    return ui->ListNotes;
}

QTreeWidget* MainWindow::getTreeArchived(){
    return ui->listArchived;
}

void MainWindow::clearAffichage(){
    ui->listArchived->clear();
    ui->ListNotes->clear();
    ui->listTask->clear();
    ui->listTask->setRowCount(0);
}

//!Méthode virtuelle définit dans la classe Widget
//! Elle permet de mettre à jour l'affichage quand un de ses collègues
//! le notifie
void MainWindow::update(){
    clearAffichage();
    initialisationArchive();
    initialisationNA();
    initialisationT();
}

void MainWindow::quit(){
    AlertViewer* alert = new AlertViewer("Corbeille", "Voulez-vous vider la corbeille ?");
    QPushButton* o = alert->addButton("Oui", QMessageBox::YesRole);
    QPushButton* no = alert->addButton("Non", QMessageBox::NoRole);
    alert->exec();
    close();
}




