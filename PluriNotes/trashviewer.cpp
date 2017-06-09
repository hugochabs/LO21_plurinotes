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
            note1 = MainWindow::addRoot(ui->listTrash, n.getIdentifier(), nv.getTypeQS());
            for(NoteVersions::iterator it2=nv.getIterator1();!it2.isDone(); it2.isNext()){
                 Note temp = it2.current();
                 MainWindow::addChild(note1, temp.getIdentifier(), nv.getTypeQS());
             }
        }
    }
}



void TrashViewer::quit(){
    mediator->distributeMessage(this, "salut");
    close();
}
