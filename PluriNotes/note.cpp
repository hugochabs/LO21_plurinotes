#include "notefille.h"
#include "relation.h"

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
    <<"Status\t\t: "<<getNoteStatusString()<<endl;
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

    cout<<nb<<endl<<nbMax<<endl;
    //décalage de tous les éléments dans le tableau pour
    //laisser la première place libre
    Note ** newTab = new Note*[nbMax];
    for (unsigned int i = 0 ; i < nb ; i++){
        cout<<"boucle for :"<<i<<endl;
        newTab[i+1] = versions[i];
    }
    Note** old = versions;

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

NoteVersions* NoteManager::getNVfromNote(Note* N){
    // parcours des différentes NotesVersions contenues dans le NoteManager
    for (unsigned int i = 0 ; i < this->nb ; i++){
        // on part du principe que toutes les versions d'une note ont le même id
            if (N->getIdentifier() == notes[i]->getVersions()[0]->getIdentifier()){
                return notes[i];
            }
    }
    // si parcours effectué et rien correspondant de trouvé on renvoit null
    throw NotesException("Pas de NoteVersions correspondant à la Note que vous recherchez");
}

void NoteManager::archiveNoteVersions(NoteVersions *NV){
    for(NoteVersions::iterator it = NV->getIterator() ; !it.isDone() ; it.isNext())
        it.current().setNoteStatus(archived);
}

void NoteManager::restoreNoteVersions(NoteVersions *NV){
    for(NoteVersions::iterator it = NV->getIterator() ; !it.isDone() ; it.isNext()){
        it.current().setNoteStatus(active);
    }
}

void NoteManager::deleteNoteVersions(Note* N){
    // get NoteVersions for the Note in parameter
    NoteVersions* NV = getNVfromNote(N);
     if ( Reference::isNoteReferenced(N) ){
        archiveNoteVersions(NV);
     }
     else {
        deleteNoteCouples(N);
        putNVToTrash(NV);
     }
}

void NoteManager::deleteNoteCouples(Note* N){
    RelationManager& RM = RelationManager::getRelationManager();
    // itération parmi les différentes Relations
    for (RelationManager::iterator it = RM.getIterator() ; !it.isDone() ; it.isNext()){
        // itération parmi les différents couples d'une Relation
        Relation R = it.current();
        for (Relation::iterator it2 = it.current().getIterator() ; !it2.isDone() ; it2.isNext() ){
            if ( it2.current().getX() == N || it2.current().getY() == N ){
                R.deleteCouple(&it2.current());

            }
        }
    }
}


void NoteManager::putNVToTrash(NoteVersions* NV){
    for(NoteVersions::iterator it = NV->getIterator() ; !it.isDone() ; it.isNext())
        it.current().setNoteStatus(trash);
}


NoteManager::~NoteManager(){
    for (unsigned int i=0 ; i<nb ; i++){
        delete notes[i];
    }
    delete[] notes;
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


Note* NoteManager::searchNote(QString& id){
    //On récupère le NM
    NoteManager& NM = getNoteManager();
    //On parcourt l'ensemble des Notes
    for(iterator it = NM.getIterator() ; !it.isDone() ; it.isNext()){
        NoteVersions NV = it.current();
        NoteVersions::iterator it2 = NV.getIterator() ;
        Note& N = it2.current();
        //Si on trouve la Note on la retourne
        if (N.getIdentifier() == id){
            return &N;
        }
    }
    return nullptr;
}

QString& Note::getStringAttributes(){
    QString& chaine = title;
    return chaine;
}


QString& Article::getStringAttributes(){
    QString* chaine = new QString;
    *chaine = getTitle() + getText();
    return *chaine;
}

QString& Task::getStringAttributes(){
    QString* chaine = new QString;
    *chaine = getTitle() + action;
    return *chaine;
}

QString& TaskWithDeadline::getStringAttributes(){
    QString* chaine = new QString;
    *chaine = getTitle() + getAction();
    return *chaine;
}

QString& TaskWithPriority::getStringAttributes(){
    QString* chaine = new QString;
    *chaine = getTitle() + getAction();
    return *chaine;
}

QString& OtherNote::getStringAttributes(){
    QString* chaine = new QString;
    *chaine = getTitle() + description;
    return *chaine;
}

QString Note::getTypeOfNote(){
    NoteManager& nm = NoteManager::getNoteManager();
    for (NoteManager::iterator it = nm.getIterator() ; !it.isDone() ; it.isNext()){
        NoteVersions nv = it.current();
        NoteVersions::iterator it2 = nv.getIterator();
        if (it2.current().getIdentifier() == getIdentifier()){
            return nv.getTypeQS();
        }
    }
}


vector<Note> Note::getReferences(){
    //On crée un vector pour la simplicité d'utilisation
    vector<Note> refs;
    //On récupère sous forme de QString l'ensemble des attributs
    //de type QString de la Note
    QString chaine = getStringAttributes();
    //pour récupérer la position des réferences dans le QSrting
    int pos = 0;
    int pos2 = 0;
    //Les marqueurs à aller chercher dans le texte
    QString beg = "\\ref{";
    QString end = "}";
    //Tant qu'on trouve une référence on continue d'en chercher
    while ((pos != -1) && (pos2 != -1)){
        //if obligatoire sinon bug
        if (pos != -1){
            //On récupère la position de la reférence (début et fin)
            pos = chaine.indexOf(beg, pos);
            pos2 = chaine.indexOf(end, pos2);
        }
        if (pos != -1){
            //incrémentation pour l'offset du à \ref{
            pos += 5;
            //variable qui contiendra l'id de la note référencée
            QString idToSearch;
            //On récupère l'id dans la chaine
            for(int i = pos ; i < pos2 ; i++){
                idToSearch += chaine[i];
            }
            //On recherche la Note correspondante
            Note* toAdd = NoteManager::searchNote(idToSearch);
            //On l'ajoute au vector
            refs.push_back(*toAdd);
            //On incrémente la position parce que ça sert à rien de chercher
            //La ou on à déjà cherché
            pos2++;
        }
        //On incrémente la position parce que ça sert à rien de chercher
        //La ou on à déjà cherché
        pos = pos2;
    }
    //Pour avoir une valeur de retour sous forme de Note*, il faut recopier le
    //contenu du vector dans le tableau
    return refs;
}




