#include "ActionStrategy.hpp"
#include "Player.hpp"
class Tax:public Actionstrategy{
    public: 
        void playcard(Player& currplayer)override{
            if(getrole()=="Governor"){
                getnameplayer().addcoin(3);
            }
            getnameplayer().addcoin(2);
        }
        std::string getactionname()const override{return "Tax";}
};