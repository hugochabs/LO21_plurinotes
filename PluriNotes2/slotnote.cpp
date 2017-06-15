#include "mainwindow.h"
#include "ui_mainwindow.h"


NoteManager& manager2 = NoteManager::getNoteManager();

//! SLOT : Connecté au signal, itemClicked(), permet d'afficher sur la note active sélectionnée
void MainWindow::affichage(QTreeWidgetItem* item, int i){
    QString id = item->text(i);
    ui->saveMW->setEnabled(true);
    ui->restoreButton_2->setEnabled(true);
    ui->delete_2->setEnabled(true);
    for(NoteManager::iterator it = manager2.getIterator();!it.isDone();it.isNext()){
        NoteVersions& nvt = it.current();       
        for(NoteVersions::iterator it2=nvt.getIterator();!it2.isDone(); it2.isNext()){
             Note& temp = it2.current();
             if(id==temp.getIdentifier()){
                 fillNote(&temp);
                 setAffichage(nvt.getType(), temp);
                 n=&temp;
                 nv=&nvt;
                 return ;
             }
         }

    }
}


//! SLOT : Quand on clique sur "Ajouter une Note", ouverture d'une nouvelle fenêtre
void MainWindow::add(){
    NoteEditeur* newNote = new NoteEditeur(3);
    mediator->registerC(newNote);
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
        ui->directoryFile->setVisible(false);

        ui->prop3L->setVisible(false);
        ui->prop3->setVisible(false);
        ui->typeON->setVisible(false);
        ui->dl->setVisible(false);

        ui->prop4L->setVisible(false);
        ui->prop4->setVisible(false);

        //ui->save->setVisible(true);
        ind=1;
        //emit fillA(n);
    }
}

void MainWindow::slotT(){
    if(ind!=2){

        ui->prop1L->setVisible(true);
        ui->prop1L->setText("Action");
        ui->prop1->setVisible(true);
        ui->text->setVisible(false);

        ui->prop2L->setVisible(true);
        ui->prop2L->setText("Priority");
        ui->prop2->setVisible(true);
        ui->directoryFile->setVisible(false);

        ui->prop3L->setVisible(true);
        ui->prop3L->setText("Deadline");
        ui->prop3->setVisible(false);
        ui->typeON->setVisible(false);
        ui->dl->setVisible(true);

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
        //ui->prop2->setVisible(true);
        ui->directoryFile->setVisible(true);

        ui->prop3L->setVisible(false);
        ui->prop3->setVisible(false);
        ui->dl->setVisible(false);


        ui->prop4L->setVisible(true);
        ui->prop4L->setText("Type");
        ui->typeON->setVisible(true);

        ui->prop4->setVisible(false);

        //save->setVisible(true);
       ind=3;
    }
}


void MainWindow::updateN(){

    QString id = ui->id->text();
    QString title = ui->titre->text();
    QString i = Note::createID(title, id.right(1).toInt());
    QString  datec;
    datec = ui->dc->dateTime().toString();

    tm* DC = Note::dateFromQString(datec);
    //cout<<"year "<<DC->tm_year<<endl;
    time_t ti = time(0);
    struct tm * now = localtime( & ti );
    switch(ind){
    case 1:{
        QString t = ui->text->toPlainText();

        Article* a = new Article(i, title, DC, now,  active, t);
        nv->updateNewVersion(a);
        break;
    }
    case 2:{
        QString act = ui->prop1->text();
        QString s = ui->prop4->text();
        TaskStatus ts = Task::toTSfromQString(s);
        Task* t;
        if(nv->getType()==TWP){
            QString p = ui->prop2->text();
            t = new TaskWithPriority(i, title, DC, now,  active, act, ts, p.toInt());
        }
        else if(nv->getType()==TWD){
            QString d = ui->dm->dateTime().toString(DATEFORMAT);
            tm* dl = Note::dateFromQString(d);
             t = new TaskWithDeadline(i,title,DC, now,  active, act, ts, dl);
        }
        else{

             t= new Task(i, title, DC, now,  active, act, ts);

        }
        nv->updateNewVersion(t);

        break;
    }
    case 3:{
        QString desc = ui->prop1->text();
        //QString fn = ui->prop2->text();
        //QString dir = ui->directoryFile->selec
        OtherNote* on = new OtherNote(i,title,DC,now,  active, desc, dir, OtherNoteType::audio);
        nv->updateNewVersion(on);
        break;
    }
    }
    Reference& ref = Reference::getRef();
    ref.getReferences();
    emit modify();

}

void MainWindow::updateAff(){

    ui->listTask->setRowCount(0);
    ui->ListNotes->clear();
    ui->listArchived->clear();
    initialisationNA();
    initialisationT();
    try{
        initialisationArchive();
    } catch (NotesException e) {
        cout<<e.getInfo()<<endl;
    }

}

// TO DELETE LATER ? (NOT USED)
void MainWindow::archive(){
    for(NoteVersions::iterator it = nv->getIterator() ; !it.isDone() ; it.isNext())
        it.current().setNoteStatus(archived);
    updateAff();
}

void MainWindow::delete2(){
    // TO DO (work mais seulement si on sélectionne une note d'abord)
    for(NoteVersions::iterator it = nv->getIterator() ; !it.isDone() ; it.isNext()){
        try{
            manager2.deleteNoteVersions(&it.current());
        } catch(NotesException e) {
            cout<< e.getInfo()<<endl;
        }

    }
    updateAff();
}

void MainWindow::chooseFile(){
    QString dF = QFileDialog::getOpenFileName();
    dir = dF;
    //cout<<dir<<endl;
}


void MainWindow::restore(){
    nv->restoreVersion(n);
    updateAff();
}

void  MainWindow::goToTrash(){

    TrashViewer* newWindow = new TrashViewer(1);
    mediator->registerC(newWindow);
    newWindow->initialisationTrash();
    newWindow->show();
}

void  MainWindow::goToRelation(){
    //cout<<"gotorelation"<<endl;
    RelationViewer* newWindow = new RelationViewer(2);
    //cout<<"gotorelation"<<endl;

    mediator->registerC(newWindow);
    //cout<<"gotorelation"<<endl;
    newWindow->initialisation();
    //cout<<"gotorelation"<<endl;
    newWindow->show();

}


void MainWindow::emptyTrash(){
    NoteManager& nm = NoteManager::getNoteManager();
    for(NoteManager::iterator it = nm.getIterator();!it.isDone();it.isNext()){
        NoteVersions& nv = it.current();
        if(&nv != nullptr){
            Note& nc=nv.getIterator().current();
            if(nc.getNoteStatus()==NoteStatus::trash){
                nm.removeNV(nv);
            }
        }
    }
}
