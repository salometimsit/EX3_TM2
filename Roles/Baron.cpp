#include "Baron.hpp"

void  Baron::abilities(Player& currplayer,ActionStrategy& action, Player* other){

    //can invest 3 coins to become 6 
}
bool Baron:: canblock(const std::string& action)const{
    if(action.isType("Sanction")){
        return True;
    }
    return False;
}

