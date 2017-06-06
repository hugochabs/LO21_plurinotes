#include "trashviewer.h"
#include "ui_trashviewer.h"

TrashViewer::TrashViewer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrashViewer)
{
    ui->setupUi(this);
    setWindowTitle(tr("Corbeille"));

    connect(ui->quit, SIGNAL(clicked()), this, SLOT(close()));
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
