#include "relation.h"
#include "mainwindow.h"
#include <QApplication>

int main (int argc, char *argv[]){
    QString * path = new QString;
    *path = "/home/guilllaume/DATA/";
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    NoteStatus act = active;
    //création de deux articles
    Article A("ID-A", "Titre Article A", now, now, act, "Texte A");
    Article B("ID-B", "Titre Article B", now, now, act, "Texte B");
    //création de deux task
    Task T("ID-T", "Titre Task", now, now, act, "Action Task", doing);
    Task T2("ID-T2", "Titre Task 2", now, now, act, "Action Task 2", done);
    //ajout des tasks dans NV que l'on crée
    Note ** tab = new Note*[0];
    NoteVersions NV(tab,0,0, NoteType::T);
    NV.addNote(&T);
    NV.addNote(&T2);
    //pareil ici
    NoteVersions NV2(tab,0,0, NoteType::A);
    NV2.addNote(&B);
    NV2.addNote(&A);

    /*NoteVersions::iterator it = NV2.getIterator();
    Note &n = it.current();
    Article &art = static_cast<Article&>(n);
    QString text = art.getText();
    cout<<"ESSAI text"<<endl;
    cout << text <<endl;*/

    NoteManager& NM = NoteManager::getNoteManager();
    NM.addNoteVersion(&NV);
    NM.addNoteVersion(&NV2);

    //création d'une relation
    Relation R;
    //création de deux couples
    Couple* c = new Couple("label", &A, &T);
    Couple* c2 = new Couple("label2", &T, &B);
    //paramétrage de la relation
    R.setTitle("Titre");
    //ajout des couples
    R.addCouple(c);
    R.addCouple(c2);

    //création d'un tableau de relations et d'un RM
    Relation** tabRel = new Relation*[5];
    RelationManager& RM = RelationManager::getRelationManager(tabRel, 0, 5);
    //Ajout des relations
    RM.addRelation(&R);
    RM.addRelation(&R);
    //Affichage des relations dans lesquelles A est impliquée
    //cout<<getRelations(&A);

    NV.updateNewVersion(&T2);
    NV.updateNewVersion(&T2);
    //cout<<NV;
    NV.restoreVersion(&T);
    //cout<<"///////////////////////////////////////////"<<endl<<NV;
    cout<<NM.toJson();
    NM.save();
    NoteManager& NM2 = NoteManager::getNoteManager();
    NM2.load();
    cout<<NM2;

    QApplication a(argc, argv);
    MainWindow w;
    w.initialisationNA(NM);
    w.initialisationT(NM);

    w.show();

    return a.exec();
}

