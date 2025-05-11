#ifndef ROLE_HPP
#define ROLE_HPP
#include <string>
class Game;
// #include "Actions/Actionstrategy.hpp"
class Actionstrategy;
class Player;
class Action;
class Role {
    
    public:
        enum class Type {
            Governor, 
            Spy, 
            Baron, 
            General, 
            Judge, 
            Merchant
        };
        
    private:
        Type type_;
    public:
        Role(Type type); // Constructor  
        Type getType() const { return type_; }
        void roleonaction(Player& currplayer,Action actionname,Player* other = nullptr)const;
        int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const;
      
        void roledefence(Player& currplayer,Action action,Player& other)const; 
        std::string getrolename() const; 
        bool canblock(const Action& action) const;
};
#endif