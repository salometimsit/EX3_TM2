
#include "Players/Player.hpp"
#include "Roles/RoleFactory.hpp"
#include <random>

Player::~Player() {
    delete role;
}

Player::Player(const std::string& name) : name(name), coins(0) {
    role = assignroles();
}
Player::Player(const Player& other): name(other.name), coins(other.coins), blockedactions(other.blockedactions), arrestCooldown(other.arrestCooldown) {
    role = RoleFactory::createRole(other.role->getrolename());
}
Player& Player::operator=(const Player& other) {
    if (this == &other) return *this;
    name = other.name;
    coins = other.coins;
    blockedactions = other.blockedactions;
    arrestCooldown = other.arrestCooldown;
    delete role;
    role = RoleFactory::createRole(other.role->getrolename());
    return *this;
}
void Player::setrole(Role* r) {
    delete role;  // clean up old one first
    role = r;
}
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

Role* Player::assignroles(){
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