#include "ActionStrategy.hpp"
#include "Player.hpp"
class Coup:public Actionstrategy{
    public: 
        void playcard(Player& currplayer)override{currplayer.removecoin(7);}
        std::string getactionname()const override{return "Coup";}
};