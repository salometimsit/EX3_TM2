#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "Player.hpp"
#include "RoleFactory.hpp"
#include <random>
#include <algorithm>

struct playermanager{
    //instead of define works for compiler +11 
    static constexpr int MIN_PLAYERS = 2;
    static constexpr int MAX_PLAYERS = 6;
    std::vector<std::unique_ptr<Player>> players;
    bool addPlayer(std::unique_ptr<Player> player) {
        if (players.size() >= MAX_PLAYERS) {
            throw std::runtime_error("Maximum number of players reached cannot add more players");
            return false;
        }
        players.push_back(std::move(player));
            return true;
    }
    bool isplayervalid()const{
        if(players.size() < MIN_PLAYERS) {
            throw std::runtime_error("Not enough players to start the game");
            return false;
        }
        if(players.size() > MAX_PLAYERS) {
            throw std::runtime_error("Too many players to start the game");
            return false;
        }
        return true;
    }
    // void shuffleplayers() {
    //     std::random_device rd;
    //     std::mt19937 g(rd());
    //     std::shuffle(players.begin(), players.end(), g);
    // }
    
    //void assignroles()

};
#endif