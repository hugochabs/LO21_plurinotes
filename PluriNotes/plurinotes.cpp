#include "plurinotes.h"

unsigned int RelationManager::nb = 0;
unsigned int RelationManager::nbMax = 0;
RelationManager* RelationManager::uniqueInstance = 0;
Relation** RelationManager::relations = new Relation*[0];


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


//Implémentation avec un iterator
ostream& operator<< (ostream& f, NoteVersions& V){
    for (NoteVersions::iterator it = V.NoteVersions::getIterator() ; !it.isDone() ; it.isNext()){
        f<<"V["<<V.getNb()-it.getNbRemain()<<"] : "<<endl<<it.current()<<endl;
    }
    return f;
}


//Implémentation avec iterator
ostream& operator<< (ostream& f, NoteManager& NM){
    for (NoteManager::iterator it = NM.NoteManager::getIterator() ; !it.isDone() ; it.isNext()){
        f<<"M["<<NM.getNb()-it.getNbRemain()<<"] : "<<endl<<it.current()<<endl;
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
    f<<"----------Relation - "<<R.getTitle()<<"---------"<<endl;
    f<<"Description : "<<R.getDescription()<<endl
     <<"Orientation : "<<R.getOrientation()<<endl;
    for (unsigned int i = 0 ; i < R.getNb() ; i++){
        f<<*R.getNthElement(i)<<endl;
    }
    return f;
}

ostream& operator << (ostream& f, Couple& C){
    f<<"----------Couple - "<<C.getLabel()<<"---------"<<endl;
    f<<"x :"<<endl<<*C.getX()<<"y :"<<endl<<*C.getY()<<endl;
    return f;
}


/**********************************/

void NoteVersions::addNote(Note * N){
    if (nb == nbMax){
        nbMax += 5;
        Note ** newTab = new Note*[nbMax];
        for (unsigned int i = 0 ; i < nbMax ; i++){
            newTab[i] = versions[i];
        }
        versions = newTab;
    }
    versions[nb++] = N;
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
        for (unsigned int i = 0 ; i < nb ; i++){
            newTab[i] = couples[i];
        }
        couples = newTab;
        for (unsigned int i = 0 ; i < nb ; i++){
            delete newTab[i];
        }
    }
    couples[nb++] = c;
}


void RelationManager::addRelation(Relation* R){
    if (getNb() == getNbMax()){
        setNbMax(getNbMax() + 5);
        Relation ** newTab = new Relation*[getNbMax()];
        for (unsigned int i = 0 ; i < getNb() ; i++){
            newTab[i] = relations[i];
            for(unsigned int j = 0 ; j < relations[i]->getNb() ; j++){
                newTab[i]->addCouple(relations[i]->getNthElement(j));
            }
        }
        relations = newTab;
    }
    relations[nb++] = R;
}

Relation& getRelations(Note* N){
    Relation *Rel = new Relation();
    Rel->setNb(0);
    Rel->setNbMax(0);
    Rel->setTitle("Relations de \"" + N->getTitle()+"\"");
    Rel->setDescription("Relations dans laquelle la note \"" + N->getTitle() + "\" est impliquee");
    //Parcours de l'ensemble des notes de NoteManager;
    for(unsigned int i = 0 ; i < RelationManager::getNb() ; i++){
        //Attention, ici il faudra utiliser l'iterator plutôt que getNthElement.
        Relation* R = RelationManager::getNthElement(i);
        for(unsigned int j = 0 ; j < R->getNb() ; j++){
            if((R->getNthElement(j)->getX() == N) || (R->getNthElement(j)->getY() == N)){
                //Peut être à garder, pas sur
                /*if (Rel->getNb() == Rel->getNbMax()){
                    Rel->setNbMax(Rel->getNbMax()+5);
                    Couple ** newTab  = new Couple*[Rel->getNbMax()];
                    for (unsigned int i = 0 ; i < Rel->getNbMax() ; i++){
                        Rel->addCouple(newTab[i]);
                    }

                }*/
                Rel->addCouple(R->getNthElement(j));
            }
        }
    }
    return *Rel;
}


RelationManager::~RelationManager(){
    for (unsigned int i = 0 ; i< nb ; i++){
        delete getNthElement(i);
    }
}

RelationManager& RelationManager::getRelationManager(Relation ** r, unsigned int n, unsigned int nM){
    if (!uniqueInstance){
        uniqueInstance = new RelationManager(r, n, nM);
    }
    return *uniqueInstance;
}

void RelationManager::freeRelationManager(){
    if(uniqueInstance){
        uniqueInstance->~RelationManager();
    }else{
        //renvoyer une erreur.
    }
}
