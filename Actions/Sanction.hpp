#ifndef SANCTION_HPP
#define SANCTION_HPP
#include "ActionStrategy.hpp"
#include "Player.hpp"
class Sanction:public Actionstrategy{
    public: 
        void playcard(Player& currplayer)override{currplayer.removecoin(3);}
        void playcard(Player& currplayer,Player& other)override;
        std::string getactionname()const override{return "Sanction";}
        virtual bool isType(const std::string& type) const {return getactionname() == type;}
};
#endif