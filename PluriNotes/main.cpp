#include "relation.h"

int main (){
    //tm* now = tm*::currentDateTime();
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    bool act = false;
    //création de deux articles
    Article A("ID-A", "Titre Article A", now, now, act, "Texte A");
    Article B("ID-B", "Titre Article B", now, now, act, "Texte B");
    //création de deux task
    Task T("ID-T", "Titre Task", now, now, act, "Action Task", doing);
    Task T2("ID-T2", "Titre Task 2", now, now, act, "Action Task 2", done);
    //ajout des tasks dans NV que l'on crée
    NoteVersions NV;
    NV.addNote(&T);
    NV.addNote(&T2);
    //pareil ici
    NoteVersions NV2;
    NV2.addNote(&B);
    NV2.addNote(&A);
    //création d'un tableau de NV
    NoteManager NM("C:\\Users\\Public\\");
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
    return 0;
}

