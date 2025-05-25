#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <memory>
#include <stdexcept>
using std::string;
class RoleFactory;
#include "Roles/Role.hpp"
#include <random>
#include <ostream>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;
using std::unique_ptr;
class Player{
    private: 
        std::string name;
        int coins;
        // std::unique_ptr<Role> role;
        Role* role=nullptr;
        std::unordered_set<std::string> blockedactions;
        
    public:
        std::unordered_map<std::string, int> arrestCooldown;
        Role* assignroles();
        // Player(const std::string& name):name(name), coins(0), role(assignroles()){}
        Player(const std::string& name);
        Player(const Player& other);
        Player& operator=(const Player& other);
        ~Player();
        void blockAction(const std::string& actionName);
        void unblockAllActions();
        bool isActionBlocked(const std::string& actionName) const;
        std::string getnameplayer(){return name;}
        int getcoins(){return coins;}
        const Role* getrole(){return role;}
        void setcoins(int c){coins=c;}
        void setname(const string& n){name=n;}
        void setrole(Role* r);
        void addcoin(int amount); 
        void removecoin(int amount){if(coins>=amount){coins-=amount;}else{throw::std::runtime_error("not enough coins");}}//return error if amount>valid 
        
};
#endif
