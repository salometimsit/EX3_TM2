//timsitmelosa@gmail.com
#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP
#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include "Players/Player.hpp"
//#include "Roles/RoleFactory.hpp"
#include <random>
#include <algorithm>
using std::unique_ptr;
struct PlayerManager{
    public:
        static constexpr int MIN_PLAYERS = 2;
        static constexpr int MAX_PLAYERS = 6;
        std::vector<Player*> players;
         /**
        * @brief Destructor – deletes all managed `Player` instances.
        */
        ~PlayerManager(); 
        /**
        * @brief Add a new player to the manager.
        * @param player Raw pointer to a `Player` instance. Ownership is transferred.
        * @return `true` if the player could be added; `false` if the player limit has been reached.
        */
        bool addPlayer(Player* player);
        /**
        * @brief Check whether the current number of players satisfies game rules.
        * @return `true` if between `MIN_PLAYERS` and `MAX_PLAYERS`, inclusive.
        */
        bool isplayervalid()const;
        /**
        * @brief Validate that an index refers to an existing player.
        * @param index Zero‑based index.
        * @return `true` if the index is within range; otherwise `false`.
        */
        bool isplayerindexvalid(int index)const;
        /**
        * @brief Eliminate (and delete) a player by index.
        * @param index Zero‑based index of the player to eliminate.
        * @note After this call the index positions of subsequent players shift.
        */
        void eliminateplayer(int index);
        /**
        * @brief Number of active players currently managed.
        */
        size_t playerCount() const;
          /**
        * @brief Retrieve a player pointer by index.
        * @param index Zero‑based index.
        * @return Raw pointer to the `Player`; `nullptr` if index is invalid.
        */
        Player* getPlayerByIndex(int index);
         /**
        * @brief Get the index of a player by name.
        * @param playerName Case‑sensitive name search.
        * @return Index if found; otherwise `-1`.
        */
        int getPlayerIndex(const std::string& playerName);
        /**
        * @brief Get the coin count for a player at the given index.
        * @param index Zero‑based player index.
        * @return Coin total.
        */
        int getPlayerCoins(int index);
         /**
        * @brief Get the role name of a player at the given index.
        * @param index Zero‑based player index.
        * @return Role name as a `std::string`.
        */
        std::string getPlayerRole(int index);

};
#endif