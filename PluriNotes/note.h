#ifndef NOTE_H
#define NOTE_H


#include "json.h"
#include "exception.h"






using json = nlohmann::json;
using namespace std;

//Définition des énumérations

enum TaskStatus{ waiting, doing, done}; //pour le statut d'un objet Task
enum OtherNoteType{audio, video, image}; //Pour le type d'un objet qui comprend un média
enum RelationOrientation{oriented, non_oriented}; //pour l'orientation des relations entre couples de Notes
enum NoteType{A, T, TWP, TWD, ON};

const QString DATEFORMAT = "%d-%m-%Y %H-%M-%S";

//----Classes de Notes----//

/*!
 * \brief La classe Note est la classe mère de tous les autres types
 * de notes. elle est caractérisée par un identificateur, un titre,
 * une date de création, une date de dernière modification, et un statut.
 */
class Note {
private :
    QString identifier;//!identifant de la note
    QString title;//!titre de la note
    tm* dateCreation;//!date de création de la note
    tm* dateLastUpdate;//!date de la dernière mise à jour de la note
    bool active;//! statut de la note
protected:
    Note(const QString& i, const QString& t, tm* dC, tm* dLU, bool a)
        : identifier(i), title(t), dateCreation(dC), dateLastUpdate(dLU), active(a){}//!constructeur de la classe
public :
    //getters
    const QString& getIdentifier(){return identifier;}//!getter d'identifier
    const QString& getTitle(){return title;}//!getter de title
    const tm* getDateCreation(){return dateCreation;}//!getter de dateCreation
    const tm* getDateLastUpdate(){return dateLastUpdate;}//!getter de dateLastUpdate
    const bool& getActive(){return active;}//!getter de active
    /*!
     * \brief getActiveString retourne la valeur de active
     * sous forme de chaîne de caractères.
     * \return (string)active.
     */
    const QString& getActiveString(){
        QString *act =  new QString;
        if (active) {
            *act = "Active";
        }else{
            *act = "Inactive";
        }
        return *act;
    }
    //setters
    void setTitle(QString& t){title = t;}//!setter de title
    void setDateCreation(tm* dC){dateCreation = dC;}//!setter de dateCreation
    void setDateLastUpdate(tm* dLU){dateLastUpdate = dLU;}//!setter de datelastUpdate
    void setActive(bool a){active = a;}//!setter de active
    /*!
     * \brief afficheSuite définition de la méthode affiche suite vouée à être
     * surchargée par les classes filles
     * \param f flux de sortie
     * \return flux de sortie
     */
    virtual ostream& afficheSuite(ostream& f){return f;}
    void affiche(ostream& f);

    /*!
     * \brief Utility method to convert a QString into a date
     *
     * \see DATEFORMAT
     * \param s the QString to parse
     * \return the date associated to the QString
     */


    void fromJson(json j);
    json toJson();

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
    NoteType type;
public :
    NoteVersions(Note ** t = new Note*[0], unsigned int n = 0, unsigned int nM = 0, NoteType ty = A)
        : versions(new Note*[nM]), nb(n), nbMax(nM), type(ty){
        //copie du tableau en paramètre.
        for (unsigned int i = 0 ; i < n ; i++){
            versions[i] = t[i];
        }//!constructeur de NoteVersions
    }
    // getters
    const unsigned int& getNb(){return nb;}//!getter de nb
    const unsigned int& getNbMax(){return nbMax;}//!getter de nbMax
    const NoteType& getType(){return type;}
    //setters
    void setNoteType(NoteType& t){type = t;}
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



    json toJson();

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
    QString directory;
public :
    //Attention, pensez à changer le chemin de filename, normalement vous devez avoir ce chemin aussi sur votre pc.
    NoteManager(NoteVersions ** note = new NoteVersions*[0], unsigned int n = 0, unsigned int nM = 0, QString dir = "C:\\Users\\Public\\Documents")
        : notes(new NoteVersions*[nM]), nb(n), nbMax(nM), directory(dir){
        //copie du tableau en paramètre.
        for (unsigned int i = 0 ; i < n ; i++){
            notes[i] = note[i];
        }
    }//!consturcteur de NoteManager
    NoteManager( QString dir = "C:\\Users\\Public\\Documents\\")
        : notes(new NoteVersions*[0]), nb(0), nbMax(0), directory(dir){
    }//! overload du constructeur pour pouvoir facilement modifier le directory.

    // getters
    const unsigned int& getNb(){return nb;}//!getter de nb
    const unsigned int& getNbMax(){return nbMax;}//!getter de nbMax
    /*!
     * \brief addNoteVersion permet d'ajouter une NoteVersions dans le tableau
     * \param NV NoteVersions à ajouter.
     */
    void addNoteVersion(NoteVersions *NV);


    json toJson();
    void save();
    NoteManager load();

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
ostream& operator<< (ostream& f, const RelationOrientation& R);
ostream& operator<< (ostream& f, const QString& S);
ostream& operator<< (ostream& f, const tm* tps);
//ostream& operator<< (ostream& f, tm*& D);

ostream& operator << (ostream& f, Note& N);
ostream& operator<< (ostream& f, NoteVersions& V);
ostream& operator<< (ostream& f, NoteManager& NM);

#endif // NOTE_H
