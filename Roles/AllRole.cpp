
#include "AllRole.hpp"
#include <iostream>

/*
    * @brief This file contains the implementation of various roles in the game.
    * Each role has its own unique abilities and interactions with actions.
    * The roles include Governor, Spy, Baron, Judge, Merchant, and General.
    * Each role implements its own special abilities and action responses.
    
*/

//---------------------------------------------------------------------------------------------

/** Governor Implementation **/

/**
 * @brief Governor has no default active special action.
 */
int Governor::rolespecialities(Player& currplayer, Game& game, Player* other) const {
    return 0;
}

/**
 * @brief If the Governor performs a Tax, they gain an extra coin.
 */
void Governor::roleonaction(Player& currplayer, const Action& actionname, Player* other) const {
    if (actionname.isType("Tax")) {
        currplayer.addcoin(1);
    }
}

void Governor::roledefence(Player& currplayer, const Action& action, Player& other) const {
    // No special defense
}

bool Governor::canblock(const Action& action) const {
    return action.isType("Tax");
}
std::unique_ptr<SpecialAction> Governor::getspecial(Game& game, Player& user, Player* target ) const{
    return std::make_unique<Governorblocktax>();
}

//---------------------------------------------------------------------------------------------
/** Spy Implementation **/

/**
 * @brief Spy blocks Arrest against another player and returns their coin count.
 */
int Spy::rolespecialities(Player& currplayer, Game& game, Player* other) const {
    if (other) {
        game.blockarrestfornext(*other);
        return other->getcoins();
    }
    std::cerr << "[ERROR] Spy special ability called with null target!\n";
    return 0;
}

/**
 * @brief Reveals the target player’s coin count.
 */
void Spy::roleonaction(Player& currplayer, const Action& actionname, Player* other) const {
    if (other) {
        std::cout << "player: " << other->getnameplayer() << ", coins: " << other->getcoins() << std::endl;
    }
}

void Spy::roledefence(Player& currplayer, const Action& action, Player& other) const {
    // No specific defense
}

bool Spy::canblock(const Action& action) const {
    return action.isType("Arrest");
}
std::unique_ptr<SpecialAction> Spy::getspecial(Game& game, Player& user, Player* target ) const{
}

//---------------------------------------------------------------------------------------------
/** Baron Implementation **/

/**
 * @brief If the Baron has 3 or more coins, converts 3 coins into 6 if he wants to invest.
 * @return 0 if the action is not performed.
 */
int Baron::rolespecialities(Player& currplayer, Game& game, Player* other) const {
    if (currplayer.getcoins() >= 3) {
        currplayer.removecoin(3);
        currplayer.addcoin(6);
    }
    return 0;
}

void Baron::roleonaction(Player& currplayer, const Action& actionname, Player* other) const {}

void Baron::roledefence(Player& currplayer, const Action& action, Player& other) const {
    std::cout << "[DEBUG] Baron::roledefence called\n";
    if (action.isType("Sanction")) {
        std::cout << "[DEBUG] Sanction detected on Baron\n";
        currplayer.addcoin(1);
    } else {
        std::cout << "[DEBUG] Action is not Sanction\n";
    }
}

bool Baron::canblock(const Action& action) const {
    return false;
}
std::unique_ptr<SpecialAction> Baron::getspecial(Game& game, Player& user, Player* target) const{
    if (user.getcoins() >= 3) {
        return std::make_unique<Baroninvest>();
    }
    return nullptr;
}

//---------------------------------------------------------------------------------------------
/** Judge Implementation **/


/**
 * @brief Judge has no passive special effect.
 */
int Judge::rolespecialities(Player& currplayer, Game& game, Player* other) const {
    return 0;
}

void Judge::roleonaction(Player& currplayer, const Action& actionname, Player* other) const {}


/**
 * @brief If sanctioned, the attacker loses a coin.
 */
void Judge::roledefence(Player& currplayer, const Action& action, Player& other) const {
    if (action.isType("Sanction")) {
        other.removecoin(1);
    }
}

bool Judge::canblock(const Action& action) const {
    return action.isType("Bribe");
}
std::unique_ptr<SpecialAction> Judge::getspecial(Game& game, Player& user, Player* target) const {}

//---------------------------------------------------------------------------------------------
/** Merchant Implementation **/
/**
 * @brief If the merchant has 3 or more coins at the beggining of their turn, they gain an additional coin.
 */
int Merchant::rolespecialities(Player& currplayer, Game& game, Player* other) const {
    if (currplayer.getcoins() >= 3) {
        currplayer.addcoin(1);
        return 1;
    }
    return 0;
}

void Merchant::roleonaction(Player& currplayer, const Action& actionname, Player* other) const {
}

void Merchant::roledefence(Player& currplayer, const Action& action, Player& other) const {
    if (action.isType("Arrest")) {
        currplayer.removecoin(2);
    }
}

bool Merchant::canblock(const Action& action) const {
    return false;
}
std::unique_ptr<SpecialAction> Merchant::getspecial(Game& game, Player& user, Player* target) const {}

//---------------------------------------------------------------------------------------------
/** General Implementation **/

/**
 * @brief General currently has no passive special effect.
 */
int General::rolespecialities(Player& currplayer, Game& game, Player* other) const {
    return 0;
}

void General::roleonaction(Player& currplayer, const Action& actionname, Player* other) const {}

/**
 * @brief Gains 1 coin if targeted by Arrest.
 */
void General::roledefence(Player& currplayer, const Action& action, Player& other) const {
    if (action.isType("Arrest")) {
        currplayer.addcoin(1);
    }
}

bool General::canblock(const Action& action) const {
    return action.isType("Coup");
}
std::unique_ptr<SpecialAction> General:: getspecial(Game& game, Player& user, Player* target) const {}