#include "plurinotes.h"


//Redéfinition des opérateurs


ostream& operator<< (ostream& f, const tm* tps)
{
    int year = tps->tm_year + 1900;
    int month = tps->tm_mon + 1;
    int day = tps->tm_mday;
    int min = tps->tm_min;
    int hour = tps->tm_hour;
    int sec = tps->tm_sec;
    f<<day<<"/"<<month<<"/"<<year<<" - "<<hour<<":"<<min<<":"<<sec;
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


/*******************************/




void Note::affiche(ostream& f){
    f<<"Id : "<<getIdentifier()<<endl
    <<"Title : "<<getTitle()<<endl
    <<"Creation date : "<<getDateCreation()<<endl
    <<"Last Update date : "<<getDateLastUpdate()<<endl
    <<"Active : "<<getActiveString()<<endl;
    afficheSuite(f);
}

ostream& operator<< (ostream& f, NoteVersions& V){
    for (unsigned int i = 0 ; i < V.getNb() ; i++){
        f<<"V["<<i<<"] : "<<*V.getNthElement(i)<<endl;
    }
    return f;
}


ostream& operator<< (ostream& f, NoteManager& NM){
    for (unsigned int i = 0 ; i < NM.getNb() ; i++){
        f<<"Note["<<i<<"] : \n"<<*NM.getNthElement(i)<<endl;
    }
    return f;
}


ostream& operator<< (ostream& f, Note& N){
    N.affiche(f);
    return f;
}


ostream& operator<< (ostream& f, Article& A){
    A.affiche(f);
    return f;
}


ostream& operator<< (ostream& f, Task& T){
    T.affiche(f);
    return f;
}

ostream& operator<< (ostream& f, TaskWithPriority& T){
    T.affiche(f);
    return f;
}

ostream& operator<< (ostream& f, TaskWithDeadline& T){
    T.affiche(f);
    return f;
}

ostream& operator<< (ostream& f, OtherNote& T){
    T.affiche(f);
    return f;
}

ostream& operator << (ostream& f, Relation& R){
    for (unsigned int i = 0 ; i < R.getNb() ; i++){
        f<<"R["<<i<<"] : "<<endl
         <<"Orientation"<<R.getOrientation()<<endl
         <<*R.getNthElement(i)<<endl;
    }
    return f;
}

ostream& operator << (ostream& f, Couple& C){
    f<<"Label : "<<C.getLabel()<<endl
     <<"x :"<<endl<<*C.getX()<<"y :"<<endl<<*C.getY()<<endl;
    return f;
}


/**********************************/

void NoteVersions::addNote(Note * t){
    if (nb == nbMax){
        nbMax += 5;
        Note ** newTab = new Note*[nbMax];
        for (unsigned int i = 0 ; i < nbMax ; i++){
            newTab[i] = versions[i];
        }
        versions = newTab;
    }
    versions[nb++] = t;
}


void NoteManager::addNoteVersion(NoteVersions *NV){
    if (nb == nbMax){
        nbMax += 5;
        NoteVersions ** newTab = new NoteVersions*[nbMax];
        for (unsigned int i = 0 ; i < nbMax ; i++){
            newTab[i] = notes[i];
        }
        notes = newTab;
    }
    notes[nb++] = NV;
}


void Relation::addCouple(Couple * c){
    if (nb == nbMax){
        nbMax += 5;
        Couple ** newTab = new Couple*[nbMax];
        for (unsigned int i = 0 ; i < nbMax ; i++){
            newTab[i] = couples[i];
        }
        couples = newTab;
    }
    couples[nb++] = c;
}



