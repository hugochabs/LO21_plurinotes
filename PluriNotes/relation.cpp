#include "relation.h"

unsigned int RelationManager::nb = 0;
unsigned int RelationManager::nbMax = 0;
RelationManager* RelationManager::uniqueInstance = 0;
Relation** RelationManager::relations = 0;
Reference* Reference::uniqueRef = 0;

ostream& operator << (ostream& f, Relation& R){
    f<<"----------Relation - "<<R.getTitle()<<"---------"<<endl;
    f<<"Description : "<<R.getDescription()<<endl
     <<"Orientation : "<<R.getOrientation()<<endl;
    for (Relation::iterator it = R.getIterator() ; !it.isDone() ; it.isNext()){
        f<<"R["<<R.getNb()-it.getNbRemain()<<"] : "<<endl<<it.current()<<endl;
    }
    return f;
}

ostream& operator << (ostream& f, Reference& R){
    f<<"----------Reference - "<<R.getTitle()<<"---------"<<endl;
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
    f<<"x :"<<endl<<*(C.getX())<<"";
    f<<"y :"<<endl;
    f<<*(C.getY())<<endl;
    return f;
}


/**********************************/













void Relation::addCouple(Couple * c){
    //agrandissement du tableau si nécessaire
    if (nb == nbMax){
        nbMax += 5;
        Couple ** newTab = new Couple*[nbMax];
        for (unsigned int i = 0 ; i < nb ; i++){
            newTab[i] = couples[i];
        }
        couples = newTab;

    }
    //ajout de l'élément
    couples[nb++] = c;
}

void Relation::deleteCouple(Couple * c){
    // TODO
}


void RelationManager::addRelation(Relation* R){
    //agrandissement du tableau si nécessaire
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
    //ajout de l'élément
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

RelationManager& RelationManager::getRelationManager(){
    if (!uniqueInstance){
        uniqueInstance = new RelationManager();
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

Reference& Reference::getRef(){
    if (!uniqueRef){
        uniqueRef = new Reference();
    }
    return *uniqueRef;
}

void Reference::freeRef(){
    if (uniqueRef){
        delete uniqueRef;
    }
    uniqueRef = nullptr;
}



void Reference::getReferences(){
    NoteManager& NM = NoteManager::getNoteManager();
    for (NoteManager::iterator it = NM.getIterator() ; !it.isDone() ; it.isNext()){
        NoteVersions NV = it.current();
        for (NoteVersions::iterator it2 = NV.getIterator() ; !it2.isDone() ; it2.isNext()){
            Note* N = &it2.current();
            vector<Note> refs;
            refs = N->getReferences();
            for (unsigned int i = 0 ; i < refs.size() ; i++){
                cout<<"refs["<<i<<"]"<<refs[i]<<endl;
                QString desc = "" + i;
                Note& tmp = refs[i];
                Couple * c = new Couple(desc, N, &tmp);
                addCouple(c);
            }
        }
    }
}

