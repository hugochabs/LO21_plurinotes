#include "relation.h"

unsigned int RelationManager::nb = 0;
unsigned int RelationManager::nbMax = 0;
RelationManager* RelationManager::uniqueInstance = 0;
Relation** RelationManager::relations = 0;
Reference* Reference::uniqueRef = 0;
QString RelationManager::directory = "/home/guilllaume/Documents/UTC/GI02/LO21/LO21_plurinotes/LO21_plurinotes/PluriNotes2/";

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

//Pour pouvoir afficher le map des descendants
ostream& operator<< (ostream& f, map<Note*, int> M){
    for(auto it = M.begin() ; it != M.end() ; it++){
        f<<"N : "<<endl<<*it->first<<endl
         <<"O : "<<it->second<<endl;
    }
    return f;
}

/**********************************/


RelationManager& relationManager = RelationManager::getRelationManager();

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
    delete c;
}

void RelationManager::addRelation(Relation* R){
    //agrandissement du tableau si nécessaire
    if (getNb() == getNbMax()){
        setNbMax(getNbMax() + 5);
        Relation ** newTab = new Relation*[getNbMax()];
        for (RelationManager::iterator it = ){
            newTab[i] = relations[i];
            for(Relation::iterator it2 = relations[i]->getIterator() ; !it2.isDone() ; it2.isNext()){
                newTab[i]->addCouple(&it2.current());
            }
        }
        relations = newTab;
    }
    //ajout de l'élément
    relations[nb++] = R;
}

void RelationManager::deleteRelation(){

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
    for(RelationManager::iterator it = getIterator() ; !it.isDone() ; it.isNext()){
        delete &it.current();
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



map<Note*, int> RelationManager::getDescendants(Note* N, int order){
    //map de retour de la forme :
    //<Note* ,  ordre auquel la Note* à été trouvée>
    map<Note*, int> M;
    //condition d'arrèt de la procédure récursive
    if(order > 0){
        //Petite itération de tous les couples
        RelationManager& RM = getRelationManager();
        for(RelationManager::iterator it = RM.getIterator() ; !it.isDone() ; it.isNext()){
            Relation& R = it.current();
            for (Relation::iterator it2 = R.getIterator() ; !it2.isDone() ; it2.isNext()){
                bool added = false;
                Couple& C = it2.current();
                //On regarde si la note en paramètre est X tq le couple soit (X,Y)
                if (C.getX()->getIdentifier() == N->getIdentifier()){
                    //si c'est le cas on l'ajoute au map avec l'ordre correspondant
                    M[C.getY()] = 2 - order;
                    added = true;
                }
                //Si Le fils n'est pas nul, on relance la procédure récursivement
                if (added){
                    map<Note*, int> Tmp;
                    Tmp = getDescendants(C.getY(), order-1);
                    //et on copie le résultat de la procédure récursive dans le tableau actuel
                    for(auto it3 = Tmp.begin() ; it3 != Tmp.end() ; it3++){
                        M[it3->first] = it3->second;
                    }
                }
            }
        }
    }
    //on retourne le map
    return M;
}


map<Note *, int> RelationManager::getAscendants(Note* N, int order){
    //map de retour de la forme :
    //<Note* ,  ordre auquel la Note* à été trouvée>
    map<Note*, int> M;
    //condition d'arrèt de la procédure récursive
    if(order > 0){
        //Petite itération de tous les couples
        RelationManager& RM = getRelationManager();
        for(RelationManager::iterator it = RM.getIterator() ; !it.isDone() ; it.isNext()){
            Relation& R = it.current();
            for (Relation::iterator it2 = R.getIterator() ; !it2.isDone() ; it2.isNext()){
                bool added = false;
                Couple& C = it2.current();
                //On regarde si la note en paramètre est Y tq le couple soit (X,Y)
                if (C.getY()->getIdentifier() == N->getIdentifier()){
                    //si c'est le cas on l'ajoute au map avec l'ordre correspondant
                    M[C.getX()] = 2 - order;
                    added = true;
                }
                //Si Le fils n'est pas nul, on relance la procédure récursivement
                if (added){
                    map<Note*, int> Tmp;
                    Tmp = getAscendants(C.getX(), order-1);
                    //et on copie le résultat de la procédure récursive dans le tableau actuel
                    for(auto it3 = Tmp.begin() ; it3 != Tmp.end() ; it3++){
                        M[it3->first] = it3->second;
                    }
                }
            }
        }
    }
    //on retourne le map
    return M;
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

//fonction statique pour pouvoir update les références plus facilement
void Reference::updateRefs(){
    Reference& R = *getRef();
    R.getReferences();
}


//fonction qui parcourt toutes les notes et crée les reférences correspondantes
void Reference::getReferences(){
    NoteManager& NM = NoteManager::getNoteManager();
    for (NoteManager::iterator it = NM.getIterator() ; !it.isDone() ; it.isNext()){
        NoteVersions NV = it.current();
        for (NoteVersions::iterator it2 = NV.getIterator() ; !it2.isDone() ; it2.isNext()){
            Note* N = &it2.current();
            vector<Note> refs;
            refs = N->getReferences();
            for (unsigned int i = 0 ; i < refs.size() ; i++){
                QString desc = "" + i;
                Note& tmp = refs[i];
                Couple * c = new Couple(desc, N, &tmp);
                addCouple(c);
            }
        }
    }
}

//retourne vrai si la note N est référencée par une autre note
bool Reference::isNoteReferenced(Note * N){
    Reference& R = *getRef();
    R.getReferences();
    for (Reference::iterator it = R.getIterator() ; !it.isDone() ; it.isNext()){
        Couple& C = it.current();
        if(C.getY() != nullptr){
            if (C.getY()->getIdentifier() == N->getIdentifier() ){
                return true;
            }
        }
    }
    return false;
}
