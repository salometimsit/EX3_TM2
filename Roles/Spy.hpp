#ifndef SPY_HPP
#define SPY_HPP
#include "ActionStrategy.hpp"
#include "Player.hpp"
#include "Rolestrategy.hpp"

class Spy:public Rolestrategy{
    private: 
        bool attack;
    public: 
        virtual void abilities(Player& currplayer,ActionStrategy& action, Player* other)override;
        virtual std::string getrolename()override const{return "Spy"};
        virtual bool isrole(const std::string& type)const{return getrolename()==type();}
        virtual bool canblock(const std::string& action)const;
};
#endif