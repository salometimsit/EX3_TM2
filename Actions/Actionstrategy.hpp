class Player;
class Actionstrategy{
    public:
        virtual ~Actionstrategy();
        virtual void playcard(Player& currplayer)=0;
        virtual void playcard(Player& currplayer,Player& other){playcard(currplayer);}
        virtual std::string getactionname();
        virtual bool isType(const std::string& type) const;
};                                     