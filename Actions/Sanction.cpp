#include "Sanction.hpp"

void playcard(Player& currplayer,Player& other){
    if(other->getrole()->getname()=="Judge"){
        currplayer.removecoin(4);
    }
    currplayer.removecoin(3);
}