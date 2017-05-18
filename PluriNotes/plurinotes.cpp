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
    for (Relation::iterator it = R.getIterator() ; !it.isDone() ; it.isNext()){
        f<<"R["<<R.getNb()-it.getNbRemain()<<"] : "<<endl<<it.current()<<endl;
    }
    return f;
}


ostream& operator<< (ostream& f, RelationManager& RM){
    f<<"-------RelationManager-------"<<endl;
    for(RelationManager::iterator it = RM.getIterator() ; !it.isDone() ; it.isNext()){
        f<<"RM["<<RM.getNb()-it.getNbRemain()<<"] : "<<endl<<it.current()<<endl;
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
    Rel->setTitle("Relations de \"" + N->getTitle()+"\"");
    Rel->setDescription("Relations dans laquelle la note \"" + N->getTitle() + "\" est impliquee");
    //Parcours de l'ensemble des notes de NoteManager;
    for(RelationManager::iterator it = RelationManager::getIterator() ; !it.isDone() ; it.isNext()){
        Relation R = it.current();
        for(Relation::iterator it = R.getIterator() ; !it.isDone() ; it.isNext()){
            //Si la note apparait dans le couple examiné.
            if((it.current().getX() == N) || (it.current().getY() == N)){
                Rel->addCouple(&it.current());
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
        throw(NotesException("Impossible de libérer l'espace mémoire, aucun RelationManager n'existe."));
    }
}
