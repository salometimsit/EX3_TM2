#ifndef BRIBE_HPP
#define BRIBE_HPP
#include "ActionStrategy.hpp"
#include "Player.hpp"
class Bribe:public Actionstrategy{
    public: 
        void playcard(Player& currplayer)override{currplayer.removecoin(4);}
        std::string getactionname()const override{return "Bribe";}
        virtual bool isType(const std::string& type) const {return getactionname() == type;}

};
#endif