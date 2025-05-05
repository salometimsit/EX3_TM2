#include "ActionStrategy.hpp"
#include "Player.hpp"
class Bribe:public Actionstrategy{
    public: 
        void playcard(Player& currplayer)override{currplayer.removecoin(4);}
        std::string getactionname()const override{return "Bribe";}

};