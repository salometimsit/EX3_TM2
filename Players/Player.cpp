//timsitmelosa@gmail.com
#include "Players/Player.hpp"
#include "Roles/RoleFactory.hpp"
#include <random>

/**
 * @brief Destroys the Player, releasing any dynamically allocated Role.
 */
Player::~Player() {
    delete role;
}
/**
 * @brief Construct a Player with a given name and zero starting coins.
 *        A role is assigned immediately via assignroles().
 *
 * @param name The display name for the player.
 */
Player::Player(const std::string& name) : name(name), coins(0) {
    role = assignroles();
}
/**
 * @brief Copy‑constructor: deep‑copies the Role and all player state.
 *
 * @param other The Player instance to copy from.
 */
Player::Player(const Player& other): name(other.name), coins(other.coins), blockedactions(other.blockedactions), arrestCooldown(other.arrestCooldown) {
    role = RoleFactory::createRole(other.role->getrolename());
}
/**
 * @brief Copy‑assignment operator: deep‑copies state and Role while guarding
 *        against self‑assignment.
 *
 * @param other The Player instance to assign from.
 * @return *this to allow chaining.
 */
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

/**
 * @brief Replace the current Role (if any) with the supplied pointer.
 *
 *  Ownership of @p newRole is transferred to this Player, and any previously
 *  held Role is deleted to prevent leaks.
 *
 * @param newRole Newly created Role object; may be nullptr to clear.
 */
void Player::setrole(Role* newRole) {
    if (role) {
        delete role;  
    }
    role = newRole;
}
/**
 * @brief Mark a specific action as blocked for this Player.
 *
 * @param actionName The canonical string name of the action.
 */
void Player::blockAction(const std::string& actionName) {
    blockedactions.insert(actionName);
}
/**
 * @brief Clear all previously blocked actions.
 */
void Player::unblockAllActions() {
        blockedactions.clear();
}
/**
 * @brief Query whether an action is currently blocked.
 *
 * @param actionName The action to test.
 * @return true if blocked, false otherwise.
 */
bool Player::isActionBlocked(const std::string& actionName) const {
    return blockedactions.find(actionName) != blockedactions.end();
}
/**
 * @brief Add coins to the player's purse.
 *
 * @param amount The positive number of coins to add.
 * @throw std::runtime_error if @p amount is negative.
 */
void Player::addcoin(int amount){
    if(amount<0){
        throw std::runtime_error("Cannot add negative coins");
    }
    coins+=amount;
}
/**
 * @brief Randomly assign one of six possible roles to the player.
 *
 *  A cryptographically secure random_device seeds a Mersenne Twister engine
 *  (`std::mt19937`). An integer in the range [1,6] selects the Role via
 *  RoleFactory. The caller assumes ownership of the returned pointer.
 *
 * @return Pointer to the newly created Role.
 * @throw std::runtime_error if the random value is out of range.
 */
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

/**
 * @brief Remove coins from the player's purse.
 *
 * @param amount The number of coins to remove.
 * @throw std::runtime_error if the player lacks sufficient coins.
 */
 void Player::removecoin(int amount){
    if(coins>=amount){
        coins-=amount;
    }
    else{
        throw::std::runtime_error("not enough coins");
    }
}