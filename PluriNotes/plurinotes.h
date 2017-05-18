#ifndef PLURINOTES_H
#define PLURINOTES_H

#include <iostream>
#include <ctime> //librairie pour gérer le temps et les dates
#include <string>


using namespace std;

//Définition des énumérations

enum TaskStatus{ waiting, doing, done}; //pour le statut d'un objet Task
enum OtherNoteType{audio, video, image}; //Pour le type d'un objet qui comprend un média
enum RelationOrientation{oriented, non_oriented}; //pour l'orientation des relations entre couples de Notes

//Définition des classes

class Couple;

//Classe d'exception :

class NotesException{
public:
    NotesException(const string& message):info(message){}
    string getInfo() const { return info; }
private:
    string info;
};




class Note {
/*Classe mère des classes Article, Task, TaskWithPriority, TaskWithDeadline, OtherArticle
 *
*/
private :
    string identifier;
    string title;
    struct tm* dateCreation;
    struct tm* dateLastUpdate;
    bool active;
    //a voir si ce setter est nécessaire
    void setIdentifier(string& id){identifier = id;}
protected:
    Note(const string& i, const string& t, tm* dC, tm* dLU, bool a)
        : identifier(i), title(t), dateCreation(dC), dateLastUpdate(dLU), active(a){}
public :
    //getters
    const string& getIdentifier(){return identifier;}
    const string& getTitle(){return title;}
    const tm* getDateCreation(){return dateCreation;}
    const tm* getDateLastUpdate(){return dateLastUpdate;}
    const bool& getActive(){return active;}
    const string& getActiveString(){ //fonction qui retourne l'état d'activité
                                     //sous forme de chaîne de caractères pour l'affichage
        string *act =  new string;
        if (active) {
            *act = "Active";
        }else{
            *act = "Inactive";
        }
        return *act;
    }

    //setters
    void setTitle(string& t){title = t;}
    void setDateCreation(tm * dC){dateCreation = dC;}
    void setDateLastUpdate(tm * dLU){dateLastUpdate = dLU;}
    void setActive(bool a){active = a;}
    virtual ostream& afficheSuite(ostream& f){return f;}
    void affiche(ostream& f);
};

class NoteVersions {
/*Classe chargé de gérer toutes les versions d'un même fichier, regroupées dans un tableau
 * de pointeurs. Pour des questions de simplicité il faut que la version la plus récente soit en tête
 * de tableau.
 * Il faudrait implémenter un iterator afin de pouvoir parcourir tous les éléments pour des recherches,
 * modifications, etc...
*/
private :

    Note ** versions;
    unsigned int nb;
    unsigned int nbMax;
public :
    NoteVersions(Note ** t = new Note*[0], unsigned int n = 0, unsigned int nM = 0) : versions(new Note*[nM]), nb(n), nbMax(nM){
        //copie du tableau en paramètre.
        for (unsigned int i = 0 ; i < n ; i++){
            versions[i] = t[i];
        }
    }
    //A remplacer par un iterator ici
    Note* getNthElement(unsigned int n){return versions[n];}
    // getters
    const unsigned int& getNb(){return nb;}
    const unsigned int& getNbMax(){return nbMax;}

    void addNote(Note* N);

    class iterator{
        friend class NoteVersions;
    private:
        unsigned int nbRemain;
        Note** currentV;
        iterator(Note** c, unsigned int nb):nbRemain(nb), currentV(c){}
    public:
        unsigned int getNbRemain()const{return nbRemain;}
        bool isDone(){return nbRemain==0;}
        void isNext(){
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            currentV++; nbRemain--;
        }
        Note& current(){
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            return **currentV;
        }
    };

    iterator getIterator(){
        return iterator(versions, nb);
    }

};


class NoteManager {
private :
    NoteVersions ** notes;
    unsigned int nb;
    unsigned int nbMax;
public :
    NoteManager(NoteVersions ** note = new NoteVersions*[0], unsigned int n = 0, unsigned int nM = 0) : notes(new NoteVersions*[nM]), nb(n), nbMax(nM){
        //copie du tableau en paramètre.
        for (unsigned int i = 0 ; i < n ; i++){
            notes[i] = note[i];
        }
    }
    //A remplacer par un iterator ici
    NoteVersions* getNthElement(unsigned int n){return notes[n];}
    // getters
    const unsigned int& getNb(){return nb;}
    const unsigned int& getNbMax(){return nbMax;}

    void addNoteVersion(NoteVersions *NV);

    class iterator{
        friend class NoteManager;
    private:
        unsigned int nbRemain;
        NoteVersions** currentN;
        iterator(NoteVersions** c, unsigned int nb):nbRemain(nb), currentN(c){}
    public:
        unsigned int getNbRemain()const{return nbRemain;}
        bool isDone(){return nbRemain==0;}
        void isNext(){
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            currentN++; nbRemain--;
        }
        NoteVersions& current(){
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            return **currentN;
        }
    };

    iterator getIterator(){
        return iterator(notes, nb);
    }
};


class Article : public Note {
/*
 *
*/
private :
    string text;
public :
    Article(const string& i, const string& t, tm* dC, tm* dLU, bool a, const string& s)
        : Note(i, t, dC, dLU, a), text(s){}
    //getters
    const string& getText(){return text;}
    //setters
    void setText(string& t){text = t;}
    ostream& afficheSuite(ostream& f){
        f<<"Text : "<<getText()<<endl;
        return f;
    }
};

class Task : public Note {
/*
 *
*/
private :
    string action;
    TaskStatus status;
public :
    Task(const string& i, const string& t, tm* dC, tm* dLU, bool a, const string& ac, TaskStatus s = waiting)
        : Note(i, t, dC, dLU, a), action(ac), status(s){}
    //getters
    const string& getAction(){return action;}
    const TaskStatus& getStatus(){return status;}
    //setters
    void getAction(string& a){action = a;}
    void getStatus(TaskStatus& s){status = s;}
    ostream& afficheSuite(ostream& f){
        f<<"Action : "<<getAction()<<endl
        <<"Status : "<<getStatus()<<endl;
        return f;
    }
};

class TaskWithPriority : public Task {
/*
 *
 */
private :
    int priority;
public :
    TaskWithPriority(const string& i, const string& t, tm* dC, tm* dLU, bool a, const string& ac, TaskStatus s, int p)
        : Task(i, t, dC, dLU, a, ac, s), priority(p){}
    //getters
    const int& getPriority(){return priority;}
    //setters
    void setPriority(int & p){priority = p;}
    ostream& afficheSuite(ostream& f){
        f<<"Action : "<<getAction()<<endl
        <<"Status : "<<getStatus()<<endl
        <<"Priority : "<<getPriority()<<endl;
        return f;
    }
};

class TaskWithDeadline : public Task {
/*
 *
 */
private :
    struct tm* deadline;
public :
    TaskWithDeadline(const string& i, const string& t, tm* dC, tm* dLU, bool a, const string& ac, TaskStatus s, tm* d)
        : Task(i, t, dC, dLU, a, ac, s), deadline(d){}
    //getters
    const tm* getDeadline(){return deadline;}
    //setters
    void setDeadline(tm * d){deadline = d;}
    ostream& afficheSuite(ostream& f){
        f<<"Action : "<<getAction()<<endl
        <<"Status : "<<getStatus()<<endl
        <<"Deadline : "<<getDeadline()<<endl;
        return f;
    }
};


class OtherNote : public Note{
/*
 *
 */
private :
    string description;
    string fileName;
    OtherNoteType type;
public :
    OtherNote(const string& i, const string& t, tm* dC, tm* dLU, bool a, const string& d, const string& fName, const OtherNoteType& ty)
        : Note(i, t, dC, dLU, a), description(d), fileName(fName), type(ty){}
    //getters
    const string& getDescription(){return description;}
    const string& getFileName(){return fileName;}
    const OtherNoteType& getType(){return type;}
    //setters
    void getDescription(string& d){description = d;}
    void getFileName(string& f){fileName = f;}
    void getType(OtherNoteType& t){type = t;}
    ostream& afficheSuite(ostream& f){
        f<<"Description : "<<getDescription()<<endl
        <<"File : "<<getFileName()<<endl
        <<"Type : "<<getType()<<endl;
        return f;
    }
};


class Couple {
/*Classe représentant une liaison entre 2 notes.
 * la note choisie devra toujours être le premier élément du
 * tableau tab de la classe NotesVersions (première version)
 */
private :
    string label;
    Note* x;
    Note* y;
public :
    Couple(const string& l, Note* x , Note* y): label(l), x(x), y(y) {}
    //getters
    const string& getLabel(){return label;}
    Note* getX(){return x;}
    Note* getY(){return y;}
    void setX(Note * Xs){x = Xs;}
    void setY(Note * Ys){y = Ys;}
};


class Relation {
/*
 *
 */
private :
    Couple ** couples;
    unsigned int nb;
    unsigned int nbMax;
    string title;
    string description;
    RelationOrientation orientation;
public :
    Relation(Couple ** c = new Couple*[0], unsigned int n = 0, unsigned int nM = 0, const string& t = "", const string& d = "", const RelationOrientation& o = oriented)
        : couples(new Couple*[nM]), nb(n), nbMax(nM), title(t), description(d), orientation(o){
        for (unsigned int i = 0 ; i< n ; i++){
            couples[i] = c[i];
        }
    }
    //getters
    Couple* getNthElement(unsigned int n){return couples[n];}
    const unsigned int& getNb(){return nb;}
    const unsigned int& getNbMax(){return nbMax;}
    const string& getTitle(){return title;}
    const string& getDescription(){return description;}
    RelationOrientation& getOrientation(){return orientation;}
    //setters
    void setNb(unsigned int n){nb = n;}
    void setNbMax(unsigned int nM){nbMax = nM;}
    void setTitle(const string& t){title = t;}
    void setDescription(const string& d){description = d;}
    void setOrientation(RelationOrientation& ori){orientation = ori;}
    void setCouple(Couple ** C){couples = C;}
    void addCouple(Couple * c);

    class iterator{
        friend class Relation;
    private:
        unsigned int nbRemain;
        Couple** currentR;
        iterator(Couple** R, unsigned int nb):nbRemain(nb), currentR(R){}
    public:
        unsigned int getNbRemain()const{return nbRemain;}
        bool isDone(){return nbRemain==0;}
        void isNext(){
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            currentR++; nbRemain--;
        }
        Couple& current(){
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            return **currentR;
        }
    };

    iterator getIterator(){
        return iterator(couples, nb);
    }

};


class RelationManager {
/*Classe permettant de gérer l'ensemble des relations
 *
 */
 //Il faut déclarer pas mal de trucs static ici pour pouvoir utiliser les relations dans les autres classes
 //A mon avis relationManager devra être un singleton, en plus on aurait aucun intérêt à avoir plusieurs
 //RelationManagers.
private :
    static RelationManager * uniqueInstance;
    static Relation ** relations;
    static unsigned int nb;
    static unsigned int nbMax;
    RelationManager(Relation ** r = new Relation*[0], unsigned int n = 0, unsigned int nM = 0){
        nb = n;
        nbMax = nM;
        relations = new Relation*[nM];
        for (unsigned int i = 0 ; i< n ; i++){
            relations[i] = r[i];
        }
    }
    virtual ~RelationManager();
    operator= (const RelationManager& RM);
    RelationManager(const RelationManager& RM);

public :
    static RelationManager& getRelationManager(Relation ** r = new Relation*[0], unsigned int n = 0, unsigned int nM = 0);
    static void freeRelationManager();
    static const unsigned int& getNb(){return nb;}
    static const unsigned int& getNbMax(){return nbMax;}
    static void setNb(unsigned int n){nb = n;}
    static void setNbMax(unsigned int nM){nbMax = nM;}

    static void addRelation(Relation* R);
    //faire un iterator
    static Relation* getNthElement(unsigned int n){return relations[n];}

    class iterator{
        friend class RelationManager;
    private:
        unsigned int nbRemain;
        Relation** currentRM;
        iterator(Relation** R, unsigned int nb):nbRemain(nb), currentRM(R){}
    public:
        unsigned int getNbRemain()const{return nbRemain;}
        bool isDone(){return nbRemain==0;}
        void isNext(){
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            currentRM++; nbRemain--;
        }
        Relation& current(){
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            return **currentRM;
        }
    };

    static iterator getIterator(){
        return iterator(relations, nb);
    }

};


//Méthodes externes aux classes

Relation &getRelations(Note* N);

//redéfinition des opérateurs

ostream& operator<< (ostream& f, const tm* tps); //necessiare pour afficher les heures de façon stylée
ostream& operator<< (ostream& f, const TaskStatus& S);    //La redéfiniton de l'opérateur << est nécessaire pour les
ostream& operator<< (ostream& f, const OtherNoteType& T); //enum car sinon lors de l'affichage, il n'affiche pas le nom de la variable
                                                    //mais l'entier associé
                                                    //Exemple cout<<waiting affiche 0
                                                    //        cout<<doing affiche 1, etc...

ostream& operator << (ostream& f, Note& N);
ostream& operator<< (ostream& f, NoteVersions& V);
ostream& operator<< (ostream& f, NoteManager& NM);
ostream& operator<< (ostream& f, Article& A);
ostream& operator<< (ostream& f, Task& T);
ostream& operator<< (ostream& f, TaskWithPriority& T);
ostream& operator<< (ostream& f, TaskWithDeadline& T);
ostream& operator<< (ostream& f, OtherNote& T);
ostream& operator<< (ostream& f, Relation& R);
ostream& operator<< (ostream& f, RelationManager& RM);
ostream& operator<< (ostream& f, Couple& C);






#endif // PLURINOTES_H
