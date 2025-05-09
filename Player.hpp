#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <memory>
#include <stdexcept>
using std::string;
#include "Roles/RoleFactory.hpp"
#include <random>
using std::unique_ptr;
class Player{
    private: 
        std::string name;
        int coins;
        std::unique_ptr<Role> role;
    public:
    
        std::unique_ptr<Role> assignroles(){
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
        Player(const std::string& name):name(name), coins(0), role(assignroles()){}
        ~Player()=default;
        std::string getnameplayer(){return name;}
        int getcoins(){return coins;}
        const Role* getrole(){return role.get();}
        void setcoins(int c){coins=c;}
        void setname(const string& n){name=n;}
        void setrole(unique_ptr<Role> r){role=std::move(r);}
        void addcoin(int amount){coins+=amount;} 
        void removecoin(int amount){if(coins>amount){coins-=amount;}else{throw::std::runtime_error("not enough coins");}}//return error if amount>valid 
        

    //is role / set role / eliminate / activate 
};
#endif
