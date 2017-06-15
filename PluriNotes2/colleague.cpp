#include"colleague.h"

using namespace std;

Mediator* Mediator::uniqueInstance = 0;

/*!
 * \brief Mediator::~Mediator destructeur de Mediator
 */
Mediator::~Mediator(){
    for(unsigned int i ; i<colleagues.size() ; i++){
        delete colleagues[i];
    }
}

/*!
 * \brief Widget::sendMessage envoie un message au Mediator
 * \param message à envoyer
 */
void Widget::sendMessage(const string& message){
    mediator->distributeMessage(this, message);
}

/*!
 * \brief Widget::receiveMessage permet de recevoir un message pour le widget
 * \param message reçu
 */
void Widget::receiveMessage(const string &message){
    update();
    //cout<<"le widget "<<getCode()<<" a recu le message : " <<message<<endl;
}
/*!
 * \brief Mediator::distributeMessage distribue un message à tous les widgets enregitrés dans le mediator
 * \param sender est l'adresse du widget qui envoie le message
 * \param message à envoyer
 */
void Mediator::distributeMessage(Widget* sender, string message){

    for(unsigned int i = 0 ; i<colleagues.size() ; i++){

        if(colleagues[i]->getCode()!= sender->getCode()){

            colleagues[i]->receiveMessage(message);
        }
    }
}

/*!
 * \brief Mediator::registerC permet d'enregistrer l'adresse d'un widget
 * \param c est l'adresse du widget qu'on enregistre dans le Mediator
 */
void Mediator::registerC(Widget *c){
    colleagues.push_back(c);
}



