/**
This class needs to be a Strategy/factory one- so the other roles use it
 */
//make as interface:
class Player;
class ActionStrategy;
class Rolestrategy{
    public:
        virtual ~Rolestrategy();
        virtual void special(Player& currplayer);
        virtual std::string getrolename();
};git add .