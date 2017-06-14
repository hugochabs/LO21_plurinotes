#ifndef NOTE_H
#define NOTE_H


#include "json.h"
#include "exception.h"
//#include "contener.h"
#include <QDateTime>

using json = nlohmann::json;
using namespace std;
//using namespace TD;

//Définition des énumérations
/*!
 * \brief L'enum TaskStatus sert à définir le statut d'un objet Task
 */
enum TaskStatus{waiting, doing, done};
/*!
 * \brief L'enum OtherNoteType sert à définir le type de note contenant un média
 */
enum OtherNoteType{audio, video, image};
/*!
 * \brief L'enum  RelationOrientation sert à définir l'orientation d'une relation
 */
enum RelationOrientation{oriented, non_oriented};
/*!
 * \brief L'enum NoteType sert à définir le type de Notes contenues dans une objet NoteVersions
 */
enum NoteType{A, T, TWP, TWD, ON};
/*!
 * \brief L'enum Notestatus sert à définir le statut d'une Note
 */
enum NoteStatus{active, archived, trash};


/*!
 * \brief DATEFORMAT Format d'affichage des dates
 */
const QString DATEFORMAT = "%d/%m/%Y %H:%M:%S";


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
    NoteStatus noteStatus;//! statut de la note
protected:

public :
    /*!
     * \brief Note constructeur de la classe Note
     */
    Note(const QString& i, const QString& t, tm* dC, tm* dLU, NoteStatus a)
        : identifier(i), title(t), dateCreation(dC), dateLastUpdate(dLU), noteStatus(a){}
    Note(): identifier(""), title(""), dateCreation(new tm), dateLastUpdate(new tm), noteStatus(active){}//!redéfinition du constructeur

    /*!
     * \brief ~Note destructeur de la classe
     */
    virtual ~Note(){}
    //getters
    const QString& getIdentifier() const{return identifier;}//!getter d'identifier
    QString& getIdentifier(){return identifier;}//!getter d'identifier
    const QString& getTitle() const{return title;}//!getter de title
    QString& getTitle(){return title;}//!getter de title
    tm* getDateCreation(){return dateCreation;}//!getter de dateCreation
    const tm* getDateCreation() const{return dateCreation;}//!getter de dateCreation
    tm* getDateLastUpdate(){return dateLastUpdate;}//!getter de dateLastUpdate
    const tm* getDateLastUpdate() const{return dateLastUpdate;}//!getter de dateLastUpdate
    NoteStatus getNoteStatus(){return noteStatus;}//!getter de noteStatus
    const NoteStatus& getNoteStatus() const{return noteStatus;}//!getter de noteStatus
    /*!
     * \brief getNoteStatusString retourne la valeur de NoteStatus
     * sous forme de chaîne de caractères.
     * \return (string)noteStatus.
     */
    QString getNoteStatusString(){
        switch(noteStatus){
        case NoteStatus::active:
            return "active";
        case NoteStatus::archived:
            return "archived";
        case NoteStatus::trash:
            return "trash";
        }
        return "active";
    }
    //setters
    void setIdentifier(QString& i){identifier = i;}//!setter de identifier
    void setTitle(QString& t){title = t;}//!setter de title
    void setDateCreation(tm* dC){dateCreation = dC;}//!setter de dateCreation
    void setDateLastUpdate(tm* dLU){dateLastUpdate = dLU;}//!setter de datelastUpdate
    void setNoteStatus(NoteStatus a){noteStatus = a;}//!setter de noteStatus

    //autres méthodes
    static QString createID(const QString& title, unsigned int version){
        QString id = title+"V"+QString::number(version+1);
        return id;
    }
    QString getTypeOfNote();
    /*!
     * \brief afficheSuite définition de la méthode affiche suite vouée à être
     * surchargée par les classes filles
     * \param f flux de sortie
     * \return flux de sortie
     */
    virtual ostream& afficheSuite(ostream& f){return f;}

    /*!
     * \brief affiche Fonction d'affichage d'une Note
     * \param f flux de sortie
     */
    void affiche(ostream& f);

    /*!
     * \brief Méthode de conversion d'un QString en date
     * \see DATEFORMAT
     * \param s le QString à convertir
     * \return la date associée au QString
     */
    static tm * dateFromQString(const QString& s){
        struct tm* date = new tm;
        strptime(s.toStdString().c_str(), DATEFORMAT.toStdString().c_str(), date);
        return date;
    }


    /*!
     * \brief Méthode pour convertir une date en QString
     * \see DATEFORMAT
     * \param date la date à transformer
     * \return le QString associé à la date
     */
    static const QString& QStringFromDate(const struct tm* date){
        char date_char[64];
        strftime(date_char, sizeof(date_char), DATEFORMAT.toStdString().c_str(), date);
        QString * res = new QString(date_char);
        return *res;
    }
    /*!
     * \brief QdatefromDate Transforme un tm* en QDateTime
     * \param date date à convertir
     * \return la date sous format QDateTime
     */
    static const QDateTime* QdatefromDate(const struct tm* date){
        int y = date->tm_year + 1900;
        int mo = date->tm_mon + 1;
        int day = date->tm_mday;
        int min = date->tm_min;
        int hour = date->tm_hour;
        int sec = date->tm_sec;
        QTime t(hour, min ,sec);
        QDate d(y, mo, day);
        QDateTime& dt = *new QDateTime(d, t);
        return &dt;
    }

    /*!
     * \brief fromJson Renvoie une référence sur une Note qui aura été
     * créée à partir d'un objet json.
     * \param j l'objet de type json
     * \return La note créée
     */
    static Note& fromJson(json j);

    /*!
     * \brief toJson insère le contenu d'un objet Note dans un objet de
     * type json
     * \return Le fichier json contenant les informations de la note
     */
    virtual json &toJson();

    /*!
     * \brief getStringAttributes Renvoie une concaténationdes attributs de la note qui sont des Qstrings
     * \return Concaténation des attributs QString
     */
    virtual QString& getStringAttributes();
    /*!
     * \brief getReferences Renvoie l'ensemble des notes référencées dans la note
     * \return le vector contenant les notes référencées
     */
    vector<Note> getReferences();
};



/*!
 * \brief Classe chargée de gérer toutes les versions d'un même fichier, regroupées dans un tableau
 * de pointeurs. Pour des questions de simplicité la version la plus récente est en tête
 * de tableau.
*/
class NoteVersions {
private :
    Note** versions;//!tableau de pointeurs de notes regroupant les versions
    unsigned int nb;//!nombre de versions
    unsigned int nbMax;//!nombre max de versions
    NoteType type;//!Type des Notes contenues dans ce NoteVersions
public :
    NoteVersions(Note ** t = new Note*[0], unsigned int n = 0, unsigned int nM = 0, NoteType ty = A)
        : versions(new Note*[nM]), nb(n), nbMax(nM), type(ty){
        //copie du tableau en paramètre.
        for (unsigned int i = 0 ; i < n ; i++){
            versions[i] = t[i];
        }
    }//!constructeur de NoteVersions
    /*!
     * \brief ~NoteVersions Destructeur de la classe
     */
    virtual ~NoteVersions(){
    }

    // getters
    const unsigned int& getNb() const{return nb;}//!getter de nb
    const unsigned int& getNbMax() const{return nbMax;}//!getter de nbMax
    const NoteType& getType() const{return type;}//!getter de type
    // getter const
    Note** getVersions(){return versions;} //! getter de versions
    const unsigned int& getNb(){return nb;}//!getter de nb
    const unsigned int& getNbMax(){return nbMax;}//!getter de nbMax
    const NoteType& getType(){return type;}//!getter de type
    QString getTypeQS();//!Renvoie le type sous forme de QString

    //setters
    void setNoteType(NoteType t){type = t;}//!setter de type
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
     * \brief toJson insère le contenu d'un objet NoteVersions dans un objet de
     * type json
     * \return Le fichier json contenant les informations de la NoteVersions
     */
    json toJson();

    /*!
     * \brief fromJson Renvoie une référence sur une NoteVersions qui aura été
     * créée à partir d'un objet json.
     * \param j l'objet de type json
     * \return La NoteVersions créée
     */
    static NoteVersions& fromJson(json j);

    /*!
     * \brief La classe iterator sert à parcourir les éléments de la classe
     * sans exposer la structure
     */
    class iterator{
        friend class NoteVersions;      //!amitié avec la classe à parcourir
    private:
        unsigned int nbRemain;          //!nombre d'éléments restant à parcourir
        Note** currentV;                //!élément courant
        iterator(Note** c, unsigned int nb):nbRemain(nb), currentV(c){}     //!constructeur de l'iterator
    public:
        unsigned int getNbRemain()const{return nbRemain;}       //!getter de nbRemain
        /*!
         * \brief isDone savoir s'il reste des éléments à parcourir
         * \return bool dépendant de la valeur de nbRemain
         */
        bool isDone(){return nbRemain==0;}
        bool isDone1(){if(nbRemain==1)return true; else return false;}
        /*!
         * \brief isNext passe à l'élément suivant si c'est possible.
         */
        void isNext(){
            if(isDone())
                throw NotesException("Error, no more versions of notes from NV");
            currentV++;
            nbRemain--;
        }
        /*!
         * \brief current retourne l'élément courant si c'est possible
         * \return current
         */
        Note& current(){
            if(isDone())
                throw NotesException("Error, no more versions of notes from NV current");
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
class NoteManager{
private :
    NoteVersions** notes;       //!tableau des NoteVersions
    unsigned int nb;            //!nombre de NoteVersions
    unsigned int nbMax;         //!nombre max de NoteVersions
    QString directory;
    static NoteManager * uniqueInstance;
    //Attention, pensez à changer le chemin de filename, normalement vous devez avoir ce chemin aussi sur votre pc.
    //Directory de Guillaume : "/home/guilllaume/Documents/UTC/GI02/LO21/LO21_plurinotes/LO21_plurinotes/PluriNotes2/"
    //Directory Hugo :
    //Directory Garance :
    NoteManager(NoteVersions ** note = new NoteVersions*[0], unsigned int n = 0, unsigned int nM = 0, QString dir = "/home/hugo/")
        :notes(new NoteVersions*[nM]),nb(n),nbMax(nM), directory(dir){
        //copie du tableau en paramètre.
        for (unsigned int i = 0 ; i < n ; i++){
            notes[i] = note[i];
        }
    }//!consturcteur de NoteManager
    NoteManager( QString dir = "/home/hugo/"):nb(0),nbMax(0),notes(new NoteVersions*[0]), directory(dir){
    }//! overload du constructeur pour pouvoir facilement modifier le directory.
    /*!
     * \brief NoteManager constructeur par recopie
     * \param nm NoteManager à recopier
     */
    NoteManager(const NoteManager& nm);
    /*!
     * \brief operator = redéfirition de l'opérateur d'affectation
     * \param nm Le NoteManager à affecter
     * \return
     */
    NoteManager& operator=(const NoteManager &nm);
    /*!
     * \brief Destructeur de la classe
     */
    ~NoteManager();

public :
    /*!
     * \brief freeNoteManager désalloue l'espace mémoire du singleton
     */
    static void freeNoteManager();
    /*!
     * \brief getNoteManager alloue l'espace mémoire du singleton et le renvoie
     * \return pointeur vers l'unique instance
     */
    static NoteManager& getNoteManager(NoteVersions ** nv = new NoteVersions*[0], unsigned int n = 0, unsigned int nM = 0);
    // getters
    const unsigned int& getNb() const{return nb;}//!getter de nb
    const unsigned int& getNbMax() const{return nbMax;}//!getter de nbMax

    /*!
     * \brief addNoteVersion permet d'ajouter une NoteVersions dans le tableau
     * \param NV NoteVersions à ajouter.
     */
    void addNoteVersion(NoteVersions *NV);

    /*! \brief getNVfromNote permet de récupérer le NoteVersions
     * en fonction de la Note passée en paramètres
     * \param N note dont on veut récupérer le NoteVersions
     */
    NoteVersions* getNVfromNote(Note* N);

    /*!
     * \brief archiveNoteVersions permet d'archiver une note
     * ainsi que toutes ses versions (= archiver une NoteVersions)
     * \param NV NoteVersions à archiver
     */
    void archiveNoteVersions(NoteVersions*NV);

    /*!
     * \brief restoreNoteVersions permet de restaurer une note
     * ainsi que toutes ses versions (= restaurer une NoteVersions)
     * \param NV NoteVersions à archiver
     */
    void restoreNoteVersions(NoteVersions *NV);

    /*!
     * \brief deleteNoteVersions permet de supprimer une note
     * ainsi que toutes ses versions. (= mettre à la corbeille si possible, soit si la Note
     * n'apparaît pas dans une Référence, et l'archiver sinon)
     * \param N note à supprimer
     */
    void deleteNoteVersions(Note* N);

    /*!
     * \brief putNVToTrash permet de mettre dans la corbeille une note
     * ainsi que toutes ses versions.
     * \param N note à mettre à la corbeille
     */
    void putNVToTrash(NoteVersions* NV);

    /*!
     * \brief deleteNoteCouples permet de supprimer tous les Couples
     * des Relations dans lesquels une note passée en paramètre se trouve.
     * \param N note que l'on veut supprimer
     */
    void deleteNoteCouples(Note* N);


    /*!
     * \brief toJson insère le contenu d'un objet NoteManager dans un objet de
     * type json
     * \return Le fichier json contenant les informations du NoteManager
    */
    json toJson();

    /*!
     * \brief fromJson ajoute les informations contenues dans le
     * fichier json à l'intérieur du tableau de NoteVersions
     * \param j l'objet de type json
     */
    void fromJson(json j);
    /*!
     * \brief save Méthode permettant de sauvegarder en mémoire les
     * informations sur les Notes dans un fichier json
     */
    void save();
    /*!
     * \brief load méthode permettant de récupérer les informations stockées en
     * mémoire dans le fichier json
     */
    void load();
    /*!
     * \brief searchNote retourne un pointeur vers la Note
     * dont l'id est passé en paramètre
     * \param id identificateur de la note à chercher
     * \return La Note correspondante
     */
    static Note *searchNote(QString& id);

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
                throw NotesException("Error, no more versions of notes NM");
            currentN++; nbRemain--;
        }
        /*!
         * \brief current retourne l'élément courant
         * \return current
         */
        NoteVersions& current(){
            if(isDone())
                throw NotesException("Error, no more versions of notes NM current");
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

    iterator end(){
        return iterator(notes+nb-1,1);
    }
};



//redéfinition des opérateurs

ostream& operator<< (ostream& f, const tm* t);
ostream& operator<< (ostream& f, const TaskStatus& S);
ostream& operator<< (ostream& f, const OtherNoteType& T);
ostream& operator<< (ostream& f, const RelationOrientation& R);
ostream& operator<< (ostream& f, const QString& S);
ostream& operator<< (ostream& f, const tm* tps);
ostream& operator << (ostream& f, Note& N);
ostream& operator<< (ostream& f, NoteVersions& V);
ostream& operator<< (ostream& f, NoteManager& NM);

#endif // NOTE_H
