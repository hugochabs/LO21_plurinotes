#include"colleague.h"

using namespace std;

Mediator* Mediator::uniqueInstance = 0;

Mediator::~Mediator(){
    for(unsigned int i ; i<colleagues.size() ; i++){
        delete colleagues[i];
    }
}

void Widget::sendMessage(const string& message){
    mediator->distributeMessage(this, message);
}

void Widget::receiveMessage(const string &message){
    update();
    cout<<"le widget "<<getCode()<<" a recu le message " <<message<<endl;
}

void Mediator::distributeMessage(Widget* sender, string message){

    for(unsigned int i = 0 ; i<colleagues.size() ; i++){

        if(colleagues[i]->getCode()!= sender->getCode()){

            colleagues[i]->receiveMessage(message);
        }
    }
}

void Mediator::registerC(Widget *c){
    colleagues.push_back(c);
}


//void TreeWidget::update(){

//}

//void MWindow::update(){
//    parent->initialisationArchive();
//    parent->initialisationT();
//    parent->initialisationNA();
//}


