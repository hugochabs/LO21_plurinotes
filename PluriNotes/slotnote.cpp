#include "mainwindow.h"
#include "ui_mainwindow.h"


NoteManager& manager2 = NoteManager::getNoteManager();

//! SLOT : Connecté au signal, itemClicked(), permet d'afficher sur la note actie sélectionnée
void MainWindow::affichage(QTreeWidgetItem* item, int i){
    QString id = item->text(i);
    for(NoteManager::iterator it = manager2.getIterator();!it.isDone();it.isNext()){
        NoteVersions& nvt = it.current();
        cout<<"for1"<<endl;
        for(NoteVersions::iterator it2=nvt.getIterator();!it2.isDone(); it2.isNext()){
        cout<<"for1"<<endl;
             Note& temp = it2.current();
             if(id==temp.getIdentifier()){
                 cout<<"id temp"<<endl;
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
        ui->directoryFile->setVisible(false);

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
        ui->directoryFile->setVisible(false);

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
        //ui->prop2->setVisible(true);
        ui->directoryFile->setVisible(true);

        ui->prop3L->setVisible(false);
        ui->prop3->setVisible(false);


        ui->prop4L->setVisible(true);
        ui->prop4L->setText("Type");
        ui->typeON->setVisible(true);

        ui->prop4->setVisible(false);

        //save->setVisible(true);
       ind=3;
    }
}

time_t ti = time(0);
struct tm * now = localtime( & ti );

void MainWindow::update(){
    cout<<"update"<<endl;
    QString i = ui->id->text();
    QString title = ui->titre->text();
    QString * dc = new QString;
    *dc = ui->dc->text();
//    QString dc = ui->dc->text();
    tm* DC = Note::dateFromQString(*dc);
    switch(ind){
    case 1:{
        QString t = ui->text->toPlainText();
        time_t ti = time(0);
        struct tm * now = localtime( & ti );
        Article* a = new Article(i+"nv", title, DC, now,  active, t);
        nv->updateNewVersion(a);
        break;
    }
    case 2:{
        QString act = ui->prop1->text();
        QString s = ui->prop4->text();
        TaskStatus ts = Task::toTSfromQString(s);
        Task* t;
        if(ui->prop2->isModified()){
            QString p = ui->prop2->text();
            t = new TaskWithPriority(i, title, DC, now,  active, act, ts, p.toInt());
        }
        else if(ui->prop3->isModified()){
            tm* dl = Note::dateFromQString(ui->prop3->text());
             t = new TaskWithDeadline(i,title,DC, now,  active, act, ts, dl);
        }
        else{

             t= new Task(i, title, DC, now,  active, act, ts);

        }
        nv->updateNewVersion(t);
        cout<<"apres maj"<<endl;
        break;
    }
    case 3:{
        QString desc = ui->prop1->text();
        QString fn = ui->prop2->text();
        OtherNote* on = new OtherNote(i,title,DC,now,  active, desc, fn, OtherNoteType::audio);
        nv->updateNewVersion(on);
        break;
    }
    }
    emit modify();

}



void MainWindow::updateAff(){
    cout<<"reinitialisaion"<<endl;
    ui->listTask->setRowCount(0);
    ui->ListNotes->clear();
    initialisationNA();
    initialisationT();
}

void MainWindow::archive(){
    for(NoteVersions::iterator it = nv->getIterator() ; !it.isDone();it.isNext())
        it.current().setNoteStatus(archived);
    updateAff();
}

void MainWindow::chooseFile(){
    QFileDialog* file = new QFileDialog;
    file->show();
}

void MainWindow::restore(){
    cout<<"restore"<<endl;
    nv->restoreVersion(n);
    updateAff();
}
