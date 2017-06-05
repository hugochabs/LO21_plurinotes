#include "mainwindow.h"
#include "ui_mainwindow.h"

NoteManager& manager1 = NoteManager::getNoteManager();

int n=manager1.getNb();

//!Fonctions qui permet d'ajouter les notes présentes dans Notemanager
QTreeWidgetItem* MainWindow::addRoot(QTreeWidget* parent, QString id, QString type){
    QTreeWidgetItem* note = new QTreeWidgetItem(parent);
    note->setText(0, id);
    note->setText(1, type);
    parent->addTopLevelItem(note);
    return note;
}

void MainWindow::addChild(QTreeWidgetItem* parent, QString title,QString type){
    QTreeWidgetItem* note = new QTreeWidgetItem();
    cout<<"enfant"<<endl;
    note->setText(0, title);
    note->setText(1, type);
    parent->addChild(note);
}

//!On initialise l'affichage au lancement de l'application
void MainWindow::initialisationNA(){
    for(NoteManager::iterator it = manager1.getIterator();!it.isDone();it.isNext()){
            NoteVersions nv = it.current();
            NoteVersions::iterator it1 = nv.getIterator();
            Note n = it1.current();

            QTreeWidgetItem* note1;
            if(n.getNoteStatusString()=="active"){
                note1 = addRoot(ui->ListNotes, n.getIdentifier(), nv.getTypeQS());
                for(NoteVersions::iterator it2=nv.getIterator1();!it2.isDone(); it2.isNext()){
                     Note temp = it2.current();
                     addChild(note1, temp.getIdentifier(), nv.getTypeQS());
                 }
            }

    }

}

void MainWindow::initialisationT(){
    //unsigned int i=1;
    for(NoteManager::iterator it = manager1.NoteManager::getIterator();!it.isDone();it.isNext()){
            NoteVersions nv = it.current();
            NoteVersions::iterator it1 = nv.NoteVersions::getIterator();
            Note& n = it1.current();
            int row;
            cout<<nv.getTypeQS()<<endl;
            cout<<it.getNbRemain()<<endl;
            cout<<manager1.getNb()<<endl;
            switch(nv.getType()){
            case NoteType::T :{
                    cout<<"ifT"<<endl;
                    Task& t = static_cast<Task&>(n);
                    //cout<<t.getAction()<<endl;
                    //QTableWidgetItem* id=new QTableWidgetItem(t.getIdentifier());
                    QTableWidgetItem* action = new QTableWidgetItem(t.Task::getAction());
                    ui->listTask->insertRow(ui->listTask->rowCount());
                    row = ui->listTask->rowCount()-1;
                    cout<<row<<endl;
                    ui->listTask->setItem(row,0, action);
                    break;}

             case NoteType::TWD : {
                cout<<"ifTWD"<<endl;
                TaskWithDeadline& t = static_cast<TaskWithDeadline&>(n);

                QString date = Note::QStringFromDate(t.getDeadline());
                QTableWidgetItem* action = new QTableWidgetItem(t.Task::getAction());
                //QTableWidgetItem* id=new QTableWidgetItem(t.getIdentifier());
                QTableWidgetItem* d=new QTableWidgetItem(date);
                cout<<"apres insertion"<<endl;
                ui->listTask->insertRow(ui->listTask->rowCount());
                cout<<"apres insertion"<<endl;
                row = ui->listTask->rowCount()-1;
                cout<<row<<endl;
                ui->listTask->setItem(row,0, action);
                ui->listTask->setItem(row,1, d);
                /*ui->listTask->setItem(row,2, status2);*/
                break;}

            case NoteType::TWP : {
               cout<<"ifTWD"<<endl;
               TaskWithPriority& t = static_cast<TaskWithPriority&>(n);

               QTableWidgetItem* action = new QTableWidgetItem(t.Task::getAction());

               QTableWidgetItem* prio=new QTableWidgetItem(t.getPriorityQS());

               ui->listTask->insertRow(ui->listTask->rowCount());

               row = ui->listTask->rowCount()-1;
               cout<<row<<endl;
               ui->listTask->setItem(row,0, action);
               ui->listTask->setItem(row,2, prio);
               break;}

           }
}
}

void MainWindow::initialisationArchive(){
    for(NoteManager::iterator it = manager1.getIterator();!it.isDone();it.isNext()){
            NoteVersions nv = it.current();
            NoteVersions::iterator it1 = nv.getIterator();
            Note n = it1.current();
            cout<<n<<endl;

            QTreeWidgetItem* note1;
            if(n.getNoteStatus() == NoteStatus::archived){
                cout<<"initialisation archived"<<endl;
                 note1 = addRoot(ui->listArchived, n.getIdentifier(), nv.getTypeQS());
            }

    }
}


void MainWindow::setAffichage(NoteType nt, Note& n){
    switch(nt){
    case NoteType::A :
    {
        Article& a = static_cast<Article&>(n);
        fillA(a);
        emit signalA();}
       return;
    case NoteType::T :
    {
        Task& t = static_cast<Task&>(n);
        fillT(t);
        emit signalT();}
        return;

    case NoteType::TWD :
    {
        TaskWithDeadline& t = static_cast<TaskWithDeadline&>(n);
        fillTWD(t);
        emit signalT();}
        return;
    case NoteType::TWP :{
        TaskWithPriority& t = static_cast<TaskWithPriority&>(n);
        fillTWP(t);
        emit signalT();}
        return;
    case NoteType::ON:{
        OtherNote& t = static_cast<OtherNote&>(n);
        fillON(t);
        emit signalON();}
        return;
    }
}


//!Fonctions qui permettent de remplir les champs de l'affichage principal
    void MainWindow::fillNote(Note* n)const{
    cout<<"fillNote"<<endl;
        ui->id->setText(n->getIdentifier());
    ui->titre->setText(n->getTitle());
    ui->dc->setText(n->getDateCQString());
    ui->dm->setText(n->getDateLUQString());
}


void MainWindow::fillA(Article& a)const{

    ui->text->setText(a.getText());
}

void MainWindow::fillT(Task& t)const{

    ui->prop1->setText(t.getAction());
    ui->prop4->setText(t.getStatusQS());
}

void MainWindow::fillTWD(TaskWithDeadline &t)const{
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


