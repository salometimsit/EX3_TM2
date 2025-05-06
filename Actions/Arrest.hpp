#ifndef ARREST_HPP
#define ARREST_HPP
#include "ActionStrategy.hpp"
#include "Player.hpp"
class Arrest:public Actionstrategy{
    public: 
        void playcard(Player& currplayer)override;
        void playcard(Player& currplayer,Player& other)override;
        std::string getactionname()const override{return "Arrest";}
        virtual bool isType(const std::string& type) const {return getactionname() == type;}

};
#endif