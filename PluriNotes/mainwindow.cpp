#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), ind(-1)
{
    ui->setupUi(this);

    ui->ListNotes->setColumnCount(2);

    QStringList labels;
    labels<<"Task"<<"Deadline"<<"Priority";
    ui->listTask->setColumnCount(3);
    ui->listTask->setHorizontalHeaderLabels(labels);
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

    //on connecte les différents signaux et slots
    QObject::connect(ui->ListNotes, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(affichage(QTreeWidgetItem*, int)));
    QObject::connect(ui->addNote, SIGNAL(clicked(bool)), this, SLOT(add()));
    connect(this, SIGNAL(signalA()), this, SLOT(slotA()));
    connect(this, SIGNAL(signalT()), this, SLOT(slotT()));

}


//!Destructeur
MainWindow::~MainWindow()
{
    delete ui;
}

//!Fonctions qui permet d'ajouter les notes présentes dans NoteManager
QTreeWidgetItem* MainWindow::addRoot(QString id, QString type){
    QTreeWidgetItem* note = new QTreeWidgetItem(ui->ListNotes);
    note->setText(0, id);
    note->setText(1, type);
    ui->ListNotes->addTopLevelItem(note);
    return note;
}

void MainWindow::addChild(QTreeWidgetItem* parent, QString id,QString type){
    QTreeWidgetItem* note = new QTreeWidgetItem();
    cout<<"enfant"<<endl;
    note->setText(0, id);
    note->setText(1, type);
    parent->addChild(note);
}

//!On initialise l'affichage au lancement de l'application
void MainWindow::initialisationNA(NoteManager& nm){
    unsigned int i=1;
    for(NoteManager::iterator it = nm.getIterator();!it.isDone();it.isNext()){
            NoteVersions nv = it.current();
            NoteVersions::iterator it1 = nv.end();
            Note n = it1.current();

            QTreeWidgetItem* note1;
            if(n.getNoteStatus()){
                 note1 = addRoot(n.getIdentifier(), nv.getTypeQS());
                for(NoteVersions::iterator it2=nv.getIterator();!it2.isDone1(); it2.isNext()){
                     cout<<"test2"<<endl;
                     Note temp = it2.current();
                     addChild(note1, temp.getIdentifier(), nv.getTypeQS());
                 }
            }
            i++;
    }

}

void MainWindow::initialisationT(NoteManager& nm){
    unsigned int i=1;
    for(NoteManager::iterator it = nm.getIterator();!it.isDone();it.isNext()){
            NoteVersions nv = it.current();
            NoteVersions::iterator it1 = nv.getIterator();
            Note& n = it1.current();

            if(nv.getTypeQS()=="Task" || nv.getTypeQS()=="Task with priority" || nv.getTypeQS()=="Task with deadline"){
                cout<<"if"<<endl;
                    Task& t = static_cast<Task&>(n);
                    QTableWidgetItem* id=new QTableWidgetItem(t.getIdentifier());
                    QTableWidgetItem* status=new QTableWidgetItem(t.getStatusQS());
                    //QTableWidgetItem* action=new QTableWidgetItem(t.getAction());

                    ui->listTask->insertRow(ui->listTask->rowCount());
                    int row = ui->listTask->rowCount()-1;
                    cout<<row<<endl;
                    ui->listTask->setItem(row,0, id);
                    ui->listTask->setItem(row,1, status);
                    //ui->listTask->setItem(row,2, action);
            }
            i++;
    }

}

NoteManager& manager = NoteManager::getNoteManager();

//! SLOT : Connecté au signal, itemClicked(), permet d'afficher sur la note actie sélectionnée
void MainWindow::affichage(QTreeWidgetItem* item, int i){
    QString id = item->text(i);
    for(NoteManager::iterator it = manager.getIterator();!it.isDone();it.isNext()){
        NoteVersions nv = it.current();

        for(NoteVersions::iterator it2=nv.getIterator();!it2.isDone(); it2.isNext()){

             Note& temp = it2.current();
             if(id==temp.getIdentifier()){
                 ui->id->setText(temp.getIdentifier());
                 ui->titre->setText(temp.getTitle());
                 ui->dc->setText(temp.getDateCQString());
                 ui->dm->setText(temp.getDateLUQString());

                 //! Selon le type de Note, on modifie l'affichage et on remplie les champs de chaque sous-clase de Note
                 switch(nv.getType()){
                 case NoteType::A :
                 {
                     Article &art = static_cast<Article&>(temp);
                     fillA(art);
                     emit signalA();}
                    return;
                 case NoteType::T :
                 {
                     Task &t = static_cast<Task&>(temp);
                     fillT(t);
                     emit signalT();}
                     return;

                 case NoteType::TWD :{
                     TaskWithDeadline &t = static_cast<TaskWithDeadline&>(temp);
                     fillTWD(t);
                     emit signalT();}
                     return;
                 case NoteType::TWP :{
                     TaskWithPriority &t = static_cast<TaskWithPriority&>(temp);
                     fillTWP(t);
                     emit signalT();}
                     return;
                 case NoteType::ON:{
                         OtherNote &on = static_cast<OtherNote&>(temp);
                         fillON(on);
                     emit signalON();}
                     return;
                 }


             }
         }

    }

}


//! SLOT : Quand on clique sur "Ajouter une Note", ouverture d'une nouvelle fenêtre
void MainWindow::add(){
    NoteEditeur* newNote = new NoteEditeur;
    newNote->show();
}


//!SLOT : modifiant l'affichage principal
void  MainWindow::slotA(){
    if(ind!=1){

        ui->prop1L->setVisible(true);
        ui->prop1L->setText("Text");
        ui->prop1->setVisible(false);
        ui->text->setVisible(true);

        ui->prop2L->setVisible(false);
        ui->prop2->setVisible(false);

        ui->prop3L->setVisible(false);
        ui->prop3->setVisible(false);
        ui->typeON->setVisible(false);

        ui->prop4L->setVisible(false);
        ui->prop4->setVisible(false);

        //ui->save->setVisible(true);
        ind=1;
        //emit fillA(n);
    }
}

void MainWindow::slotT(){
    if(ind!=2){
        cout<<"if"<<endl;
        ui->prop1L->setVisible(true);
        ui->prop1L->setText("Action");
        ui->prop1->setVisible(true);
        ui->text->setVisible(false);

        ui->prop2L->setVisible(true);
        ui->prop2L->setText("Priority");
        ui->prop2->setVisible(true);

        ui->prop3L->setVisible(true);
        ui->prop3L->setText("Deadline");
        ui->prop3->setVisible(true);
        ui->typeON->setVisible(false);

        ui->prop4L->setVisible(true);
        ui->prop4L->setText("Status");
        ui->prop4->setVisible(true);

        //save->setVisible(true);
       ind=2;
    }
}



void MainWindow::slotON(){
    if(ind!=3){

        ui->prop1L->setVisible(true);
        ui->prop1L->setText("Description");
        ui->prop1->setVisible(true);
        ui->text->setVisible(false);

        ui->prop2L->setVisible(true);
        ui->prop2L->setText("Filename");
        ui->prop2->setVisible(true);

        ui->prop3L->setVisible(true);
        ui->prop3L->setText("Type");
        ui->prop3->setVisible(false);
        ui->typeON->setVisible(true);

        ui->prop4L->setVisible(false);

        ui->prop4->setVisible(false);

        //save->setVisible(true);
       ind=3;
    }
}


//!Fonctions qui permettent de remplir les champs de l'affichage principal
void MainWindow::fillA(Article& a)const{

    ui->text->setText(a.getText());
}

void MainWindow::fillT(Task& t)const{

    ui->prop1->setText(t.getAction());
    ui->prop4->setText(t.getStatusQS());
}

void MainWindow::fillTWD(TaskWithDeadline& t)const{
    fillT(t);
    QString date = Note::QStringFromDate(t.getDeadline());

    ui->prop3->setText(date);
}

void MainWindow::fillTWP(TaskWithPriority& t)const{
    fillT(t);
    ui->prop2->setText(t.getPriorityQS());
}

void MainWindow::fillON(OtherNote& on)const{
    ui->prop1->setText(on.getDescription());
    ui->prop2->setText(on.getFileName());
}


