#ifndef ALLACTION_HPP
#define ALLACTION_HPP
#include "SpecialActions.hpp"
#include "Action.hpp"

class Arrest : public Action {
public:
    std::string getactionname() const override;
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
};

class Bribe : public Action {
public:
    std::string getactionname() const override;
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
};

class Coup : public Action {
public:
    std::string getactionname() const override;
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
};

class Gather : public Action {
public:
    std::string getactionname() const override;
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
};

class Sanction : public Action {
public:
    std::string getactionname() const override;
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
};

class Tax : public Action {
public:
    std::string getactionname() const override;
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
};
class Baroninvest: public SpecialAction {
public:
    std::string getactionname() const override{return "Baroninvest";};
    bool isType(const std::string& type) const override;
    void playcard(Player& currplayer) const override;
    void playcard(Player& currplayer, Player& other) const override;
    bool isspecial(const std::string& roleName) const override;
};
// class Generalprotectother: public SpecialAction {
//     public:
//         std::string getactionname() const override{return "Generalprotectother";};
//         bool isType(const std::string& type) const override;
//         void playcard(Player& currplayer) const override;
//         void playcard(Player& currplayer, Player& other) const override;
//         bool isspecial(const std::string& roleName) const override;
// };
class Governorblocktax: public SpecialAction {
    public:
        std::string getactionname() const override{return "Governorblocktax";};
        bool isType(const std::string& type) const override;
        void playcard(Player& currplayer) const override;
        void playcard(Player& currplayer, Player& other) const override;
        bool isspecial(const std::string& roleName) const override;
};
#endif
