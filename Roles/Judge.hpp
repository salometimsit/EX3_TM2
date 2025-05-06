#ifndef JUDGE_HPP
#define JUDGE_HPP
#include "ActionStrategy.hpp"
#include "Player.hpp"
#include "Rolestrategy.hpp"

class Judge:public Rolestrategy{
    private: 
        bool attack;
    public: 
        virtual void abilities(Player& currplayer,ActionStrategy& action, Player* other)override;
        virtual std::string getrolename()override const{return "Judge"};
        virtual bool isrole(const std::string& type)const{return getrolename()==type();}
        virtual bool canblock(const std::string& action)const;
};
#endif















