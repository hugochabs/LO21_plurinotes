#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <iostream>
#include <ctime> //librairie pour gérer le temps et les dates
#include <string>


using namespace std;

//----Classe d'exception----//
/*!
 * \brief La classe NotesException sert à gérer les exceptions,
 * renvoyées par l'ensemble du programme sous forme de string.
 */
class NotesException{
public:
    NotesException(const string& message):info(message){}
    string getInfo() const { return info; }
private:
    string info;
};




#endif // EXCEPTION_H
