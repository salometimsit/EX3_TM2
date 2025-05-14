#include "Roles/Role.hpp"
#include "Actions/ActionFactory.hpp"
#include "Game.hpp"
using  namespace std;
#include <iostream>

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
void Role::roleonaction(Player& currplayer, const Action& actionname, Player* other) const {
    if (type_ == Type::Spy && other != nullptr) {
        std::cout << "player: " << other->getnameplayer() << ", coins: " << other->getcoins() << std::endl;
    }
    switch(type_){
        case Type::Governor:
            if(actionname.isType("Tax")){
                currplayer.addcoin(1);
                break;
            }
            break;
        case Type::Spy:{
            break;
        }
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
int Role::rolespecialities(Player& currplayer,Game& game, Player* other)const{
    switch(type_){
        case Type::Governor:
            return 0;
        case Type::Spy:{
            if (other) {
                game.blockarrestfornext(*other);
                return other->getcoins();
            } else {
                std::cerr << "[ERROR] Spy special ability called with null target!\n";
                return 0;
            }
        }
        case Type::Baron:
        if(currplayer.getcoins()>=3){
            currplayer.removecoin(3);
            currplayer.addcoin(6);
            
        }
        return 0;
        
        case Type::Judge:
            return 0;
        case Type::Merchant:
            if(currplayer.getcoins()>3){
                currplayer.addcoin(1);
            }
            return 0;
        case Type::General:
           return 0;
        default:
            return 0;
    }
}
void Role::roledefence(Player& currplayer, const Action& action, Player& other) const {
    if(action.isType("Arrest")){
        other.addcoin(1);
    }
    switch(type_){
        case Type::Governor:
            break;
        case Type::Spy:
            break;
        case Type::Baron:
            if(action.isType("Sanction")){
                currplayer.addcoin(1);
            }
            break;
        case Type::Judge:
            if(action.isType("Sanction")){
                other.removecoin(2);
            }
            break;
        case Type::Merchant:
            if(action.isType("Arrest")){
                currplayer.removecoin(1);
            }
            break;
        case Type::General:
            if(action.isType("Arrest")){
                currplayer.addcoin(1);
            }
            break;
    }
}
bool Role::canblock(const Action& action) const{
    switch (type_) {
        case Type::Governor:
            return action.isType("Tax");
        case Type::Spy:
            return action.isType("Arrest");
        case Type::Baron:
            return false;
        case Type::Judge:
            return action.isType("Bribe");
        case Type::Merchant:
            return false;
        case Type::General:
            return action.isType("Coup");
        default:
            return false;
    }
}
