#ifndef PLURINOTES_H
#define PLURINOTES_H

#include <iostream>
#include <ctime> //librairie pour gérer le temps et les dates
#include <string>


using namespace std;

//-----------------------------------//

//Définition des énumérations

enum TaskStatus{ waiting, doing, done}; //pour le statut d'un objet Task
enum OtherNoteType{audio, video, image}; //Pour le type d'un objet qui comprend un média
enum RelationOrientation{oriented, non_oriented}; //pour l'orientation des relations entre couples de Notes

//----Définition des classes----//


//----Classe d'exception----//
/*!
 * \brief La classe NotesException sert à gérer les exceptions,
 * renvoyées par l'ensemble du programme sous forme de string.
 */
class NotesException{
public:
    NotesException(const string& message):info(message){}
    string getInfo() const { return info; }
private:
    string info;
};


//----Classes de Notes----//

/*!
 * \brief La classe Note est la classe mère de tous les autres types
 * de notes. elle est caractérisée par un identificateur, un titre,
 * une date de création, une date de dernière modification, et un statut.
 */
class Note {
private :
    string identifier;//!identifant de la note
    string title;//!titre de la note
    struct tm* dateCreation;//!date de création de la note
    struct tm* dateLastUpdate;//!date de la dernière mise à jour de la note
    bool active;//! statut de la note
protected:
    Note(const string& i, const string& t, tm* dC, tm* dLU, bool a)
        : identifier(i), title(t), dateCreation(dC), dateLastUpdate(dLU), active(a){}//!constructeur de la classe
public :
    //getters
    const string& getIdentifier(){return identifier;}//!getter d'identifier
    const string& getTitle(){return title;}//!getter de title
    const tm* getDateCreation(){return dateCreation;}//!getter de dateCreation
    const tm* getDateLastUpdate(){return dateLastUpdate;}//!getter de dateLastUpdate
    const bool& getActive(){return active;}//!getter de active
    /*!
     * \brief getActiveString retourne la valeur de active
     * sous forme de chaîne de caractères.
     * \return (string)active.
     */
    const string& getActiveString(){
        string *act =  new string;
        if (active) {
            *act = "Active";
        }else{
            *act = "Inactive";
        }
        return *act;
    }
    //setters
    void setTitle(string& t){title = t;}//!setter de title
    void setDateCreation(tm * dC){dateCreation = dC;}//!setter de dateCreation
    void setDateLastUpdate(tm * dLU){dateLastUpdate = dLU;}//!setter de datelastUpdate
    void setActive(bool a){active = a;}//!setter de active
    /*!
     * \brief afficheSuite définition de la méthode affiche suite vouée à être
     * surchargée par les classes filles
     * \param f flux de sortie
     * \return flux de sortie
     */
    virtual ostream& afficheSuite(ostream& f){return f;}
    void affiche(ostream& f);
};


/*!
 * Classe chargée de gérer toutes les versions d'un même fichier, regroupées dans un tableau
 * de pointeurs. Pour des questions de simplicité la version la plus récente est en tête
 * de tableau.
*/
class NoteVersions {
private :
    Note ** versions;//!tableau de pointeurs de notes regroupant les versions
    unsigned int nb;//!nombre de versions
    unsigned int nbMax;//!nombre max de versions
public :
    NoteVersions(Note ** t = new Note*[0], unsigned int n = 0, unsigned int nM = 0) : versions(new Note*[nM]), nb(n), nbMax(nM){
        //copie du tableau en paramètre.
        for (unsigned int i = 0 ; i < n ; i++){
            versions[i] = t[i];
        }//!constructeur de NoteVersions
    }
    // getters
    const unsigned int& getNb(){return nb;}//!getter de nb
    const unsigned int& getNbMax(){return nbMax;}//!getter de nbMax
    /*!
     * \brief addNote ajoute une note à la fin du tableau
     * \param N Note à ajouter
     */
    void addNote(Note* N);
    /*!
     * \brief Méthode qui ajoute une note (dernière version)
     * en tête de la liste.
     * \param N Note à ajouter
     */
    void updateNewVersion(Note* N);

    /*!
     * \brief restoreVersion permet de restaurer une version existante d'une note
     * et de la placer comme version courante.
     * \param N version à restaurer
     */
    void restoreVersion(Note * N);

    /*!
     * \brief La classe iterator sert à parcourir les éléments de la classe
     * sans exposer la structure
     */
    class iterator{
        friend class NoteVersions;//!amitié avec la classe à parcourir
    private:
        unsigned int nbRemain;//!nombre d'éléments restant à parcourir
        Note** currentV;//!élément courant
        iterator(Note** c, unsigned int nb):nbRemain(nb), currentV(c){}//!constructeur de l'iterator
    public:
        unsigned int getNbRemain()const{return nbRemain;}//!getter de nbRemain
        /*!
         * \brief isDone savoir s'il reste des éléments à parcourir
         * \return bool dépendant de la valeur de nbRemain
         */
        bool isDone(){return nbRemain==0;}
        /*!
         * \brief isNext passe à l'élément suivant si c'est possible.
         */
        void isNext(){
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            currentV++; nbRemain--;
        }
        /*!
         * \brief current retourne l'élément cournat si c'est possible
         * \return current
         */
        Note& current(){
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            return **currentV;
        }
    };
    /*!
     * \brief getIterator retourne un iterator pour parcourir les versions
     * \return un iterator
     */
    iterator getIterator(){
        return iterator(versions, nb);
    }

};

/*!
 * \brief La classe NoteManager sert à gérer et stocker les différentes NotesVersions
 */
class NoteManager {
private :
    NoteVersions ** notes;//!tableau des NoteVersions
    unsigned int nb;//!nombre de NoteVersions
    unsigned int nbMax;//!nombre max de NoteVersions
public :
    NoteManager(NoteVersions ** note = new NoteVersions*[0], unsigned int n = 0, unsigned int nM = 0) : notes(new NoteVersions*[nM]), nb(n), nbMax(nM){
        //copie du tableau en paramètre.
        for (unsigned int i = 0 ; i < n ; i++){
            notes[i] = note[i];
        }
    }//!consturcteur de NoteManager
    // getters
    const unsigned int& getNb(){return nb;}//!getter de nb
    const unsigned int& getNbMax(){return nbMax;}//!getter de nbMax
    /*!
     * \brief addNoteVersion permet d'ajouter une NoteVersions dans le tableau
     * \param NV NoteVersions à ajouter.
     */
    void addNoteVersion(NoteVersions *NV);

    /*!
     * \brief La classe iterator sert à parcourir les éléments de la classe
     * sans exposer la structure
     */
    class iterator{
        friend class NoteManager;//!amitié avec la classe à parcourir
    private:
        unsigned int nbRemain;//!nombre d'éléments restant à parcourir
        NoteVersions** currentN;//!élément courant.
        iterator(NoteVersions** c, unsigned int nb):nbRemain(nb), currentN(c){}//!constructeur de l'iterator
    public:
        unsigned int getNbRemain()const{return nbRemain;}//!getter de nbRemain
        bool isDone(){return nbRemain==0;}//!permet de savoir d'il reste des éléments à parcourir
        /*!
         * \brief isNext passe à l'élément suivant
         */
        void isNext(){
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            currentN++; nbRemain--;
        }
        /*!
         * \brief current retourne l'élément courant
         * \return current
         */
        NoteVersions& current(){
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            return **currentN;
        }
    };
    /*!
     * \brief getIterator retourne un iterator pour parcourir les éléments du tableau.
     * \return iterator
     */
    iterator getIterator(){
        return iterator(notes, nb);
    }
};

/*!
 * \brief La classe Article représente les article, identifiés par
 * un texte en supplément des attirbuts de Note.
 */
class Article : public Note {
private :
    string text;//!texte de l'article
public :
    Article(const string& i, const string& t, tm* dC, tm* dLU, bool a, const string& s)
        : Note(i, t, dC, dLU, a), text(s){}//!constructeur de l'article
    //getters
    const string& getText(){return text;}//!getter de text
    //setters
    void setText(string& t){text = t;}//!setter de text
    /*!
     * \brief afficheSuite surcharge pour l'affichage
     * \param f flot de sortie
     * \return flot de sortie
     */
    ostream& afficheSuite(ostream& f){
        f<<"Text : "<<getText()<<endl;
        return f;
    }
};

/*!
 * \brief The Task class
 */
class Task : public Note {
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

/*!
 * \brief The TaskWithPriority class
 */
class TaskWithPriority : public Task {
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

/*!
 * \brief The TaskWithDeadline class
 */
class TaskWithDeadline : public Task {
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

/*!
 * \brief The OtherNote class
 */
class OtherNote : public Note{
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


//----Classes de Relations----//

/*!
 * \brief La classe Couple représente une liaison entre 2 notes.
 * La note choisie devra toujours être le premier élément du
 * tableau tab de la classe NotesVersions (première version)
 */
class Couple {
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

/*!
 * \brief The Relation class
 */
class Relation {
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

/*!
 * \brief La classe RelationManager permet de gérer l'ensemble des relations, c'est un singleton.
 */
class RelationManager {
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


//--------------------------------//

//Méthodes externes aux classes

Relation &getRelations(Note* N);


//--------------------------------//

//redéfinition des opérateurs

ostream& operator<< (ostream& f, const tm* tps); //necessiare pour afficher les heures de façon stylée
/*La redéfiniton de l'opérateur << est nécessaire pour les
 * enum car sinon lors de l'affichage, il n'affiche pas le nom de la variable
 * mais l'entier associé.
 * Exemple :
 * cout<<waiting affiche : 0
 * cout<<doing affiche : 1, etc...
 */
ostream& operator<< (ostream& f, const TaskStatus& S);
ostream& operator<< (ostream& f, const OtherNoteType& T);

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
