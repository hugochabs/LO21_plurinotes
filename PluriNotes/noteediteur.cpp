#include "noteediteur.h"

/*QApplication app(int n, char** argv);
MainWindow& mymw = MainWindow::getMainWindow();*/

Mediator& med = Mediator::getMediator();

NoteEditeur::NoteEditeur( unsigned int i,QWidget* parent): QDialog(parent), Widget(i){

    setWhatsThis("Pour ajouter une note, veuillez sélectionner le type de note. Ensuite rentrez les différentes informations");

    //!Bouton pour choisir le type de note

    task = new QRadioButton("Task", this);
    article = new QRadioButton("Article", this);
    other = new QRadioButton("Other", this);
    layouthbutton = new QHBoxLayout;

    layouthbutton->addWidget(task);
    layouthbutton->addWidget(article);
    layouthbutton->addWidget(other);



    layoutv = new QVBoxLayout;

    layouth2 = new QHBoxLayout;
    layouth3 = new QHBoxLayout;

    //Propriété de note

    titre1 = new QLabel("Titre");
    titre = new QLineEdit;

    //propriété de Notefille
    ind=-1; ind2 = -1;
    prop1L = new QLabel;
    prop1 = new QLineEdit;
    art = new QTextEdit;
    prop2L = new QLabel;
    prop2 = new QLineEdit;
    prop3L = new QLabel;
    prop3 = new QLineEdit;
    prop4L = new QLabel;
    prop4 = new QLineEdit;

    twd = new QRadioButton;
    twp = new QRadioButton;

    selectType = new QButtonGroup;
    selectOption = new QButtonGroup;

    dl = new QDateTimeEdit;
    dl->setCalendarPopup(true);

    selectType->addButton(task);
    selectType->addButton(article);
    selectType->addButton(other);

    selectOption->addButton(twp);
    selectOption->addButton(twd);


    menu = new QComboBox;
    menu->addItem("Audio");
    menu->addItem("Vidéo");
    menu->addItem("Image");

    prop1L->setVisible(false);
    prop1->setVisible(false);
    art->setVisible(false);
    prop2->setVisible(false);
    prop2->setVisible(false);
    prop3L->setVisible(false);
    prop3->setVisible(false);
    dl->setVisible(false);
    prop4L->setVisible(false);
    prop4->setVisible(false);
    twp->setVisible(false);
    twd->setVisible(false);
    menu->setVisible(false);

    layout1 = new QHBoxLayout;
    layout2 = new QHBoxLayout;
    layout3 = new QHBoxLayout;
    layout4 = new QHBoxLayout;
    layout1->addWidget(prop1L);
    layout1->addWidget(prop1);
    layout1->addWidget(art);
    layout2->addWidget(prop2L);
    layout2->addWidget(prop2);
    layout2->addWidget(twp);
    layout3->addWidget(prop3L);
    layout3->addWidget(prop3);
    layout3->addWidget(dl);
    layout3->addWidget(twd);
    layout3->addWidget(menu);
    layout4->addWidget(prop4L);
    layout4->addWidget(prop4);


    //Bouton de save et quit
    save = new QPushButton("Sauvegarder", this);
    save->setEnabled(false);
    save->setVisible(false);

    quit = new QPushButton("Quitter", this);


    layouth2->addWidget(titre1);


    layouth2->addWidget(titre);

    layoutv->addLayout(layouthbutton);
    layoutv->addLayout(layouth2);
    layoutv->addLayout(layout1);
    layoutv->addLayout(layout2);
    layoutv->addLayout(layout3);
    layoutv->addLayout(layout4);
    //layoutv->addLayout(layouth3);
    layoutv->addWidget(save);
    layoutv->addWidget(quit);
    setLayout(layoutv);
    setWindowTitle(tr("Ajout d'une note"));
    setModal(true);

    //connexion des différents boutons
    connect(quit, SIGNAL(clicked()),this, SLOT(close()));
    connect(task, SIGNAL(clicked(bool)), this, SLOT(changeTask()));
    connect(article, SIGNAL(clicked(bool)), this, SLOT(changeArticle()));
    //connect(note, SIGNAL(clicked(bool)), this, SLOT(changeNote()));
    connect(other, SIGNAL(clicked(bool)), this, SLOT(changeOther()));
    connect(titre, SIGNAL(textChanged(QString)), this, SLOT(activerSave()));
    connect(save, SIGNAL(clicked()), this, SLOT(addN()));
    connect(twd, SIGNAL(clicked()), this, SLOT(activeDeadline()));
    connect(twp, SIGNAL(clicked()), this, SLOT(activePriority()));

}

void NoteEditeur::activerSave(){
    save->setEnabled(true);
}




void NoteEditeur::changeTask(){
    if(ind!=1){
        prop1L->setVisible(true);
        prop1L->setText("Action");
        prop1->setVisible(true);
        art->setVisible(false);

        prop2L->setVisible(true);
        prop2L->setText("Priority");
        prop2->setVisible(true);

        prop3L->setVisible(true);
        prop3L->setText("Deadline");
        prop3->setVisible(false);
        dl->setVisible(true);
        menu->setVisible(false);

        prop4L->setVisible(true);
        prop4L->setText("Status");
        prop4->setVisible(true);

        twd->setVisible(true);
        twp->setVisible(true);

        save->setVisible(true);
        ind=1;
    }
}

void NoteEditeur::changeArticle(){
      if(ind!=2){
        prop1L->setVisible(true);
        prop1L->setText("Text");
        prop1->setVisible(false);
        art->setVisible(true);

        prop2L->setVisible(false);
        prop2->setVisible(false);

        prop3L->setVisible(false);
        prop3->setVisible(false);
        menu->setVisible(false);
        dl->setVisible(false);

        prop4L->setVisible(false);
        prop4->setVisible(false);

        twd->setVisible(false);
        twp->setVisible(false);

        save->setVisible(true);
        ind=2;
      }
}



void NoteEditeur::changeOther(){
      if(ind!=3){
          prop1L->setVisible(true);
          prop1L->setText("Description");
          prop1->setVisible(true);
          art->setVisible(false);

          prop2L->setVisible(true);
          prop2L->setText("filename");
          prop2->setVisible(true);

          prop3L->setVisible(true);
          prop3L->setText("Type");
          prop3->setVisible(false);
          menu->setVisible(true);
          dl->setVisible(false);

          prop4L->setVisible(false);
          prop4->setVisible(false);

          twd->setVisible(false);
          twp->setVisible(false);

          save->setVisible(true);
          ind=3;
      }
}

void NoteEditeur::activeDeadline(){
    ind2 = 1;
}
void NoteEditeur::activePriority(){
    ind2 = 2;
}


NoteManager& nm = NoteManager::getNoteManager();
void NoteEditeur::addN(){
    time_t t = time(0);   // get time now
    struct tm * now1 = localtime( & t );

    QString titleN = titre->text();
    QString idN = Note::createID(titleN, 0);
    NoteVersions* nv = new NoteVersions(new Note*[0], 0,0);
    if(ind==2){
        Article* a = new Article(idN, titleN, now1, now1, active, art->toPlainText());
        nv->updateNewVersion(a);
    }
    else if(ind==1){
        nv->setNoteType(NoteType::T);
        QString action = prop1->text();
        Task* t = new Task(idN, titleN, now1, now1, active, action, waiting);
        if(ind2==1){
            nv->setNoteType(NoteType::TWD);
            QString d = dl->dateTime().toString(DATEFORMAT);
            tm* date = Note::dateFromQString(d);
            t = new TaskWithDeadline(idN, titleN, now1, now1, active, action, waiting, date);
        }
        else if(ind2==2){
            nv->setNoteType(NoteType::TWP);
            unsigned int prio = prop2->text().toInt();
            t = new TaskWithPriority(idN, titleN, now1, now1, active, action, waiting, prio);
        }
        nv->updateNewVersion(t);

    }
    else if(ind==3){
        nv->setNoteType(ON);
        QString desc = prop1->text();
        QString type = menu->currentText();
        QString fn = prop2->text();
        OtherNoteType t = OtherNote::toONTFromQString(type);
        OtherNote* on = new OtherNote(idN, titleN, now1, now1,  active, desc, fn, t);
        nv->updateNewVersion(on);
    }
    nm.addNoteVersion(nv);    
    mediator->distributeMessage(this, "salut");
    AlertViewer* alert = new AlertViewer("Confirmation", "Votre note a bien ajoutée");
    alert->exec();
    close();
}
