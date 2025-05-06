#include "Role.hpp"
using std namespace;
Role::Role(Type type) : type_(type) {}
string Role::getrolename() const{
    switch(type_){
        case Type::Governor:return "Governor";
        case Type::Spy:return "Spy";
        case Type::Baron:return "Baron";
        case Type::Judge:return "Judge";
        case Type::Merchant:return "Merchant";
        case Type::General:return "General";
        default:return "Unknown";
    }

}
void Role:: roleonaction(Player& currplayer,Action& actionname,Player& other){
    switch(type_){
        case Type::Governor:
            if(actionname.isType("Tax")){
                break;
            }
            break;
        case Type::Spy:
            int othercoins=other.getcoins();
            cout<<"player:"<<other.getnameplayer()<<"number of coins:"<<othercoins<<endl;
            break;
        case Type::Baron:
            break;
        case Type::Judge:
            break;
        case Type::Merchant:
            if(currplayer.getcoins()>3){
                currplayer.addcoin(1);
            }
            break;
        case Type::General:
            if(actionname.isType("Arrest")){
                currplayer.addcoin(1);
            }
    }
}
void Role:: roledefence(Player& currplayer,Action& actionname,Player& other){
    switch(type_){
        case Type::Governor:
            break;
        case Type::Spy:
            break;
        case Type::Baron:
            if(actionname.isType("Sanction")){
                currplayer.addcoin(1);
            }
            break;
        case Type::Judge:
            if(actionname.isType("Sanction")){
                other.removecoin(1);
            }
            break;
        case Type::Merchant:
            if(actionname.isType("Arrest")){
                currplayer.removecoin(1);
            }
            break;
        case Type::General:
            if(actionname.isType("Arrest")){
                currplayer.addcoin(1);
            }
            break;
    }
}
bool Role::canblock(const Action& action) const{
    switch(type_){
        case Type::Governor:
            return action == "Tax";
        case Type::Spy:
            return action == "Arrest";
        case Type::Baron:
            return false;
        case Type::Judge:
            return action == "Bribe";
        case Type::Merchant:
            return false;
        case Type::General:
            return action == "Coup";
        default:
            return false;
    }
}
