#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "Player.hpp"
#include "Roles/RoleFactory.hpp"
#include <random>
#include <algorithm>
using std::unique_ptr;
struct PlayerManager{
    //instead of define works for compiler +11 
    public:
        static constexpr int MIN_PLAYERS = 2;
        static constexpr int MAX_PLAYERS = 6;
        std::vector<unique_ptr<Player>> players;

        bool addPlayer(unique_ptr<Player> player) ;
        bool isplayervalid()const;
        bool isplayerindexvalid(int index);
        void shuffleplayers();
        void eliminateplayer(int index);
        size_t playerCount() const;
        //void assignroles()

        Player* getPlayerByIndex(int index);
        int getPlayerIndex(const std::string& playerName);
        int getPlayerCoins(int index);
        std::string getPlayerRole(int index);

};
#endif