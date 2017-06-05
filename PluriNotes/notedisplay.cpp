#include "mainwindow.h"
#include "ui_mainwindow.h"

NoteManager& manager = NoteManager::getNoteManager();

int n =manager.getNb();

//!Fonctions qui permet d'ajouter les notes présentes dans NoteManager
QTreeWidgetItem* MainWindow::addRoot(QString id, QString type){
    QTreeWidgetItem* note = new QTreeWidgetItem(ui->ListNotes);
    note->setText(0, id);
    note->setText(1, type);
    ui->ListNotes->addTopLevelItem(note);
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
    for(NoteManager::iterator it = manager.getIterator();!it.isDone();it.isNext()){
            NoteVersions nv = it.current();
            NoteVersions::iterator it1 = nv.getIterator();
            Note n = it1.current();

            QTreeWidgetItem* note1;
            if(n.getNoteStatusString()=="active"){
                 note1 = addRoot(n.getIdentifier(), nv.getTypeQS());
                for(NoteVersions::iterator it2=nv.getIterator1();!it2.isDone(); it2.isNext()){
                     Note temp = it2.current();
                     addChild(note1, temp.getIdentifier(), nv.getTypeQS());
                 }
            }

    }

}

void MainWindow::initialisationT(){
    //unsigned int i=1;
    for(NoteManager::iterator it = manager.NoteManager::getIterator();!it.isDone();it.isNext()){
            NoteVersions nv = it.current();
            NoteVersions::iterator it1 = nv.NoteVersions::getIterator();
            Note& n = it1.current();
            int row;
            cout<<nv.getTypeQS()<<endl;
            cout<<it.getNbRemain()<<endl;
            cout<<manager.getNb()<<endl;
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
    for(NoteManager::iterator it = manager.getIterator();!it.isDone();it.isNext()){
            NoteVersions nv = it.current();
            NoteVersions::iterator it1 = nv.getIterator();
            Note n = it1.current();

            QTreeWidgetItem* note1;
            if(n.getNoteStatusString()=="active"){
                 note1 = addRoot(n.getIdentifier(), nv.getTypeQS());
                for(NoteVersions::iterator it2=nv.getIterator1();!it2.isDone(); it2.isNext()){
                     Note temp = it2.current();
                     addChild(note1, temp.getIdentifier(), nv.getTypeQS());
                 }
            }

    }
}



//! SLOT : Connecté au signal, itemClicked(), permet d'afficher sur la note actie sélectionnée
void MainWindow::affichage(QTreeWidgetItem* item, int i){
    QString id = item->text(i);
    for(NoteManager::iterator it = manager.getIterator();!it.isDone();it.isNext()){
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

//void MainWindow::afficherItem()
//MainWindow& mw = MainWindow::getMainWindow();

time_t ti = time(0);
struct tm * now = localtime( & ti );

void MainWindow::update(){
    cout<<"update"<<endl;
    QString i = ui->id->text();
    QString title = ui->titre->text();
    QString dc = ui->dc->text();
    tm* DC = Note::dateFromQString(dc);
    switch(ind){
    case 1:{
        QString t = ui->text->toPlainText();
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
