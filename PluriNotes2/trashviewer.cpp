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
    setModal(true);

    connect(ui->quit, SIGNAL(clicked()), this, SLOT(quit()));
    connect(ui->listTrash, SIGNAL(itemClicked(QTreeWidgetItem*,int)), this, SLOT(select(QTreeWidgetItem*,int)));
    connect(ui->restoreButton, SIGNAL(clicked(bool)), this, SLOT(restore()));
}

TrashViewer::~TrashViewer()
{
    delete ui;
}

NoteManager& manager = NoteManager::getNoteManager();

void TrashViewer::initialisationTrash(){
    cout<<"initialisation"<<endl;
    for(NoteManager::iterator it = manager.getIterator() ;!it.isDone();it.isNext()){
        NoteVersions nv = it.current();
        NoteVersions::iterator it2 = nv.getIterator();
        Note n = it2.current();
        QTreeWidgetItem* note1;
        if(n.getNoteStatus()==trash){   
            note1 = MainWindow::addRoot(ui->listTrash, n.getIdentifier(), nv.getTypeQS());
            it2.isNext();
            for(it2 ;!it2.isDone(); it2.isNext()){
                 Note temp = it2.current();
                 MainWindow::addChild(note1, temp.getIdentifier(), nv.getTypeQS());
             }
        }
    }
}

void TrashViewer::select(QTreeWidgetItem* item, int i){
    QString id = item->text(i);
    for(NoteManager::iterator it = manager.getIterator();!it.isDone();it.isNext()){
        NoteVersions& nvt = it.current();
        for(NoteVersions::iterator it2=nvt.getIterator();!it2.isDone(); it2.isNext()){
             Note& temp = it2.current();
             if(id==temp.getIdentifier()){
                 n=&temp;
                 nv=&nvt;
                 return ;

             }
         }

    }
}

void TrashViewer::restore(){
    cout<<"restore"<<endl;
    manager.restoreNoteVersions(nv);
    mediator->distributeMessage(this, "salut");
    ui->listTrash->clear();
    initialisationTrash();
}


void TrashViewer::quit(){
    mediator->distributeMessage(this, "salut");
    close();
}
