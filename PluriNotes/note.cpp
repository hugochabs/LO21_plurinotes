#include "notefille.h"

using namespace std;

NoteManager * NoteManager::uniqueInstance = &NoteManager::getNoteManager();

ostream& operator<< (ostream& f, const tm* t){
    f<<t->tm_mday<<"/"<<t->tm_mon<<"/"<<t->tm_year<<" - "<<t->tm_hour<<":"<<t->tm_min<<":"<<t->tm_sec;
    return f;
}



ostream& operator<< (ostream& f, const TaskStatus& S){
    if (S == 0) {
        f<<"Waiting";
    }else if (S == 1){
        f<<"Doing";
    }else if (S == 2){
        f<<"Done";
    }else{
        //Lancer une erreur ici?
    }
    return f;
}

ostream& operator<< (ostream& f, const OtherNoteType& T){
    if (T == 0) {
        f<<"Audio";
    }else if (T == 1){
        f<<"Video";
    }else if (T == 2){
        f<<"Image";
    }else{
        //Lancer une erreur ici?
    }
    return f;
}

ostream& operator<< (ostream& f, const RelationOrientation& R){
    if (R){
        f<<"oriented";
    }else{
        f<<"non-oriented";
    }
    return f;
}

ostream& operator<< (ostream& f, const QString& S){
    f<<S.toStdString();
    return f;
}

QString Note::getDateCQString(){

    int year = dateCreation->tm_year + 1900;

    //cout<<year<<endl;

    QString y = QString::number(year);

    int month = dateCreation->tm_mon + 1;

    QString mo = QString::number(month);

    int day = dateCreation->tm_mday;

    QString d = QString::number(day);

    int min = dateCreation->tm_min;

    QString mi = QString::number(min);

    int hour = dateCreation->tm_hour;

    QString h = QString::number(hour);

    int sec = dateCreation->tm_sec;

    QString s = QString::number(sec);

    QString dateC = d + "/" + mo + "/" + y + " - " + h + ":" + mi + ":" + s;

    return dateC;

}

QString Note::getDateLUQString(){
    int year = dateLastUpdate->tm_year + 1900;
    QString y = QString::number(year,10);
    int month =dateLastUpdate->tm_mon + 1;
    QString mo = QString::number(month);
    int day = dateLastUpdate->tm_mday;
    QString d = QString::number(day);
    int min = dateLastUpdate->tm_min;
    QString mi = QString::number(min);
    int hour = dateLastUpdate->tm_hour;
    QString h = QString::number(hour);
    int sec = dateLastUpdate->tm_sec;
    QString s = QString::number(sec);
    QString dateLU = d + "/" +mo+"/"+ y + " - " + h + ":"+mi+":"+s;
    return dateLU;
}

QString NoteVersions::getTypeQS(){
    switch(type){
    case NoteType::A:
        return "Article";
    case NoteType::T:
        return "Task";
    case NoteType::TWP:
        return "Task with priority";
    case NoteType::TWD:
        return "Task with deadline";
    case NoteType::ON:
        return "Other note";
    }
}


void Note::affiche(ostream& f){
    f<<"Id\t\t: "<<getIdentifier()<<endl
    <<"Title\t\t: "<<getTitle()<<endl
    <<"Creation date\t: "<<getDateCreation()<<endl
    <<"Last Update date\t: "<<getDateLastUpdate()<<endl
    <<"Active\t\t: "<<getStatusString()<<endl;
    afficheSuite(f);
}

//Implémentation avec un iterator
ostream& operator<< (ostream& f, NoteVersions& NV){
    f<<"-------NoteVersion-------"<<endl;
    for (NoteVersions::iterator it = NV.NoteVersions::getIterator() ; !it.isDone() ; it.isNext()){
        f<<"V["<<NV.getNb()-it.getNbRemain()<<"] : "<<endl<<it.current()<<endl;
    }
    return f;
}


//Implémentation avec iterator
ostream& operator<< (ostream& f, NoteManager& NM){
    f<<"-------NoteManager-------"<<endl;
    for (NoteManager::iterator it = NM.NoteManager::getIterator() ; !it.isDone() ; it.isNext()){
        f<<"M["<<NM.getNb()-it.getNbRemain()<<"] : "<<endl<<it.current()<<endl;
    }
    return f;
}


ostream& operator<< (ostream& f, Note& N){
    N.affiche(f);
    return f;
}

void NoteVersions::restoreVersion(Note *N){
    //on parcours le tableau à la recherche de la note à restaurer
    iterator it = getIterator();
    while ((!it.isDone())&&(&it.current() != N)){
        it.isNext();
    }
    /*nb - it.nbRemain indique le rang de la note à déplacer, il faut
     * donc décaler tous les éléments suivant d'un rang vers la gauche
     * afin qu'on ne laisse pas d'espace vide en enlevant la note.
     */
    for(unsigned int i = (nb - it.getNbRemain()) ; i < nb-1 ; i++){
        cout<<"T["<<i<<"] passe de : "<<versions[i]->getIdentifier()<<" a : "<<versions[i+1]->getIdentifier()<<endl;
        versions[i] = versions[i+1];
    }
    //puisqu'on a tout décalé vers la gauche, la dernière note ne doit plus exister
    versions[nb-1] = nullptr;
    //on a enlevé une note donc on décrémente le nombre de notes
    nb--;
    //puis on rajoute la version à restaurer en tête de liste.
    updateNewVersion(N);
}

void NoteVersions::addNote(Note * N){
    //agrandissemtn du tableau si nécessaire
    if (nb == nbMax){
        nbMax += 5;
        Note ** newTab = new Note*[nbMax];
        for (unsigned int i = 0 ; i < nbMax ; i++){
            newTab[i] = versions[i];
        }
        Note** old = versions;
        versions = newTab;
        delete[] old;
    }
    //ajout de l'élément dans le tableau
    versions[nb++] = N;
}



void NoteVersions::updateNewVersion(Note *N){
    //agrandissement éventuel du tableau
    if (nb == nbMax){
        ++nbMax;
    }
    cout<<"apres if updateNewversion"<<endl;
    cout<<nb<<endl<<nbMax<<endl;
    //décalage de tous les éléments dans le tableau pour
    //laisser la première place libre
    Note ** newTab = new Note*[nbMax];
    for (unsigned int i = 0 ; i < nb ; i++){
        cout<<"boucle for :"<<i<<endl;
        newTab[i+1] = versions[i];
    }
    Note** old = versions;
    cout<<"apres agrandissement tableau"<<endl;
    nb++;
    delete[] old;
    versions = newTab;

    //ajout de la note en tête de tableau
    versions[0] = N;
}

void NoteManager::addNoteVersion(NoteVersions *NV){
    //agrandissement du tableau si nécessaire
    if (nb == nbMax){
        nbMax += 5;
        NoteVersions ** newTab = new NoteVersions*[nbMax];
        for (unsigned int i = 0 ; i < nbMax ; i++){
            newTab[i] = notes[i];
        }
        notes = newTab;
    }
    //ajout de la NoteVersions dans le tableau
    notes[nb++] = NV;
    cout<<"ajout de la noteersion" <<endl;
}



NoteManager::~NoteManager(){
    for (unsigned int i=0 ; i<nb ; i++){
        delete notes[i];
    }
    delete[] notes;
    delete notes;
}


NoteManager& NoteManager::getNoteManager(NoteVersions **nv, unsigned int n, unsigned int nM){
    if (!uniqueInstance){
        uniqueInstance = new NoteManager(nv, n, nM);
    }
    return *uniqueInstance;
}

void NoteManager::freeNoteManager(){
    if(uniqueInstance){
        uniqueInstance->~NoteManager();
    }else{
        throw(NotesException("Impossible de libérer l'espace mémoire, aucun RelationManager n'existe."));
    }
}
