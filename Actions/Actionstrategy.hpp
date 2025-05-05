class Player;
class Actionstrategy{
    public:
        virtual ~Actionstrategy();
        virtual void playcard(Player& currplayer);
        virtual std::string getactionname();
};