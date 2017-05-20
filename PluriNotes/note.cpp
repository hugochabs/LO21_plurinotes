#include "notefille.h"

using namespace std;
/*
ostream& operator<< (ostream& f, const tm* tps)
{
    f<<tps->toString();
    return f;
}
*/

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






void Note::affiche(ostream& f){
    f<<"Id\t: "<<getIdentifier()<<endl
    <<"Title\t: "<<getTitle()<<endl
    <<"Creation date\t: "<<getDateCreation()<<endl
    <<"Last Update date\t: "<<getDateLastUpdate()<<endl
    <<"Active\t: "<<getActiveString()<<endl;
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
        versions = newTab;
    }
    //ajout de l'élément dans le tableau
    versions[nb++] = N;
}



void NoteVersions::updateNewVersion(Note *N){
    //agrandissement éventuel du tableau
    if (nb == nbMax){
        ++nbMax;
    }
    //décalage de tous les éléments dans le tableau pour
    //laisser la première place libre
    Note ** newTab = new Note*[nbMax];
    for (unsigned int i = 0 ; i < nb ; i++){
        newTab[i+1] = versions[i];
    }
    nb++;
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
}
