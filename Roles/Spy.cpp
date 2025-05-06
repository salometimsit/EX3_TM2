#include "Spy.hpp"
void Spy::abilities(Player& currplayer,ActionStrategy& action, Player* other){
    int othercoins=other.getcoins();
    cout<<"player:"<<other.getnameplayer()<<"number of coins:"<<othercoins<<endl;
}
bool Spy:: canblock(const std::string& action)const{
    if(action.isType("Arrest")){
        //block in next round
        return True;
    }
    return False;
}