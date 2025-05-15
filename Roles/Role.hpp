#ifndef ROLE_HPP
#define ROLE_HPP
#include <string>
#include <memory>
#include "Actions/Action.hpp"
#include "Actions/SpecialActions.hpp"
class Game;
// #include "Actions/Actionstrategy.hpp"
class Actionstrategy;
class Player;
class Action;
class Role {
    public:
        Role() = default;
        virtual ~Role();
        virtual int rolespecialities(Player& currplayer,Game& game,Player* other=nullptr)const=0;
        virtual void roleonaction(Player& currplayer, const Action& actionname, Player* other = nullptr) const=0;
        virtual void roledefence(Player& currplayer, const Action& action, Player& other) const=0;
        virtual std::string getrolename() const=0; 
        virtual bool canblock(const Action& action) const=0;
        virtual std::unique_ptr<SpecialAction> getspecial(Game& game, Player& user, Player* target = nullptr) const;
        

};
#endif