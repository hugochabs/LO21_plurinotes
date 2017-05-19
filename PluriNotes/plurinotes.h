#ifndef PLURINOTES_H
#define PLURINOTES_H



//-----------------------------------//


//----Définition des classes----//







//--------------------------------//

//redéfinition des opérateurs

ostream& operator<< (ostream& f, const tm* tps); //necessiare pour afficher les heures de façon stylée
/*La redéfiniton de l'opérateur << est nécessaire pour les
 * enum car sinon lors de l'affichage, il n'affiche pas le nom de la variable
 * mais l'entier associé.
 * Exemple :
 * cout<<waiting affiche : 0
 * cout<<doing affiche : 1, etc...
 */
ostream& operator<< (ostream& f, const TaskStatus& S);
ostream& operator<< (ostream& f, const OtherNoteType& T);






#endif // PLURINOTES_H
