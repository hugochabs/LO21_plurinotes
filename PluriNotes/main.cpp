#include "relation.h"
#include "mainwindow.h"
#include <QApplication>
#include "colleague.h"
#include <QTextCodec>


int main (int argc, char *argv[]){
    //!Ces codecs permettent d'afficher les accents dans les fenêtres
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    /*
    QString * path = new QString;
    *path = "/home/guilllaume/DATA/";
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    NoteStatus act = active;
    //création de deux articles
    Article A("ID-A", "Titre Article A", now, now, act, "Texte A");
    Article B("ID-B", "Titre Article B", now, now, act, "Texte B");
    Article Z("ID-Z", "Titre \\ref{ID-B} Article Z", now, now, act, "Texte\\ref{ID-T} Z");
    //création de deux task
    Task T("ID-T", "Titre Task", now, now, act, "Action Task", doing);
    Task T2("ID-T2", "Titre Task 2", now, now, act, "Action Task 2", done);

    //Création de OotherNote
    OtherNote On1("ID-ON1", "Test1", now, now, act, "petite description", "filename", audio);
    OtherNote On2("ID-ON2", "Test2", now, now, act, "petite description", "filename2", video);

    //création de taskwithdeadline
    TaskWithDeadline twd1("ID-TWD1", "taskwithdeadline", now, now, trash,"action twd", waiting, now);
    TaskWithDeadline twd2("ID-TWD2", "taskwithdeadline", now, now, trash, "Action twd", waiting, now);

    TaskWithPriority twp1("ID-TWP1", "taskwithpriority", now, now, NoteStatus::archived,"action twp", waiting,56);
    TaskWithPriority twp2("ID-TWP2", "taskwithpriority", now, now,NoteStatus::archived, "Action twp", waiting,52);
    //ajout des tasks dans NV que l'on crée
    Note ** tab = new Note*[0];
    NoteVersions NV(tab,0,0, NoteType::T);
    NV.addNote(&T);
    NV.addNote(&T2);
    //pareil ici
    NoteVersions NV2(tab,0,0, NoteType::A);
    NV2.addNote(&B);
    NV2.addNote(&A);
    NV2.addNote(&Z);
    NoteVersions NV3(tab,0,0, NoteType::TWD);
    NV3.addNote(&twd1);
    NV3.addNote(&twd2);

    NoteVersions NV4(tab,0,0, NoteType::TWP);
    NV4.addNote(&twp1);
    NV4.addNote(&twp2);

    NoteVersions NV5(tab,0,0, NoteType::ON);
    NV5.addNote(&On1);
    NV5.addNote(&On2);


    NoteManager& NM = NoteManager::getNoteManager();
    NM.addNoteVersion(&NV);
    NM.addNoteVersion(&NV2);
    NM.addNoteVersion(&NV3);
    NM.addNoteVersion(&NV4);
    NM.addNoteVersion(&NV5);
    cout<<NM.getNb()<<endl;

    //création d'une relation
    Relation R;
    //création de deux couples
    Couple* c = new Couple("label", &A, &T);
    Couple* c2 = new Couple("label2", &T, &B);
    Couple* c3 = new Couple("label3", &Z, &A);
    Couple* c4 = new Couple("label4", &B, &A);
    Couple* c5 = new Couple("label5", &B, &T);
    //paramétrage de la relation
    R.setTitle("Titre");
    R.setDescription("Relation qui joint les deux notes lde l'espace");
    //ajout des couples
    R.addCouple(c);
    R.addCouple(c2);
    R.addCouple(c3);
    R.addCouple(c4);
    R.addCouple(c5);

    //création d'un tableau de relations et d'un RM
    Relation** tabRel = new Relation*[5];
    RelationManager& RM = RelationManager::getRelationManager(tabRel, 0, 5);
    //Ajout des relations
    RM.addRelation(&R);

    NV.updateNewVersion(&T2);
    NV.updateNewVersion(&T2);

    NV.restoreVersion(&T);

    NM.save();
    NoteManager& NM2 = NoteManager::getNoteManager();
    //NM2.load();
    cout<<NM2.getNb()<<endl;
    //cout<<NM2;
    */
    NoteManager& NM = NoteManager::getNoteManager();
    cout<<"debug"<<endl;
    NM.load();

    QApplication a(argc, argv);
    MainWindow w(0);
    w.initialisationNA();
    w.initialisationT();
    w.initialisationArchive();

    w.show();


    //Note * RZ = Z.getReferences();
    //cout<<"a"<<endl;
    //cout<<RZ[0]<<endl;

    Mediator& mediator = Mediator::getMediator();

    mediator.registerC(&w);



    /*
    Reference& Ref = Reference::getRef();
    Ref.getReferences();
    bool referenced = Reference::isNoteReferenced(&B);
    cout<<referenced;
    */
    return a.exec();


}

