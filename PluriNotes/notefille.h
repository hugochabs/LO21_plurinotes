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
    const QString& getText(){return text;}//!getter de text

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
    json toJson();
    void fromJson();
};

/*!
 * \brief The Task class
 */
class Task : public Note {
private :
    QString action;
    TaskStatus status;

public :
    Task(const QString& i, const QString& t, tm* dC, tm* dLU,NoteStatus a, const QString& ac, TaskStatus s = waiting)
        : Note(i, t, dC, dLU, a), action(ac), status(s){}
    //getters
    QString getAction()const {return action;}
    const TaskStatus& getStatus(){return status;}
    QString getStatusQS(){ //!Getter pour avoir status en QString
        switch(status){
        case TaskStatus::doing:
            return "Doing";
        case TaskStatus::done :
            return "Done";
        case TaskStatus::waiting:
            return "Waiting";
        }
    }

    static TaskStatus toTSfromQString(const QString& t){
        if(t=="waiting")
             return waiting;
         else if(t=="done")
             return done;
         else if(t=="en realisation")
             return doing;
    }

    //setters
    void setAction(QString& a){action = a;}
    void setStatus(TaskStatus& s){status = s;}
    ostream& afficheSuite(ostream& f){
        f<<"Action\t: "<<getAction()<<endl
        <<"Status\t: "<<getStatus()<<endl;
        return f;
    }

    json toJson();
    void fromJson();
};

/*!
 * \brief The TaskWithPriority class
 */
class TaskWithPriority : public Task {
private :
    int priority;
public :
    TaskWithPriority(const QString& i, const QString& t, tm* dC, tm* dLU, NoteStatus a, const QString& ac, TaskStatus s, int p)
        : Task(i, t, dC, dLU, a, ac, s), priority(p){}
    //getters
    const int& getPriority(){return priority;}
    QString getPriorityQS(){//!On convertit priority en QString
        return QString::number(priority);
    }

    //setters
    void setPriority(int & p){priority = p;}
    ostream& afficheSuite(ostream& f){
        f<<"Action : "<<getAction()<<endl
        <<"Status : "<<getStatus()<<endl
        <<"Priority : "<<getPriority()<<endl;
        return f;
    }

    json toJson();
    void fromJson();
};

/*!
 * \brief The TaskWithDeadline class
 */
class TaskWithDeadline : public Task {
private :
    struct tm* deadline;
public :
    TaskWithDeadline(const QString& i, const QString& t, tm* dC, tm* dLU, NoteStatus a, const QString& ac, TaskStatus s, tm* d)
        : Task(i, t, dC, dLU, a, ac, s), deadline(d){}

    //getters
    const tm* getDeadline(){return deadline;}

    //setters
    void setDeadline(tm* d){deadline = d;}
    ostream& afficheSuite(ostream& f){
        f<<"Action : "<<getAction()<<endl
        <<"Status : "<<getStatus()<<endl
        <<"Deadline : "<<getDeadline()<<endl;
        return f;
    }

    json toJson();
    void fromJson();
};

/*!
 * \brief The OtherNote class
 */
class OtherNote : public Note{
private :
    QString description;
    QString fileName;
    OtherNoteType type;
public :
    OtherNote(const QString& i, const QString& t, tm* dC, tm* dLU, NoteStatus a, const QString& d, const QString& fName, const OtherNoteType& ty)
        : Note(i, t, dC, dLU, a), description(d), fileName(fName), type(ty){}
    //getters
    const QString& getDescription(){return description;}
    const QString& getFileName(){return fileName;}
    const OtherNoteType& getType(){return type;}
    QString getTypeQS();//! On convertit le type en QString
    static OtherNoteType toONTFromQString(const QString& t){
        if(t=="Audio")
             return OtherNoteType::audio;
         else if(t=="Vidéo")
             return OtherNoteType::video;
         else if(t=="Image")
             return OtherNoteType::image;
    }

    //setters
    void getDescription(QString& d){description = d;}
    void getFileName(QString& f){fileName = f;}
    void getType(OtherNoteType& t){type = t;}


    ostream& afficheSuite(ostream& f){
        f<<"Description : "<<getDescription()<<endl
        <<"File : "<<getFileName()<<endl
        <<"Type : "<<getType()<<endl;
        return f;
    }

    json toJson();
    void fromJson();
};

//redéfinition des opérateurs

ostream& operator<< (ostream& f, Article& A);
ostream& operator<< (ostream& f, Task& T);
ostream& operator<< (ostream& f, TaskWithPriority& T);
ostream& operator<< (ostream& f, TaskWithDeadline& T);
ostream& operator<< (ostream& f, OtherNote& T);





#endif // NOTEFILLE_H
