#ifndef GATHER_HPP
#define GATHER_HPP
#include "ActionStrategy.hpp"
#include "Player.hpp"
class Gather:public Actionstrategy{
     public: 
        void playcard(Player& currplayer,Player& other)override{currplayer.addcoin(1);}
        std::string getactionname()const override{return "Gather";}
        virtual bool isType(const std::string& type) const {return getactionname() == type;}
};
#endif