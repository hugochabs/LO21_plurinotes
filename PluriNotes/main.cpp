#include "plurinotes.h"






int main (){

    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    bool act = false;
    Article A("2000", "titre", now, now, act, "texte");
    Article B("1616", "Titre2", now, now, act, "Texte2");
    Task T("2000", "titre", now, now, act, "Action", doing);
    Task T2("1856", "titre2", now, now, act, "Action16", done);
    Note ** tabA = new Note*[5];
    tabA[0] = &A;
    tabA[1] = &A;
    NoteVersions NV(tabA, 2, 5); //Lors de la définition, il faut préciser le type de noteVersions qu'on crée.
    NoteVersions NV2;
    NV2.addNote(&B);
    NV2.addNote(&A);
    NoteVersions ** tabVers = new NoteVersions*[5];
    tabVers[0] = &NV;
    tabVers[1] = &NV2;
    NoteManager NM(tabVers, 2, 5);
    //NoteVersions<Article> NV; //on peut aussi utiliser le constructeur sans arguement.
    OtherNote ON("2000", "titre", now, now, act, "Description", "C:photos", image);
    /*
    cout<<A;
    cout<<"-------------------"<<endl;
    cout<<T;
    cout<<"-------------------"<<endl;
    cout<<ON;
    cout<<"-------------------"<<endl;

    cout<<NV;
    NV.addNote(&A);
    cout<<"-------------------"<<endl;
    cout<<NV;
    */
    Relation R;
    Couple* c = new Couple("label", &A, &T);
    Couple* c2 = new Couple("label2", &T, &B);
    R.addCouple(c);
    R.addCouple(c2);
    cout<<R;
    cout<<"-------------------"<<endl;
    cout<<NM;
    return 0;
}

