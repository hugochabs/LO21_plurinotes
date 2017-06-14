#ifndef NOTEFILLE_H
#define NOTEFILLE_H


#include "note.h"

using namespace std;

/*!
 * \brief La classe Article représente les article, identifiés par
 * un texte en supplément des attirbuts de Note.
 */
class Article : public Note {
private :
    QString text;//!texte de l'article
public :
    Article(const QString& i, const QString& t, tm* dC, tm* dLU, NoteStatus a, const QString& s)
        : Note(i, t, dC, dLU, a), text(s){}//!constructeur de l'article
    //getters
    const QString& getText() const{return text;}//!getter de text
    QString& getText(){return text;}//!getter de text

    //setters
    void setText(QString& t){text = t;}//!setter de text

    /*!
     * \brief afficheSuite surcharge pour l'affichage
     * \param f flot de sortie
     * \return flot de sortie
     */
    ostream& afficheSuite(ostream& f){
        f<<"Text\t: "<<getText()<<endl;
        return f;
    }

    /*!
     * \brief getStringAttributes Renvoie une concaténationdes attributs de la note qui sont des Qstrings
     * \return Concaténation des attributs QString
     */
    QString& getStringAttributes();

    /*!
     * \brief toJson insère le contenu d'un objet Note dans un objet de
     * type json
     * \return Le fichier json contenant les informations de la note
     */
    json& toJson();
    /*!
     * \brief fromJson Renvoie une référence sur un Article qui aura été
     * créée à partir d'un objet json.
     * \param j l'objet de type json
     * \return L'article créé
     */
    static Article& fromJson(json j);
};

/*!
 * \brief The Task class
 */
class Task : public Note {
private :
    QString action;//!action à réaliser
    TaskStatus status;//!statut de la tâche

public :
    Task(const QString& i, const QString& t, tm* dC,  tm* dLU,NoteStatus a, const QString& ac, TaskStatus s = waiting)
        : Note(i, t, dC, dLU, a), action(ac), status(s){}//!constructeur de Task
    //getters
    QString& getAction(){return action;}//!getter de action
    const QString& getAction() const{return action;}//!getter de action
    TaskStatus& getStatus(){return status;}//!getter de status
    const TaskStatus& getStatus() const{return status;}//!getter de status
    QString getStatusQS(){
        switch(status){
        case TaskStatus::doing:
            return "Doing";
        case TaskStatus::done :
            return "Done";
        case TaskStatus::waiting:
            return "Waiting";
        }
        return "Waiting";
    }//!Getter pour avoir status en QString

    static TaskStatus toTSfromQString(const QString& t){
        if(t=="waiting")
             return waiting;
         else if(t=="done")
             return done;
         else if(t=="en realisation")
             return doing;
    }//!getter de TaskStatus en QString

    //setters
    void setAction(QString& a){action = a;}//!setter de action
    void setStatus(TaskStatus& s){status = s;}//!setter de status

    /*!
     * \brief afficheSuite surcharge pour l'affichage
     * \param f flot de sortie
     * \return flot de sortie
     */
    ostream& afficheSuite(ostream& f){
        f<<"Action\t: "<<getAction()<<endl
        <<"Status\t: "<<getStatus()<<endl;
        return f;
    }
    /*!
     * \brief getStringAttributes Renvoie une concaténationdes attributs de la note qui sont des Qstrings
     * \return Concaténation des attributs QString
     */
    QString& getStringAttributes();

    /*!
     * \brief toJson insère le contenu d'un objet Note dans un objet de
     * type json
     * \return Le fichier json contenant les informations de la note
     */
    json& toJson();

    /*!
     * \brief fromJson Renvoie une référence sur une Task qui aura été
     * créée à partir d'un objet json.
     * \param j l'objet de type json
     * \return La task créée
     */
    static Task& fromJson(json j);
};

/*!
 * \brief The TaskWithPriority class
 */
class TaskWithPriority : public Task {
private :
    int priority;//!indice de priorité de la classe
public :
    TaskWithPriority(const QString& i, const QString& t,  tm* dC,tm* dLU, NoteStatus a, const QString& ac, TaskStatus s, int p)
        : Task(i, t, dC, dLU, a, ac, s), priority(p){}//!constructeur de TWP
    //getters
    int& getPriority(){return priority;}//!getter de priority
    const int& getPriority() const{return priority;}//!getter de priority
    QString getPriorityQS(){
        return QString::number(priority);
    }//!Conversion de priority en QString

    //setters
    void setPriority(int & p){priority = p;}//!setter de priority

    /*!
     * \brief afficheSuite surcharge pour l'affichage
     * \param f flot de sortie
     * \return flot de sortie
     */
    ostream& afficheSuite(ostream& f){
        f<<"Action : "<<getAction()<<endl
        <<"Status : "<<getStatus()<<endl
        <<"Priority : "<<getPriority()<<endl;
        return f;
    }

    /*!
     * \brief getStringAttributes Renvoie une concaténationdes attributs de la note qui sont des Qstrings
     * \return Concaténation des attributs QString
     */
    QString& getStringAttributes();

    /*!
     * \brief toJson insère le contenu d'un objet Note dans un objet de
     * type json
     * \return Le fichier json contenant les informations de la note
     */
    json& toJson();

    /*!
     * \brief fromJson Renvoie une référence sur une TWP qui aura été
     * créée à partir d'un objet json.
     * \param j l'objet de type json
     * \return La TWP créée
     */
    static TaskWithPriority& fromJson(json j);
};

/*!
 * \brief The TaskWithDeadline class
 */
class TaskWithDeadline : public Task {
private :
    struct tm* deadline;//!deadline de la tâche
public :
    TaskWithDeadline(const QString& i, const QString& t, tm* dC,tm* dLU, NoteStatus a, const QString& ac, TaskStatus s,  tm* d)
        : Task(i, t, dC, dLU, a, ac, s), deadline(d){}//!consturcteur de TWD

    //getters
    const tm* getDeadline() const{return deadline;}//!getter de deadline
    // tm* getDeadline(){return deadline;}

    //setters
    void setDeadline(tm* d){deadline = d;}//!setter de deadline

    /*!
     * \brief afficheSuite surcharge pour l'affichage
     * \param f flot de sortie
     * \return flot de sortie
     */
    ostream& afficheSuite(ostream& f){
        f<<"Action : "<<getAction()<<endl
        <<"Status : "<<getStatus()<<endl
        <<"Deadline : "<<getDeadline()<<endl;
        return f;
    }

    /*!
     * \brief getStringAttributes Renvoie une concaténationdes attributs de la note qui sont des Qstrings
     * \return Concaténation des attributs QString
     */
    QString& getStringAttributes();

    /*!
     * \brief toJson insère le contenu d'un objet Note dans un objet de
     * type json
     * \return Le fichier json contenant les informations de la note
     */
    json& toJson();

    /*!
     * \brief fromJson Renvoie une référence sur une TWD qui aura été
     * créée à partir d'un objet json.
     * \param j l'objet de type json
     * \return La TWD créée
     */
    static TaskWithDeadline& fromJson(json j);
};

/*!
 * \brief The OtherNote class
 */
class OtherNote : public Note{
private :
    QString description;//!description de la note
    QString fileName;//!lien du fichier media
    OtherNoteType type;//!type de média
public :
    OtherNote(const QString& i, const QString& t, tm* dC,  tm* dLU, NoteStatus a, const QString& d, const QString& fName, const OtherNoteType& ty)
        : Note(i, t, dC, dLU, a), description(d), fileName(fName), type(ty){}//!constructeur de OtherNote
    //getters
    const QString& getDescription() const{return description;}//!getter de description
    const QString& getFileName() const{return fileName;}//!getter de fileName
    const OtherNoteType& getType() const{return type;}//!getter de type
//    QString& getDescription(){return description;}
//    QString& getFileName(){return fileName;}
//    OtherNoteType& getType(){return type;}
    QString getTypeQS();//! On convertit le type en QString
    static OtherNoteType toONTFromQString(const QString& t){
        if(t=="Audio")
             return OtherNoteType::audio;
        else if(t=="Vidéo")
             return OtherNoteType::video;
        else if(t=="Image")
             return OtherNoteType::image;
        return OtherNoteType::image;
    }//!conversion de l'otherNoteType en QString

    //setters
    void setDescription(QString& d){description = d;}//!setter de description
    void setFileName(QString& f){fileName = f;}//!setter de fileName
    void setType(OtherNoteType& t){type = t;}//!setter de type

    /*!
     * \brief afficheSuite surcharge pour l'affichage
     * \param f flot de sortie
     * \return flot de sortie
     */
    ostream& afficheSuite(ostream& f){
        f<<"Description : "<<getDescription()<<endl
        <<"File : "<<getFileName()<<endl
        <<"Type : "<<getType()<<endl;
        return f;
    }

    /*!
     * \brief getStringAttributes Renvoie une concaténationdes attributs de la note qui sont des Qstrings
     * \return Concaténation des attributs QString
     */
    QString& getStringAttributes();

    /*!
     * \brief toJson insère le contenu d'un objet Note dans un objet de
     * type json
     * \return Le fichier json contenant les informations de la note
     */
    json& toJson();

    /*!
     * \brief fromJson Renvoie une référence sur une OtherNote qui aura été
     * créée à partir d'un objet json.
     * \param j l'objet de type json
     * \return L'OtherNote créée
     */
    static OtherNote& fromJson(json j);
};


#endif // NOTEFILLE_H
