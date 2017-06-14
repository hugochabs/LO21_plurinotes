#include "createrelation.h"
#include "ui_createrelation.h"

CreateRelation::CreateRelation(unsigned int i, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateRelation), Widget(i)
{
    mediator = &Mediator::getMediator();
    ui->setupUi(this);
    setWindowTitle(tr("Ajouter une relation"));
    ui->ok->setEnabled(false);
    setModal(true);

    connect(ui->title, SIGNAL(textChanged(QString)), this, SLOT(activeOK()));
    connect(ui->ok, SIGNAL(clicked(bool)), this, SLOT(addRelation()));
}

CreateRelation::~CreateRelation()
{
    delete ui;
}

RelationManager& rm1 = RelationManager::getRelationManager();

void CreateRelation::activeOK(){
    ui->ok->setEnabled(true);
}

void CreateRelation::addRelation(){
    QString t = ui->title->text();
    QString d = ui->description->toPlainText();
    Relation* newR = new Relation;
    newR->setTitle(t);
    newR->setDescription(d);
    rm1.addRelation(newR);
    sendMessage("Relation ajoutee avec succes");
    AlertViewer* newAV = new AlertViewer("Confirmation", "Votre relation a été ajoutée avec succès");
    newAV->exec();
    close();
}

NoteManager& nm2 = NoteManager::getNoteManager();

EnrichRelation::EnrichRelation(unsigned int i, Relation* rel, QWidget *parent): Widget(i), r(rel){
    mediator = &Mediator::getMediator();

    label = new QLabel("Label");
    note1 = new QLabel("Note X");
    note2 = new QLabel("Note Y");
    labelEdit = new QLineEdit;
//    note1Edit = new QLineEdit;
//    note2Edit = new QLineEdit;
    choice1 = new QComboBox;
    choice2 = new QComboBox;
    labels = new QHBoxLayout;
    noteX = new QHBoxLayout;
    noteY = new QHBoxLayout;
    buttons= new QHBoxLayout;
    vertical = new QVBoxLayout;
    cancel = new QPushButton("Annuler");
    ok = new QPushButton("Valider");

    labels->addWidget(label);
    labels->addWidget(labelEdit);
    noteX->addWidget(note1);
    noteX->addWidget(choice1);
    noteY->addWidget(note2);
    noteY->addWidget(choice2);
    buttons->addWidget(cancel);
    buttons->addWidget(ok);

    vertical->addLayout(labels);
    vertical->addLayout(noteX);
    vertical->addLayout(noteY);
    vertical->addLayout(buttons);

    for(NoteManager::iterator it=nm2.getIterator(); !it.isDone(); it.isNext()){
        NoteVersions nv = it.current();
        Note n = nv.getIterator().current();
        choice1->addItem(n.getIdentifier());
        choice2->addItem(n.getIdentifier());
    }


    setWindowTitle(tr("Enrichir une relation"));
    setModal(true);
    ok->setEnabled(false);
    setLayout(vertical);

    connect(ok, SIGNAL(clicked(bool)), this, SLOT(addC()));
    connect(labelEdit, SIGNAL(textChanged(QString)), this, SLOT(activeOK()));
    //connect(choice1, SIGNAL(activated(int)), this, SLOT(activeOK()));
    //connect(labelEdit, SIGNAL(textChanged(QString)), this, SLOT(activeOK()));
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(close()));
}


RelationManager& rm2 = RelationManager::getRelationManager();

void EnrichRelation::activeOK(){
    ok->setEnabled(true);
}

void EnrichRelation::addC(){
    QString l = labelEdit->text();
    QString n1 = choice1->currentText();
    QString n2 = choice2->currentText();
    Note* nx = NoteManager::searchNote(n1);
    Note* ny = NoteManager::searchNote(n2);
    cout<<nx->getIdentifier()<<endl;
    cout<<ny->getIdentifier()<<endl;

    Couple* newCouple = new Couple(l, nx, ny);
    r->addCouple(newCouple);
    sendMessage("Couple bien ajoutee");
    close();
}
