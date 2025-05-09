#include "Action.hpp"
#include <memory>
#include <string>
#include <stdexcept>


bool Action::isType(const std::string& type) const {
    switch (action) {
        case ActionType::Arrest:
            return "Arrest" == type;
        case ActionType::Bribe:
            return "Bribe" == type;
        case ActionType::Coup:
            return "Coup" == type;
        case ActionType::Gather:
            return "Gather" == type;
        case ActionType::Sanction:
            return "Sanction" == type;
        case ActionType::Tax:
            return "Tax" == type;
        default:
            return false;
    }
}

void Action::playcard(Player& currplayer) const{
    switch (action) {
        case ActionType::Arrest:
            currplayer.addcoin(1);
            break;
        case ActionType::Bribe:
            currplayer.removecoin(4);
            break;
        case ActionType::Coup:
            currplayer.removecoin(7);
            break;
        case ActionType::Gather:
            currplayer.addcoin(1);
            break;
        case ActionType::Sanction:
            currplayer.removecoin(3);
            break;
        case ActionType::Tax:
            currplayer.addcoin(2);
            break;
        default:
            break;
    }
}

void Action::playcard(Player& currplayer, Player& other)const {
    switch (action) {
        case ActionType::Arrest:
            currplayer.addcoin(1);
            other.removecoin(1);
            break;
        case ActionType::Bribe:
            currplayer.removecoin(4);
            break;
        case ActionType::Coup:
            currplayer.removecoin(7);
            break;
        case ActionType::Gather:
            currplayer.addcoin(1);
            break;
        case ActionType::Sanction:
            currplayer.removecoin(3);
            break;
        case ActionType::Tax:
            currplayer.addcoin(2);
            break;
        default:
            playcard(currplayer);
            break;
    }
}

std::string Action::getactionname() const {
    switch (action) {
        case ActionType::Arrest:
            return "Arrest";
        case ActionType::Bribe:
            return "Bribe";
        case ActionType::Coup:
            return "Coup";
        case ActionType::Gather:
            return "Gather";
        case ActionType::Sanction:
            return "Sanction";
        case ActionType::Tax:
            return "Tax";
        default:
            return "";
    }
}