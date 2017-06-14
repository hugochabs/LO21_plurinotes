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
    //! Constructeur privé pour avoir qu'une seule instance de Mediator
    Mediator( unsigned int n=0, unsigned int nMax=0): colleagues(n, nullptr), nb(n),nbMax(nMax){
    nm = &NoteManager::getNoteManager();
    }
    virtual ~Mediator();
    //! constructeur par recopie et operateur d'affectation privés pour éviter la duplication
    Mediator(const Mediator& m);
    Mediator& operator=(const Mediator& m);
protected:
    //!Attributs protégés si la classe Mediator vient à être sous-classé
    vector<Widget*> colleagues;
    NoteManager* nm;
    unsigned int nb;
    unsigned int nbMax;

public :
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



/*! Classe Widget qui regroupe les attributs pour identifier
 *  chaque Colleague et définit l'interface
 */
class Widget{
protected :

    Mediator* mediator;
    unsigned int colleagueCode;

public:
    Widget(unsigned int i) : colleagueCode(i){
        mediator = &Mediator::getMediator();
    }
    virtual ~Widget(){}
    //!fonctions virtuelles qui permettent la communcation avec le mediator
    virtual void sendMessage(const string &message);//ok implémenté
    virtual void receiveMessage(const string& message);//ok implémenté
    unsigned int getCode()const{return colleagueCode;}
    const Mediator* getMediator()const{return mediator;}

    virtual void update()=0;

};




#endif // COLLEAGUE

