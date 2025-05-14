#ifndef ALLACTION_HPP
#define ALLACTION_HPP

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

#endif
