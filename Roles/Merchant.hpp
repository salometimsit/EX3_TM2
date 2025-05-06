#ifndef MERCHANT_HPP
#define MERCHANT_HPP
#include "ActionStrategy.hpp"
#include "Player.hpp"
#include "Rolestrategy.hpp"

class Merchant:public Rolestrategy{
    public: 
        virtual void abilities(Player& currplayer,ActionStrategy& action, Player* other)override;
        virtual std::string getrolename()override const{return "Merchant"};
        virtual bool isrole(const std::string& type)const{return getrolename()==type();}
        virtual bool canblock(const std::string& action)const;
};
#endif















