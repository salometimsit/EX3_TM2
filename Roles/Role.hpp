#ifndef ROLE_HPP
#define ROLE_HPP
#include <string>
class Player;
class Actionstrategy;
class Role {
    private:
        Type type_;
    public:
        enum class Type {
            Governor, 
            Spy, 
            Baron, 
            General, 
            Judge, 
            Merchant
        };
        Role(Type type); // Constructor  
        Type getType() const { return type_; }
        void roleonaction(Player& currplayer,Action& actionname);
        void roledefence(Player& currplayer,Action&actionname,Player& other); 
        std::string getrolename() const; 
        bool canblock(const std::string& action) const; 


};
#endif