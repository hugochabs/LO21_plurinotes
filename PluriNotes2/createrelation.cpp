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
    AlertViewer* newAV = new AlertViewer("Confirmation", "Vtre relation a été ajoutée avec succès");
    newAV->exec();
    close();
}

EnrichRelation::EnrichRelation(unsigned int i, QWidget *parent): Widget(i){
    mediator = &Mediator::getMediator();

    label = new QLabel("Label");
    note1 = new QLabel("Note X");
    note2 = new QLabel("Note Y");
    labelEdit = new QLineEdit;
    note1Edit = new QLineEdit;
    note2Edit = new QLineEdit;
    cancel = new QPushButton("Annuler");
    ok = new QPushButton("Valider");
    setWindowTitle(tr("Enrichir une relation"));
    setModal(true);
    ok->setEnabled(false);

    //connect(ok, S)
}
