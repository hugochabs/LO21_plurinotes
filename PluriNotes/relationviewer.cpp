#include "relationviewer.h"
#include "ui_relationviewer.h"

RelationViewer::RelationViewer(unsigned int i, QWidget *parent) :
    Widget(i),
    QDialog(parent),
    ui(new Ui::RelationViewer), r(0)
{
    ui->setupUi(this);
    setWindowTitle(tr("Ensemble des relations"));
    ui->listRelation->setColumnCount(2);
    QStringList labels;
    labels<<"Titre"<<"Orientation";
    ui->listRelation->setHeaderLabels(labels);

    setModal(true);

    connect(ui->quit, SIGNAL(clicked()), this, SLOT(quit()));
    connect(ui->listRelation, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(affichage(QTreeWidgetItem*,int)));

   //connect(ui->create, SIGNAL(clicked()), this, SLOT());
}

RelationViewer::~RelationViewer()
{
    delete ui;
}



void RelationViewer::addChild(QTreeWidgetItem* parent, QString label){
    QTreeWidgetItem* couple = new QTreeWidgetItem();
    couple->setText(0, label);
    parent->addChild(couple);
}

RelationManager& rm = RelationManager::getRelationManager();

void RelationViewer::initialisation(){
    for(RelationManager::iterator it = rm.getIterator();!it.isDone(); it.isNext()){
        Relation& r = it.current();
        QTreeWidgetItem* p = MainWindow::addRoot(ui->listRelation, r.getTitle(), r.getOrientationQS());
        for(Relation::iterator it2 = r.getIterator() ; !it2.isDone() ; it2.isNext()){
            addChild(p, it2.current().getLabel());
        }
    }
}

void RelationViewer::quit(){
    mediator->distributeMessage(this, "salut");
    close();
}

void RelationViewer::affichage(QTreeWidgetItem* item, int i){
    QString title = item->text(0);
    for(RelationManager::iterator it = rm.getIterator();!it.isDone();it.isNext()){
        if(it.current().getTitle()==title){
            fillRelation(it.current());
        }
    }
}

void RelationViewer::fillRelation(Relation& r){
    ui->title->setText(r.getTitle());
    ui->description->setText(r.getDescription());
}
