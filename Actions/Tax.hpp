#ifndef TAX_HPP
#define TAX_HPP
#include "ActionStrategy.hpp"
#include "Player.hpp"
class Tax:public Actionstrategy{
    public: 
        void playcard(Player& currplayer,Player& other)override;
        void playcard(Player& currplayer)override{currplayer.addcoin(2);}
        std::string getactionname()const override{return "Tax";}
        virtual bool isType(const std::string& type) const {return getactionname() == type;}
};
#endif