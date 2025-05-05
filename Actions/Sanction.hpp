#include "ActionStrategy.hpp"
#include "Player.hpp"
class Sanction:public Actionstrategy{
    public: 
        void playcard(Player& currplayer,Player& other)override;
        std::string getactionname()const override{return "Sanction";}
};