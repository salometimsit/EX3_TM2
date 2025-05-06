class Role {
public:
    enum class Type {
        Governor, 
        Spy, 
        Baron, 
        General, 
        Judge, 
        Merchant
    };
    Role(Type type); // Constructor  
    Type getType() const { return type_; }
    void roleonaction(Player& currplayer,string& actionname);
    void roledefence(Player& currplayer,string& actionname,Player& other); 
    std::string getrolename() const; 
    bool canBlock(const std::string& action) const; 
private:
    Type type_;

};