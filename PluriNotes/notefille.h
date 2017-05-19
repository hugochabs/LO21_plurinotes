#ifndef NOTEFILLE_H
#define NOTEFILLE_H

#include <iostream>
#include <ctime> //librairie pour gérer le temps et les dates
#include <string>
#include "note.h"

using namespace std;

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

//redéfinition des opérateurs

ostream& operator<< (ostream& f, Article& A);
ostream& operator<< (ostream& f, Task& T);
ostream& operator<< (ostream& f, TaskWithPriority& T);
ostream& operator<< (ostream& f, TaskWithDeadline& T);
ostream& operator<< (ostream& f, OtherNote& T);





#endif // NOTEFILLE_H
