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
    QString label;//!label du couple
    Note* x;//!Note du couple
    Note* y;//!Not du couple
public :
    Couple(const QString& l, Note* x , Note* y): label(l), x(x), y(y) {}//!Constructeur de Couple
    Couple(): label(""), x(new Note), y(new Note){}//!redéfinition du constructeur
    //getters
    const QString& getLabel() const{return label;}//!getter de label
    const Note* getX() const{return x;}//!getter de x
    const Note* getY() const{return y;}//!getter de y

    QString& getLabel(){return label;}//!getter de label
    Note* getX(){return x;}//!getter de x
    Note* getY(){return y;}//!getter de y
    //setters
    void setX(Note * Xs){x = Xs;}//!setter de x
    void setY(Note * Ys){y = Ys;}//!setter de y

    /*!
     * \brief toJson insère le contenu d'un objet Couple dans un objet de
     * type json
     * \return Le fichier json contenant les informations du Couple
    */
    json toJson();

    /*!
     * \brief fromJson ajoute les informations contenues dans le
     * fichier json à l'intérieur du Couple
     * \param j l'objet de type json
     */
    static Couple& fromJson(json j);
};

/*!
 * \brief La classe Relation
 */
class Relation {
private :
    Couple ** couples;//!tableau de pointeur de couples
    unsigned int nb;//!nombre de couples dnas le tableau
    unsigned int nbMax;//!nombre maximal de couples
    QString title;//!titre de la relation
    QString description;//!description de la relation
    RelationOrientation orientation;//!orientation de la relation
public :
    Relation(Couple ** c = new Couple*[0], unsigned int n = 0, unsigned int nM = 0, const QString& t = "", const QString& d = "", const RelationOrientation& o = oriented)
        : couples(new Couple*[nM]), nb(n), nbMax(nM), title(t), description(d), orientation(o){
        for (unsigned int i = 0 ; i< n ; i++){
            couples[i] = c[i];
        }
    }//!constructeur de realtion
    Relation(const RelationOrientation& o)
        : couples(new Couple*[0]), nb(0), nbMax(0), title(""), description(""), orientation(o){
    }//!redéfinition du consturcteur de Relation

    virtual ~Relation(){}//!destructeur de Relation

    //getters
    const unsigned int& getNb() const{return nb;}//!getter de nb
    const unsigned int& getNbMax() const{return nbMax;}//!getter de nbMax
    const QString& getTitle() const{return title;}//!getter de title
    const QString& getDescription() const{return description;}//!getter de description
    const RelationOrientation& getOrientation() const{return orientation;}//!getter de orientation
    unsigned int& getNb(){return nb;}//!getter de  nb
    unsigned int& getNbMax(){return nbMax;}//!getter de nbMax
    QString& getTitle(){return title;}//!getter de title
    QString& getDescription(){return description;}//!getter de description
    RelationOrientation& getOrientation(){return orientation;}//!getter de orientation

    QString getOrientationQS(){
        switch(orientation){
        case oriented:
            return "orientée";
        case non_oriented:
            return "non orientée";
        }
        return "orientée";
    }//!getter de orientation sous forme de QString

    //setters
    void setNb(unsigned int n){nb = n;}//!setter de nb
    void setNbMax(unsigned int nM){nbMax = nM;}//!setter de nbMax
    void setTitle(const QString& t){title = t;}//!setter de title
    void setDescription(const QString& d){description = d;}//!setter de description
    void setOrientation(RelationOrientation& ori){orientation = ori;}//!setter de orientation
    //void setCouple(Couple ** C){couples = C;} // TO DELETE ? (NOT USED)
    //autres méthodes :
    /*!
     * \brief addCouple ajout eun couple à la relation
     * \param c le couple à ajouter
     */
    void addCouple(Couple * c);

    /*!
     * \brief deleteCouple Supprime le couple en paramètre de la relation
     * \param c le couple à supprimer
     */
    void deleteCouple(Couple * c);

    /*!
     * \brief fromJson ajoute les informations contenues dans le
     * fichier json à l'intérieur du Relation
     * \param j l'objet de type json
     */
    static Relation& fromJson(json j);


    /*!
     * \brief toJson insère le contenu d'un objet Relation dans un objet de
     * type json
     * \return Le fichier json contenant les informations de la Relation
    */
    json toJson();

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
                throw NotesException("Error, no more versions of notes");
            currentR++; nbRemain--;
        }
        Couple& current(){ // = getCurrentR
            if(isDone())
                throw NotesException("Error, no more versions of notes");
            return **currentR;
        }
        Couple* currentPtr(){
            if(isDone()){
                throw NotesException("Error, no more versions of notes");
            }
            return *currentR;
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
private :
    static RelationManager * uniqueInstance;//!Instance unique du singleton
    static Relation ** relations;//!tableau de pointeurs de relations
    static unsigned int nb;//!nombre de relations dans le tableau
    static unsigned int nbMax;//!nombre maximal de relations
    static QString directory;//!chemin vers l'emplacement de sauvegarde des relations
    RelationManager(Relation ** r = new Relation*[0], unsigned int n = 0, unsigned int nM = 0){
        nb = n;
        nbMax = nM;
        relations = new Relation*[nM];
        for (unsigned int i = 0 ; i< n ; i++){
            relations[i] = r[i];
        }
    }//!constructeur de RelationManager
    /*!
     * \brief ~RelationManager destructeur de Relation Manager
     */
    virtual ~RelationManager();
    /*!
     * \brief operator = redéfinition de l'opérateur d'affectation
     * \param RM le RM à affecter
     */
    RelationManager& operator= (const RelationManager& RM);
    /*!
     * \brief RelationManager constructeur par recopie de RM
     * \param RM le RM à recopier
     */
    RelationManager(const RelationManager& RM);

public :
    /*!
     * \brief getRelationManager alloue de la mémoire pour l'instance unique et la retourne
     * \return l'unique instance de RM
     */
    static RelationManager& getRelationManager(Relation ** r, unsigned int n, unsigned int nM);
    /*!
     * \brief getRelationManager redéfinition de la méthode pour récupérer un RM
     */
    static RelationManager& getRelationManager();
    /*!
     * \brief freeRelationManager libère l'espace mémoire utilisé par le RM
     */
    static void freeRelationManager();

    //getters
    static unsigned int& getNb(){return nb;}//!getter de nb
    static unsigned int& getNbMax(){return nbMax;}//!getter de nbMax

    //setters
    static void setNb(unsigned int n){nb = n;}//!setter de nb
    static void setNbMax(unsigned int nM){nbMax = nM;}//!setter de nbMax

    /*!
     * \brief addRelation ajoute une relation au tableau de relations
     * \param R la relation à ajouter.
     */
    static void addRelation(Relation* R);


    static void deleteRelation();

    //faire un iterator
    //static Relation* getNthElement(unsigned int n){return relations[n];}

    /*!
     * \brief getDescendants renvoie l'ensemble des descendants d'une note
     * \param N La note en question
     * \param order l'ordre jusqu'auquel on veut chercher des descendants
     * \return un map de la forme <Note* ,  ordre auquel la Note* à été trouvée>
     */
    static map<Note *, int> getDescendants(Note* N, int order = 2);

    /*!
     * \brief getAscendants renvoie l'ensemble des ascendants d'une note
     * \param N La note en question
     * \param order l'ordre jusqu'auquel on veut chercher des ascendants
     * \return un map de la forme <Note* ,  ordre auquel la Note* à été trouvée>
     */
    static map<Note *, int> getAscendants(Note* N, int order = 2);

    /*!
     * \brief toJson insère le contenu d'un objet RelationManager dans un objet de
     * type json
     * \return Le fichier json contenant les informations du RelationManager
    */
    json toJson();

    /*!
     * \brief save Sauvegarde les informations contenues dans le RelationManager dans la mémoire à l'endroit ou est défini directory
     */
    void save();
    /*!
     * \brief load récupère les informations contenues dans le fichier directory/relations.json
     */
    void load();


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
                throw NotesException("Error, no more versions of notes RM");
            currentRM++;
            nbRemain--;
        }
        Relation& current(){
            if(isDone())
                throw NotesException("Error, no more versions of notes RM");
            return **currentRM;
        }
    };

    static iterator getIterator(){
        return iterator(relations, nb);
    }

};


class Reference : public Relation {
private :
    static Reference * uniqueRef;//!instance unique de référence
    Reference(Couple ** c = new Couple*[0], unsigned int n = 0, unsigned int nM = 0, const QString& t = "References", const QString& d = "Cette realtion contient les références", const RelationOrientation& o = oriented)
        : Relation(c, n, nM, t, d, o){}//!construteur de Reference
    ~Reference(){}//!destructeur de Reference
    /*!
     * \brief Reference Constructeur par recopie de Reference
     * \param r la reference à copier
     */
    Reference(const Reference& r);
    /*!
     * \brief operator = Redéfinition de l'opérateur d'affectation
     * \param r la Referecne à affecter
     */
    Reference& operator=(const Reference& r);

public :
    /*!
     * \brief getRef alloue de la mémoire à l'unique instance et la retourne
     * \return l'unique instance
     */
    static Reference& getRef();
    /*!
     * \brief freeRef libère l'espace mémoire occupé par l'unique instance
     */
    static void freeRef();

    /*!
     * \brief updateRefs Mets à jour les references en parcourrant l'ensemble des notes
     */
    static void updateRefs();

    /*!
     * \brief isNoteReferenced permet de vérifier si une Note
     *  se trouve dans une Référence
     * \param N Note
     */
    static bool isNoteReferenced(Note * N);

    /*!
     * \brief getReferencesNote retourne les références de la Note en paramètre
     * \param N La note en question
     */
    void getReferencesNote(Note * N);

    /*!
     * \brief getReferences retourne l'ensemble des références de l'ensembled des notes
     */
    void getReferences();

    /*!
     * \brief operator * retourne la valeur pointée par l'unique instance
     */
    Reference& operator* (){return *uniqueRef;}
};



//--------------------------------//

//Méthodes externes aux classes

Relation &getRelations(Note* N);

//redéfinition des opérateurs

ostream& operator<< (ostream& f, Relation& R);
ostream& operator<< (ostream& f, RelationManager& RM);
ostream& operator<< (ostream& f, Couple& C);

ostream& operator<< (ostream& f, map<Note*, int> M);


#endif // RELATION_H
