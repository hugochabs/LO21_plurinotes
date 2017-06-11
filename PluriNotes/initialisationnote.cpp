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

QTreeWidgetItem* MainWindow::addRootBis(QTreeWidget* parent, QString id){
    QTreeWidgetItem* note = new QTreeWidgetItem(parent);
    note->setText(0, id);
    parent->addTopLevelItem(note);
    return note;
}

void MainWindow::addChild(QTreeWidgetItem* parent, QString title,QString type){
    QTreeWidgetItem* note = new QTreeWidgetItem();
    note->setText(0, title);
    note->setText(1, type);
    parent->addChild(note);
}

QTreeWidgetItem* MainWindow::addChildBis(QTreeWidgetItem* parent, QString title){
    QTreeWidgetItem* note = new QTreeWidgetItem();
    note->setText(0, title);
    parent->addChild(note);
    return note;
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
                NoteVersions::iterator it2=nv.getIterator();
                it2.isNext();
                for(it2 ;!it2.isDone(); it2.isNext()){
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
            if(n.getNoteStatusString()=="active"){
                switch(nv.getType()){
                case NoteType::T :{

                        Task& t = static_cast<Task&>(n);

                        QTableWidgetItem* action = new QTableWidgetItem(t.Task::getAction());
                        ui->listTask->insertRow(ui->listTask->rowCount());
                        row = ui->listTask->rowCount()-1;
                        cout<<row<<endl;
                        ui->listTask->setItem(row,0, action);
                        break;}

                 case NoteType::TWD : {

                    TaskWithDeadline& t = static_cast<TaskWithDeadline&>(n);

                    QString date = Note::QStringFromDate(t.getDeadline());
                    QTableWidgetItem* action = new QTableWidgetItem(t.Task::getAction());
                    //QTableWidgetItem* id=new QTableWidgetItem(t.getIdentifier());
                    QTableWidgetItem* d=new QTableWidgetItem(date);

                    ui->listTask->insertRow(ui->listTask->rowCount());

                    row = ui->listTask->rowCount()-1;
                    cout<<row<<endl;
                    ui->listTask->setItem(row,0, action);
                    ui->listTask->setItem(row,1, d);
                    /*ui->listTask->setItem(row,2, status2);*/
                    break;}

                case NoteType::TWP : {

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
}

void MainWindow::initialisationArchive(){
    for(NoteManager::iterator it = manager1.getIterator();!it.isDone();it.isNext()){
            NoteVersions nv = it.current();
            NoteVersions::iterator it1 = nv.getIterator();
            Note n = it1.current();
            cout<<n<<endl;

            QTreeWidgetItem* note1;
            if(n.getNoteStatus() == NoteStatus::archived){
                 note1 = addRoot(ui->listArchived, n.getIdentifier(), nv.getTypeQS());
            }

    }
}


void MainWindow::setAffichage(NoteType nt, Note& n){
    RelationManager& rm = RelationManager::getRelationManager();
    map<Note*, int> asc = rm.getAscendants(&n);
    map<Note*, int> desc = rm.getDescendants(&n);
    addElementsInWidgets(asc, ui->ascendants);
    addElementsInWidgets(desc, ui->descendants);
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


void MainWindow::addElementsInWidgets(map<Note*, int>& N, QTreeWidget* widget){
    //on nettoie le widget
    widget->clear();
    //booléen pour savoir si au moins une racine à été ajoutée
    bool hasAtleastOneRoot = false;
    //Variables temporaires pour gérer l'arborescence (retour en arrière, fils, etc...)
    QTreeWidgetItem* beforelastParentAdded = nullptr;
    QTreeWidgetItem* lastParentAdded = nullptr;
    QTreeWidgetItem* lastChildAdded = nullptr;
    //profondeur actuelle
    int currentRank = 0;
    //On itère tant que le map n'est pas vide
    while(!N.empty()){
        //on parcourt tous les éléments
        for (auto it = N.begin() ; it != N.end() ; it++){
            //cas ou c'est une racine
            if(it->second == 0){
                lastParentAdded = addRootBis(widget, (it->first)->getIdentifier());
                N.erase(it);
                hasAtleastOneRoot = true;
                currentRank = 1;
            }else{
                //si il y a au moins une racine
                if(hasAtleastOneRoot){
                    //ajout du fils sur le rang en cours
                    if (it->second == currentRank){
                        lastChildAdded = addChildBis(lastParentAdded, (it->first)->getIdentifier());
                        N.erase(it);
                    //ajout du fils sur un rang supérieur
                    }else if (it->second > currentRank){
                        lastChildAdded = addChildBis(lastParentAdded, (it->first)->getIdentifier());
                        beforelastParentAdded = lastParentAdded;
                        lastParentAdded = lastChildAdded;
                        N.erase(it);
                        currentRank++;
                    //ajout du fils sur un rang inférieur
                    }else{
                        lastParentAdded = beforelastParentAdded;
                        lastChildAdded = addChildBis(lastParentAdded, (it->first)->getIdentifier());
                        N.erase(it);
                        currentRank--;
                    }
                }
            }
        }
    }
}



//!Fonctions qui permettent de remplir les champs de l'affichage principal
void MainWindow::fillNote(Note* n)const{

    ui->id->setText(n->getIdentifier());
    ui->titre->setText(n->getTitle());
    //QString dateC = Note::QStringFromDate(n->getDateCreation());
    //QString dateLU = Note::QStringFromDate(n->getDateLastUpdate());

    QDateTime dateC = *Note::QdatefromDate(n->getDateCreation());
    QDateTime dateLU = *Note::QdatefromDate(n->getDateLastUpdate());
    ui->dc->setDateTime(dateC);
    ui->dm->setDateTime(dateLU);
}


void MainWindow::fillA(Article& a)const{

    ui->text->setText(a.getText());
}

void MainWindow::fillT(Task& t)const{
    ui->prop1->setText(t.getAction());
    ui->prop4->setText(t.getStatusQS());
    ui->prop3->setReadOnly(true);
    ui->prop2->setReadOnly(true);
}

void MainWindow::fillTWD(TaskWithDeadline &t)const{
    fillT(t);
    QDateTime dateC = *Note::QdatefromDate(t.getDeadline());
    ui->prop3->setReadOnly(true);
    ui->dm->setDateTime(dateC);
    ui->prop2->setReadOnly(true);
}

void MainWindow::fillTWP(TaskWithPriority& t)const{
    fillT(t);
    ui->prop2->setReadOnly(true);
    ui->prop2->setText(t.getPriorityQS());
    ui->prop3->setReadOnly(true);
}

void MainWindow::fillON(OtherNote& on)const{
    ui->prop1->setText(on.getDescription());
    //ui->prop2->setText(on.getFileName());
}


