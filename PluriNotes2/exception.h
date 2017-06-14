#ifndef EXCEPTION_H
#define EXCEPTION_H


#include <iostream>
//#include <time.h>
#include <ctime> //librairie pour gérer le temps et les dates
#include <string>
#include <fstream>

#include <QString>
#include <QMessageBox>
#include <QWidget>

using namespace std;

//----Classe d'exception----//
/*!
 * \brief La classe NotesException sert à gérer les exceptions,
 * renvoyées par l'ensemble du programme sous forme de QString.
 */
class NotesException {
public:
    NotesException(const QString& message):info(message){}
    QString getInfo() const { return info; }
private:
    QString info;
   // QMessageBox::information();
};




#endif // EXCEPTION_H
