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


/*!
 * \brief la classe Mediator est responsable de la communication entre les différents objets dont elle a l'adresse dans un vector
 * Cette classe est implémentée avec le design pattern singleton
 */

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

    /*!
     * \brief Mediator::distributeMessage distribue un message à tous les widgets enregitrés dans le mediator
     * \param sender est l'adresse du widget qui envoie le message
     * \param message à envoyer
     */
    virtual void distributeMessage(Widget* sender, const string message);

    /*!
     * \brief Mediator::registerC permet d'enregistrer l'adresse d'un widget
     * \param c est l'adresse du widget qu'on enregistre dans le Mediator
     */
    virtual void registerC(Widget* c);

    /*!
     * \brief getMediator est une méthode static pour retourner la référence de l'instance unique
     * \return
     */
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

    /*!
     * \brief Mediator::~Mediator destructeur de Mediator
     */
    virtual ~Widget(){}

    /*!
     * \brief Widget::sendMessage envoie un message au Mediator
     * \param message à envoyer
     */
    virtual void sendMessage(const string &message);

    /*!
     * \brief Widget::receiveMessage permet de recevoir un message pour le widget
     * \param message reçu
     */
    virtual void receiveMessage(const string& message);
    unsigned int getCode()const{return colleagueCode;}
    const Mediator* getMediator()const{return mediator;}

    virtual void update()=0;

};




#endif // COLLEAGUE

