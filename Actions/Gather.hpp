#include "ActionStrategy.hpp"
#include "Player.hpp"
class Gather:public Actionstrategy{
        void playcard(Player& currplayer)override{currplayer.addcoin(1);}
        std::string getactionname()const override{return "Gather";}
};