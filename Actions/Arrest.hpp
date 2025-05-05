#include "ActionStrategy.hpp"
#include "Player.hpp"
class Arrest:public Actionstrategy{
    public: 
        void playcard(Player& currplayer,Player& other)override;
        std::string getactionname()const override{return "Arrest";}

};