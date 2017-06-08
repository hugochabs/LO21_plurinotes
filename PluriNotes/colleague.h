#ifndef COLLEAGUE
#define COLLEAGUE

#include<QTreeWidget>
#include<QWidget>
#include <QTableWidget>
#include <QDialog>
#include<string>
//#include"contener.h"
#include "note.h"

using namespace std;
//using namespace TD;

class Widget;


//!Classe Mediator qui permet la transmission de message
//! entre les differents Widget de l'application
class Mediator{
private:
    static Mediator* uniqueInstance;
protected:
    vector<Widget*> colleagues;
    NoteManager* nm;
    unsigned int nb;
    unsigned int nbMax;

public :
    Mediator( unsigned int n=0, unsigned int nMax=0): nb(n),nbMax(nMax), colleagues(n, nullptr){
    nm = &NoteManager::getNoteManager();
    }

    ~Mediator();
    virtual void distributeMessage(Widget* sender, const string message);
    virtual void registerC(Widget* c);

    static Mediator& getMediator(){
        if (!uniqueInstance){
            uniqueInstance = new Mediator;
        }
        return *uniqueInstance;
    }

    static void freeMediator(){
        if(uniqueInstance)
            uniqueInstance->~Mediator();
        uniqueInstance=0;
    }

signals:
    void signalMediator();
};



//!Classe Widget qui regroupe les attributs pour identifier
//! chaque Colleague et définit l'interface
class Widget{
protected :

    Mediator* mediator;
    unsigned int colleagueCode;

public:
    Widget(unsigned int i) : colleagueCode(i){
        mediator = &Mediator::getMediator();
    }
    virtual void sendMessage(const string &message);//ok implémenté
    virtual void receiveMessage(const string& message);//ok implémenté
    unsigned int getCode(){return colleagueCode;}
    const Mediator* getMediator(){return mediator;}

    virtual void update()=0;

};




#endif // COLLEAGUE

