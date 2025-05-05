#include "Arrest.hpp"
 void playcard(Player& currplayer,Player* other){

    if(other->getcoins()!=0 && other->getrole()->getname()!="General"){
        currplayer.addcoin(1);
        other->removecoin(1);
    }
    else if(other->getrole()->getname()=="General"){
        currplayer.removecoin(1);
    }
}