# Coup Game - C++ Implementation with Qt GUI

A multiplayer strategy game implementation inspired by the card game Coup, featuring unique roles, special abilities, and strategic gameplay mechanics.


## 🎮 Game Overview

This is a turn-based elimination game where players use actions to gain coins and eliminate opponents. The last player standing wins. Each player is assigned a secret role that grants unique abilities and defensive options.

## 🎯 Features

- **Graphical User Interface**: Built with Qt framework for an intuitive gaming experience
- **6 Unique Roles**: Each with special abilities and defensive capabilities
- **Strategic Gameplay**: Balance between offensive actions, defensive blocks, and resource management
- **Action Blocking System**: Players can counter certain actions based on their roles
- **Turn Management**: Includes special mechanics like bonus turns and cooldowns
- **Comprehensive Logging**: Game events are logged for debugging and analysis

## 🎭 Roles

### 1. **Governor**
- **Special Ability**: Can block Tax actions from other players
- **Defense**: Can block Coup attempts to protect other players
- **Bonus**: Gains +1 coin when performing Tax action

### 2. **Spy**
- **Special Ability**: Can spy on another player to see their coins and block their next Arrest
- **Defense**: Can block Arrest actions against themselves
- **Strategic**: Information gathering and disruption

### 3. **Baron**
- **Special Ability**: Can invest 3 coins to gain 6 coins (net +3)
- **Defense**: Gains +1 coin when targeted by Sanction
- **Economic**: Focused on wealth accumulation

### 4. **Judge**
- **Special Ability**: Can block another player from using Bribe
- **Defense**: Can block Bribe actions; attacker loses 1 coin when sanctioning a Judge
- **Control**: Maintains order and prevents corruption

### 5. **Merchant**
- **Special Ability**: Passive income - gains +1 coin at start of turn if they have 3+ coins
- **Defense**: Vulnerable to Arrest (loses 2 coins instead of 1)
- **Economic**: Steady wealth generation

### 6. **General**
- **Special Ability**: None (defensive role)
- **Defense**: Gains +1 coin when targeted by Arrest
- **Unique**: Cannot block Coup anymore (Governor has this ability)

## 🎲 Actions

### Basic Actions
1. **Gather**: Gain 1 coin (free action)
2. **Tax**: Gain 2 coins (can be blocked by Governor)
3. **Bribe**: Pay 4 coins, gain 2 extra turns (can be blocked by Judge)

### Targeted Actions
4. **Arrest**: Steal 1 coin from target (Merchant loses 2; has 2-turn cooldown per target)
5. **Sanction**: Pay 3 coins to block target's Tax and Gather for one turn
6. **Coup**: Pay 7 coins to eliminate target (can be blocked by Governor)

### Special Actions (Role-Specific)
- **Baron Investment**: Convert 3 coins to 6 coins
- **Governor Tax Block**: Block a player from using Tax
- **Judge Bribe Block**: Block a player from using Bribe
- **Spy**: Reveal target's coins and block their Arrest

## 🏗️ Technical Architecture

### Core Components

1. **Game Engine** (`Game.cpp/hpp`)
   - Manages game state and turn flow
   - Handles player actions and validation
   - Implements blocking mechanics
   - Tracks win conditions

2. **GUI System** (`GUI.cpp/hpp`)
   - Qt-based graphical interface
   - Player addition screen
   - Game board with action buttons
   - Role-specific special action buttons
   - Real-time game state updates

3. **Player Management** (`Player.cpp/hpp`, `PlayerManager.cpp/hpp`)
   - Player state tracking (coins, role, blocked actions)
   - Action cooldown system
   - Player elimination handling

4. **Action System** (`Action.hpp`, `AllAction.cpp/hpp`)
   - Abstract action interface
   - Concrete action implementations
   - Special action support for roles
   - Action factory pattern

5. **Role System** (`Role.hpp`, `AllRole.cpp/hpp`)
   - Abstract role interface
   - Role-specific abilities and defenses
   - Role factory pattern

### Design Patterns Used
- **Factory Pattern**: For creating actions and roles
- **Strategy Pattern**: For role behaviors and action execution

## 🚀 Getting Started

### Prerequisites
- C++ compiler with C++11 support
- Qt 5.15 or higher
- CMake (optional, for building)

### Running the Game
```bash
# Using makefile run:
make 
./coup_game
#Running tests:
make run_tests
./run_tests
#Running valgrind:
make valgrind-tests
## 🎮 How to Play

1. **Start Screen**: Add 2-6 players by entering their names
2. **Role Assignment**: Each player is randomly assigned a secret role
3. **Turn Order**: Players take turns performing actions
4. **Resource Management**: Collect coins to perform powerful actions
5. **Strategic Blocking**: Use your role's abilities to counter opponents
6. **Forced Coup**: Must coup when having more than 10 coins
7. **Victory**: Last player standing wins!

## 📝 Game Rules

- Players start with 2 coins
- One action per turn (except with Bribe bonus)
- Actions can be blocked based on roles
- Coup cannot be avoided if you have 7+ coins
- Eliminated players are removed from the game
- Some actions have cooldowns or restrictions

## 🐛 Debug Features

- Comprehensive logging to `coup_log.txt`
- Turn-by-turn action tracking
- Player state logging (role, coins)
- Block attempt logging

## 📁 File Structure

```
project/
├── Gamelogic/
│   ├── Game.cpp/hpp          # Core game engine
│   └── GUI.cpp/hpp           # Qt GUI implementation
├── Players/
│   ├── Player.cpp/hpp        # Player class
│   └── PlayerManager.cpp/hpp # Player management
├── Actions/
│   ├── Action.hpp            # Action interface
│   ├── AllAction.cpp/hpp     # All action implementations
│   ├── SpecialActions.hpp    # Special action interface
│   └── ActionFactory.cpp/hpp # Action creation
├── Roles/
│   ├── Role.cpp/hpp          # Role interface
│   ├── AllRole.cpp/hpp       # All role implementations
│   └── RoleFactory.cpp/hpp   # Role creation
├── images/                   # Game assets
│   ├── player_background.jpg
│   └── main_background.jpg
└── main.cpp                  # Entry point
```

## 🎨 GUI Features

- **Stylized UI**: Custom backgrounds and golden theme
- **Dynamic Updates**: Real-time player status and coin tracking
- **Role-Specific Buttons**: Special actions appear based on current player's role
- **Interactive Dialogs**: Target selection and blocking decisions
- **Visual Feedback**: Clear indication of successful/failed actions

## 🔧 Future Enhancements

- Network multiplayer support
- AI opponents
- Additional roles and actions
- Statistics tracking
- Save/load game functionality
- Animation effects
- Sound effects and music

## 🧪 Unit Test Coverage

The project includes a rich suite of unit tests powered by the **Doctest** framework to ensure robust game logic and mechanics.

### ✅ Test Areas

#### `test_allaction.cpp`
- Core logic for actions like `Gather`, `Tax`, `Bribe`, `Coup`, `Sanction`, and `Arrest`
- Special effects (e.g., `Baroninvest`)
- Error handling: insufficient coins, invalid targets, etc.

#### `test_game.cpp`
- Game startup constraints and player addition
- Turn rotation logic
- Enforced rules (e.g., mandatory Coup if >10 coins)
- Game completion and winner determination

#### `test_gamesimulation.cpp`
- Full multi-role simulation (6 players)
- Round-based scenarios testing turn flow, blocking, and role abilities
- Edge cases like elimination, stress testing, and role combinations

#### `Test_player.cpp`
- Player object behavior: coins, name, blocking, and role assignment
- Action blocking and unblocking
- Arrest cooldown functionality

#### `test_playermanager.cpp`
- Managing player creation, indexing, and elimination
- Role effects through `PlayerManager`
- Index validation and overflow checks

#### `test_rolesonactions.cpp`
- Role defenses and their impact on action flow
- Special blocking rules (e.g., Spy blocks Arrest, Judge blocks Bribe)
- Cooldowns, bonus turns, turn advancement
- Game integrity when players are eliminated

### 🧰 Test Tools
- All tests are built with **Doctest**
- Designed for **modularity and coverage**
- Easy to run using a test runner or compiled binary

To run the tests, compile the test files with your build system and execute the resulting binary.

## Help
- I used ChatGpt to document,make tests and makefile but the rest of the code came from my logic and thinking

## 📄 License
This project is open source and available under the MIT License.
