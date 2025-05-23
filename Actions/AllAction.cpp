#include "AllAction.hpp"
#include "Players/Player.hpp"
#include <iostream>


/** Arrest Action Implementation **/
std::string Arrest::getactionname() const {
    return "Arrest";
}

bool Arrest::isType(const std::string& type) const {
    return type == "Arrest";
}

void Arrest::playcard(Player& currplayer) const {
    // No effect in single-player context
}

void Arrest::playcard(Player& currplayer, Player& other) const {
    if (other.getrole() && other.getrole()->getrolename() == "Merchant") {
        other.removecoin(2); // Merchant loses 2
    } else {
        currplayer.addcoin(1);
        other.removecoin(1);
    }
}
//--------------------------------------------------------------------------------------------
/** Bribe Action Implementation **/

std::string Bribe::getactionname() const {
    return "Bribe";
}

bool Bribe::isType(const std::string& type) const {
    return type == "Bribe";
}

void Bribe::playcard(Player& currplayer) const {
    currplayer.removecoin(4);
}

void Bribe::playcard(Player& currplayer, Player& other) const {
    currplayer.removecoin(4);
}

//--------------------------------------------------------------------------------------------
/** Coup Action Implementation **/

std::string Coup::getactionname() const {
    return "Coup";
}

bool Coup::isType(const std::string& type) const {
    return type == "Coup";
}

void Coup::playcard(Player& currplayer) const {
    currplayer.removecoin(7);
}

void Coup::playcard(Player& currplayer, Player& other) const {
    currplayer.removecoin(7);
}
//--------------------------------------------------------------------------------------------
/** Gather Action Implementation **/

std::string Gather::getactionname() const {
    return "Gather";
}

bool Gather::isType(const std::string& type) const {
    return type == "Gather";
}

void Gather::playcard(Player& currplayer) const {
    currplayer.addcoin(1);
}

void Gather::playcard(Player& currplayer, Player& other) const {
    currplayer.addcoin(1);
}
//--------------------------------------------------------------------------------------------
/** Sanction Action Implementation **/

std::string Sanction::getactionname() const {
    return "Sanction";
}

bool Sanction::isType(const std::string& type) const {
    return type == "Sanction";
}

void Sanction::playcard(Player& currplayer) const {
    currplayer.removecoin(3);
}

void Sanction::playcard(Player& currplayer, Player& other) const {
    currplayer.removecoin(3);
    other.blockAction("Tax");
    other.blockAction("Gather");
    std::cout << "[DEBUG] " << other.getnameplayer() << " was sanctioned (Tax & Gather blocked)\n";
}
//--------------------------------------------------------------------------------------------
/** Tax Action Implementation **/

std::string Tax::getactionname() const {
    return "Tax";
}

bool Tax::isType(const std::string& type) const {
    return type == "Tax";
}

void Tax::playcard(Player& currplayer) const {
    currplayer.addcoin(2);
}

void Tax::playcard(Player& currplayer, Player& other) const {
    currplayer.addcoin(2);
}
//--------------------------------------------------------------------------------------------
//special actoins:
/** Baroninvest Action Implementation **/
void Baroninvest::playcard(Player& currplayer) const {
    currplayer.removecoin(3);
    currplayer.addcoin(6);
}
void Baroninvest::playcard(Player& currplayer, Player& other) const {
}
bool Baroninvest::isType(const std::string& type) const {
    return type == "Baroninvest";
}
bool Baroninvest::isspecial(const std::string& roleName) const{
    if(roleName == "Baron") {
        return true;
    }
    return false;
}
//--------------------------------------------------------------------------------------------
/** Governorblocktax Action Implementation **/

void Governorblocktax::playcard(Player& currplayer) const {
}
void Governorblocktax::playcard(Player& currplayer, Player& other) const {
    other.blockAction("Tax");
}
bool Governorblocktax::isType(const std::string& type) const {
    return type == "Governorblocktax";
}
bool Governorblocktax::isspecial(const std::string& roleName) const{
    if(roleName == "Governor") {
        return true;
    }
    return false;
}