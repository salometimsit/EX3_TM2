#include "Judge.hpp"
void General::abilities(Player& currplayer,ActionStrategy& action, Player* other){
    if(action.isType("Arrest")){
        other.removecoin(1);
        currplayer.addcoin(1);
    }
}
bool General::canblock(const std::string& action)const{
    if(action.isType("Coup")){
        return True;
    }
    return False;
}