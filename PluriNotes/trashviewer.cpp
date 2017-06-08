#include "trashviewer.h"
#include "ui_trashviewer.h"

TrashViewer::TrashViewer(unsigned int i, QWidget *parent) :
    QDialog(parent),
    Widget(i),
    ui(new Ui::TrashViewer)
{
    ui->setupUi(this);
    setWindowTitle(tr("Corbeille"));
    ui->listTrash->setColumnCount(2);

    connect(ui->quit, SIGNAL(clicked()), this, SLOT(quit()));
}

TrashViewer::~TrashViewer()
{
    delete ui;
}

NoteManager& manager = NoteManager::getNoteManager();

void TrashViewer::initialisationTrash(){
    for(NoteManager::iterator it = manager.getIterator() ;!it.isDone();it.isNext()){
        NoteVersions nv = it.current();
        NoteVersions::iterator it2 = nv.getIterator();
        Note n = it2.current();

        QTreeWidgetItem* note1;
        if(n.getNoteStatus()==trash){
            note1 = addRoot(ui->listTrash, n.getIdentifier(), nv.getTypeQS());
            for(NoteVersions::iterator it2=nv.getIterator1();!it2.isDone(); it2.isNext()){
                 Note temp = it2.current();
                 addChild(note1, temp.getIdentifier(), nv.getTypeQS());
             }
        }
    }
}

QTreeWidgetItem* TrashViewer::addRoot(QTreeWidget* parent, QString id, QString type){
    QTreeWidgetItem* note = new QTreeWidgetItem(parent);
    note->setText(0, id);
    note->setText(1, type);
    parent->addTopLevelItem(note);
    return note;
}

void TrashViewer::addChild(QTreeWidgetItem* parent, QString title,QString type){
    QTreeWidgetItem* note = new QTreeWidgetItem();
    cout<<"enfant"<<endl;
    note->setText(0, title);
    note->setText(1, type);
    parent->addChild(note);
}

void TrashViewer::quit(){
    mediator->distributeMessage(this, "salut");
    close();
}
