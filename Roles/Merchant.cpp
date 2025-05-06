#include "Merchant.hpp"
void Merchant::abilities(Player& currplayer,ActionStrategy& action, Player* other){
    if(currplayer.getcoins()>3)){
        currplayer.addcoin(1);
    }
}
bool Merchant::canblock(const std::string& action)const{
    if(action.isType("Arrest")){
        return True;
    }
    return False;
}