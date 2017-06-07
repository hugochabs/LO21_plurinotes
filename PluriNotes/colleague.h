#ifndef COLLEAGUE
#define COLLEAGUE

#include<QTreeWidget>
#include<QWidget>
#include <QTableWidget>
#include <QDialog>
#include<string>
//#include"contener.h"
#include "notefille.h"
#include "noteediteur.h"

using namespace std;
//using namespace TD;

class Widget;

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
    virtual void registerC( Widget* c);

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

//    class iterator{
//        friend class Mediator;
//    private:
//        unsigned int nbRemain;//!nombre d'éléments restant à parcourir
//        Widget** currentC;//!élément courant
//        iterator(Widget** c, unsigned int nb):nbRemain(nb), currentC(c){}//!constructeur de l'iterator
//    public:
//        unsigned int getNbRemain()const{return nbRemain;}//!getter de nbRemain
//        /*!
//         * \brief isDone savoir s'il reste des éléments à parcourir
//         * \return bool dépendant de la valeur de nbRemain
//        */
//        bool isDone(){return nbRemain==0;}
//        //bool isDone1(){if(nbRemain==1)return true; else return false;}
//        /*!
//         * \brief isNext passe à l'élément suivant si c'est possible.
//        */
//        void isNext(){
//            if(isDone())
//                throw NotesException("Error, no more versions of notes");
//            currentC++;
//            nbRemain--;
//        }
//        /*!
//         * \brief current retourne l'élément cournat si c'est possible
//         * \return current
//        */
//        Widget& current(){
//            if(isDone())
//                throw NotesException("Error, no more versions of notes");
//            return **currentC;
//        }
//    };
//    /*!
//     * \brief getIterator retourne un iterator pour parcourir les versions
//     * \return un iterator
//        */
//    iterator getIterator(){
//        cout<<"iterator"<<endl;
//        return iterator(colleagues, nb);
//    }
};



/*class ConcreteMediator : public Mediator{

};*/


class Widget{
protected :

    Mediator* mediator;
    unsigned int colleagueCode;

public:
    Widget(Mediator* m, unsigned int i) : mediator(m), colleagueCode(i){}
    virtual void sendMessage(const string &message);//ok implémenté
    virtual void receiveMessage(const string& message);//ok implémenté
    unsigned int getCode(){return colleagueCode;}
    const Mediator* getMediator(){return mediator;}
    //const string& getName(){return name;}

    virtual void update()=0;

signals:
    void signalM();
};


/*class widget: public Colleague{
private:
    QWidget* parent;
public:
    widget(QWidget* p, Mediator m, unsigned int i):Colleague(m,i), parent(p){}
    void update(){}
};*/

class TreeWidget : public Widget{
private :

    QTreeWidget* parent;
public :
    TreeWidget(QTreeWidget* p, Mediator* m, unsigned int i):Widget(m,i), parent(p){

    }
    void update();
};

class TableWidget : public Widget{

    private :

        QTableWidget* parent;
    public :
        TableWidget(QTableWidget* p, Mediator* m, unsigned int i):Widget(m,i), parent(p){}
        void update(){}
};

class Window : public Widget {
private:
    QWidget* parent;
public :
    Window(QWidget* w, Mediator* m, unsigned int i) : Widget(m,i), parent(w){ cout<<"creation ok"<<endl;}
    void update(){}
};


#endif // COLLEAGUE

