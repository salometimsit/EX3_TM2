#include "Judge.hpp"
void Judge::abilities(Player& currplayer,ActionStrategy& action, Player* other){
    if(action.isType("Sanction")){
        other.removecoin(1);
    }
}
bool Judge:: canblock(const std::string& action)const{
    if(action.isType("Bribe")){
        return True;
    }
    return False;
}