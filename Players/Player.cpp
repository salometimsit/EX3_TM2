
#include "Players/Player.hpp"
#include "Roles/RoleFactory.hpp"
#include <random>


void Player::blockAction(const std::string& actionName) {
    blockedactions.insert(actionName);
}
void Player::unblockAllActions() {
        blockedactions.clear();
}
bool Player::isActionBlocked(const std::string& actionName) const {
    return blockedactions.find(actionName) != blockedactions.end();
}

void Player::addcoin(int amount){
    if(amount<0){
        throw std::runtime_error("Cannot add negative coins");
    }
    coins+=amount;
}

std::unique_ptr<Role> Player::assignroles(){
            std::random_device rd;
            std::mt19937 g(rd());
            std::uniform_int_distribution<int> dist(1,6);
            int rand= dist(g);
            RoleFactory factory;
            switch (rand) {
                case 1:
                    return factory.createRole("Governor");
                case 2:
                    return factory.createRole("Spy");
                case 3:
                    return factory.createRole("Baron");
                case 4:
                    return factory.createRole("General");
                case 5:
                    return factory.createRole("Judge");
                case 6:
                    return factory.createRole("Merchant");
                default:
                    throw std::runtime_error("Invalid role assignment");
            }
}