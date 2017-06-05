#ifndef RELATION_H
#define RELATION_H


#include "notefille.h"

using namespace std;

//----Classes de Relations----//

/*!
 * \brief La classe Couple représente une liaison entre 2 notes.
 * La note choisie devra toujours être le premier élément du
 * tableau tab de la classe NotesVersions (première version)
 */
class Couple {
private :
    QString label;
    Note* x;
    Note* y;
public :
    Couple(const QString& l, Note* x , Note* y): label(l), x(x), y(y) {}
    //getters
    const QString& getLabel(){return label;}
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
    QString title;
    QString description;
    RelationOrientation orientation;
public :
    Relation(Couple ** c = new Couple*[0], unsigned int n = 0, unsigned int nM = 0, const QString& t = "", const QString& d = "", const RelationOrientation& o = oriented)
        : couples(new Couple*[nM]), nb(n), nbMax(nM), title(t), description(d), orientation(o){
        for (unsigned int i = 0 ; i< n ; i++){
            couples[i] = c[i];
        }
    }
    //getters
    Couple* getNthElement(unsigned int n){return couples[n];}
    const unsigned int& getNb(){return nb;}
    const unsigned int& getNbMax(){return nbMax;}
    const QString& getTitle(){return title;}
    const QString& getDescription(){return description;}
    RelationOrientation& getOrientation(){return orientation;}
    //setters
    void setNb(unsigned int n){nb = n;}
    void setNbMax(unsigned int nM){nbMax = nM;}
    void setTitle(const QString& t){title = t;}
    void setDescription(const QString& d){description = d;}
    void setOrientation(RelationOrientation& ori){orientation = ori;}
    void setCouple(Couple ** C){couples = C;} // TO DELETE ? (NOT USED)
    void addCouple(Couple * c);
    void deleteCouple(Couple * c); // TODO

    class iterator{
        friend class Relation;
    private:
        unsigned int nbRemain;
        Couple** currentR;      // = currentCouple ?
        iterator(Couple** R, unsigned int nb):nbRemain(nb), currentR(R){}
    public:
        unsigned int getNbRemain()const{return nbRemain;}
        bool isDone(){return nbRemain==0;}
        void isNext(){
            if(isDone())
                // TODO change comments
                throw NotesException("Error, no more versions of notes");
            currentR++; nbRemain--;
        }
        Couple& current(){ // = getCurrentR
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
    bool operator= (const RelationManager& RM);
    RelationManager(const RelationManager& RM);

public :
    static RelationManager& getRelationManager(Relation ** r, unsigned int n, unsigned int nM);
    static RelationManager& getRelationManager();
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
        Relation** currentRM; // TODO CHANGE ??? iterate through Relation not RM !?
        iterator(Relation** R, unsigned int nb):nbRemain(nb), currentRM(R){}
    public:
        unsigned int getNbRemain()const{return nbRemain;}
        bool isDone(){return nbRemain==0;}
        void isNext(){
            if(isDone())
                // TODO change comments
                throw NotesException("Error, no more versions of notes");
            currentRM++;
            nbRemain--;
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

//redéfinition des opérateurs

ostream& operator<< (ostream& f, Relation& R);
ostream& operator<< (ostream& f, RelationManager& RM);
ostream& operator<< (ostream& f, Couple& C);



#endif // RELATION_H
