
#include "AllRole.hpp"
#include <iostream>
// Governor.cpp


int Governor::rolespecialities(Player& currplayer, Game& game, Player* other) const {
    return 0;
}

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


// Spy.cpp



int Spy::rolespecialities(Player& currplayer, Game& game, Player* other) const {
    if (other) {
        game.blockarrestfornext(*other);
        return other->getcoins();
    }
    std::cerr << "[ERROR] Spy special ability called with null target!\n";
    return 0;
}

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

// Baron.cpp


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


// Judge.cpp



int Judge::rolespecialities(Player& currplayer, Game& game, Player* other) const {
    return 0;
}

void Judge::roleonaction(Player& currplayer, const Action& actionname, Player* other) const {}

void Judge::roledefence(Player& currplayer, const Action& action, Player& other) const {
    if (action.isType("Sanction")) {
        other.removecoin(1);
    }
}

bool Judge::canblock(const Action& action) const {
    return action.isType("Bribe");
}
std::unique_ptr<SpecialAction> Judge::getspecial(Game& game, Player& user, Player* target) const {}

// Merchant.cpp



int Merchant::rolespecialities(Player& currplayer, Game& game, Player* other) const {
    if (currplayer.getcoins() > 3) {
        currplayer.addcoin(1);
        std::cout << "[DEBUG] Merchant bonus applied\n";
    }
    return 0;
}

void Merchant::roleonaction(Player& currplayer, const Action& actionname, Player* other) const {
    if (currplayer.getcoins() > 3) {
        currplayer.addcoin(1);
    }
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

// General.cpp


int General::rolespecialities(Player& currplayer, Game& game, Player* other) const {
    return 0;
}

void General::roleonaction(Player& currplayer, const Action& actionname, Player* other) const {}

void General::roledefence(Player& currplayer, const Action& action, Player& other) const {
    if (action.isType("Arrest")) {
        currplayer.addcoin(1);
    }
}

bool General::canblock(const Action& action) const {
    return action.isType("Coup");
}
std::unique_ptr<SpecialAction> General:: getspecial(Game& game, Player& user, Player* target) const {}