#include "Arrest.hpp"
void Arrest::playcard(Player& currplayer,Player& other){
    currplayer.addcoin(1);
    other.removecoin(1);
}