#include "Role.hpp"
class Player{
    private: 
        std::string name;
        int coins;
        std::unique_ptr<Role> role; 
    public:
        Player(const std::string& name, std::unique_ptr<Role> r):name(name), coins(0), role(std::move(r));
        ~Player();
        std::string getnameplayer(){return name;}
        int getcoins(){return coins;}
        const Role* getrole(return role.get());
        void addcoin(int amount){coins+=amount;} 
        void removecoin(int amount){if(coins>amount){coins-=amount;}else{throw::std::runtime_error("not enough coins");}}//return error if amount>valid 
    //is role / set role / eliminate / activate 
};