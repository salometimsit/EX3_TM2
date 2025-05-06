#include "ActionStrategy.hpp"
#include "Player.hpp"
class Coup:public Actionstrategy{
    public: 
        void playcard(Player& currplayer,Player& other)override{currplayer.removecoin(7);}
        std::string getactionname()const override{return "Coup";}
        virtual bool isType(const std::string& type) const {return getactionname() == type;}
};