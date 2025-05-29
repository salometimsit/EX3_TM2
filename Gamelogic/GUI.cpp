//timsitmelosa@gmail.com
#include "Gamelogic/GUI.hpp"
#include <QInputDialog>
#include <fstream>
#include <QMessageBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QApplication>
#include "Actions/ActionFactory.hpp"
/**
    * @brief Global logger function to log events to a file.
    * @param message The message to log
 */
std::ofstream logFile("coup_log.txt");
void logEvent(const std::string& message) {
    logFile << message << std::endl;
}
/**
    * @brief Logs an event with player details.
    * @param message The message to log
    * @param player Pointer to the player involved in the event
 */
void logEventWithRole(const std::string& message, const Player* player) {
    std::string name = player ? player->getnameplayer() : "UnknownPlayer";
    std::string role = (player && player->getrole()) ? player->getrole()->getrolename() : "UnassignedRole";
    int coins = player ? player->getcoins() : -1;

    logFile << "(" << name << " | Role: " << role << " | Coins: " << coins << ") "
            << message << std::endl;
}

/**
 * @brief GUI constructor initializes the main window and sets up the game interface.
 * @param g Reference to the Game object managing game state.
 * @param parent Parent widget for the GUI.
 * 
 * This constructor sets up the main window, initializes layouts, and creates widgets
 * for adding players and displaying the game screen. It also connects buttons to their
 * respective slots for handling player actions.
 */
GUI::GUI(Game& g, QWidget* parent) : QMainWindow(parent), game(g) {
    logEvent("GUI constructor started");
    resize(900, 1000);
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    stackedLayout = new QStackedLayout();
    central->setLayout(stackedLayout);

    // === Add Player Screen ===
    addPlayerScreen = new QWidget();
    addPlayerScreen->setObjectName("AddPlayerScreen");

    QPixmap addBg("/home/salome/projects/EX3/images/player_background.jpg");
    
    addBg = addBg.scaled(900, 1000, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPalette addPalette;
    addPalette.setBrush(QPalette::Window, addBg);
    addPlayerScreen->setAutoFillBackground(true);
    addPlayerScreen->setPalette(addPalette);

    QVBoxLayout* addLayout = new QVBoxLayout(addPlayerScreen);
    addLayout->setContentsMargins(250, 600, 250, 200);
    addLayout->setSpacing(15);

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter player name");
    nameInput->setStyleSheet("background: rgba(255, 255, 255, 0.7); padding: 8px; border-radius: 10px; font-size: 16px;");
    addLayout->addWidget(nameInput);

    QPushButton* addBtn = new QPushButton("ADD");
    QPushButton* startBtn = new QPushButton("START");

    QString buttonStyle = "font-size: 18px; background-color: rgba(0,0,0,0.7); color: white; border: 1px solid white; border-radius: 10px; padding: 6px;";
    addBtn->setStyleSheet(buttonStyle);
    startBtn->setStyleSheet(buttonStyle);

    errorLabel = new QLabel();
    errorLabel->setStyleSheet("color: red; font-size: 16px; font-weight: bold;");

    addLayout->addWidget(addBtn);
    addLayout->addWidget(startBtn);
    addLayout->addWidget(errorLabel);
    addLayout->setAlignment(Qt::AlignTop);

    connect(addBtn, &QPushButton::clicked, this, &GUI::addPlayer);
    connect(startBtn, &QPushButton::clicked, this, &GUI::startGame);

    // === Game Screen ===
    gameScreen = new QWidget(this);
    gameScreen->setObjectName("GameScreen");

    QPixmap gameBg("/home/salome/projects/EX3/images/main_background.jpg");
    gameBg = gameBg.scaled(900, 1000, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPalette gamePalette;
    gamePalette.setBrush(QPalette::Window, gameBg);
    gameScreen->setAutoFillBackground(true);
    gameScreen->setPalette(gamePalette);

    QVBoxLayout* mainLayout = new QVBoxLayout(gameScreen);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(15);

    statusLabel = new QLabel("Welcome to Coup");
    statusLabel->setStyleSheet("color: #F1C40F; font-size: 24px; font-weight: bold; background-color: rgba(0,0,0,0.4); padding: 10px; border-radius: 10px;");
    mainLayout->addWidget(statusLabel);

    playerList = new QListWidget();
    playerList->setStyleSheet("background-color: rgba(255, 255, 255, 0.4); border: none; color: white; font-weight: bold; font-size: 16px; border-radius: 10px; padding: 5px;");
    mainLayout->addWidget(playerList);

    actionGroup = new QGroupBox("Actions");
    actionGroup->setStyleSheet(R"(
        QGroupBox {
            background-color: rgba(0, 0, 0, 0.5);
            border: 2px solid #D4AF37;
            border-radius: 15px;
            margin-top: 10px;
        }
        QGroupBox::title {
            color: #D4AF37;
            subcontrol-origin: margin;
            padding-left: 10px;
        }
    )");

    QVBoxLayout* actionLayout = new QVBoxLayout();

    QStringList actions = {"Gather", "Tax", "Bribe", "Arrest", "Sanction", "Coup"};
    QString actionBtnStyle = R"(
        QPushButton {
            font-size: 18px; padding: 6px;
            color: #D4AF37;
            background-color: rgba(0,0,0,0.6);
            border: 1px solid #D4AF37;
            border-radius: 10px;
        }
        QPushButton:hover {
            background-color: rgba(255, 255, 255, 0.1);
        }
        QPushButton:pressed {
            background-color: rgba(255, 255, 255, 0.3);
        }
    )";

    for (const QString& act : actions) {
        QPushButton* btn = new QPushButton(act);
        btn->setStyleSheet(actionBtnStyle);
        actionButtons.push_back(btn);
        actionLayout->addWidget(btn);
        connect(btn, &QPushButton::clicked, this, [this, act]() {
            handleAction(act);
        });
    }

    spyButton = new QPushButton("Spy on Player");
    BaronButton = new QPushButton("Barons investment");
    GovernorButton = new QPushButton("Governor Tax Block");
    JudgeButton = new QPushButton("Judge Block Bribe");
    for (auto* btn : {spyButton, BaronButton, GovernorButton, JudgeButton}) {
        btn->setStyleSheet(actionBtnStyle);
        actionLayout->addWidget(btn);
        btn->hide();
    }

    connect(spyButton, &QPushButton::clicked, this, &GUI::handleSpyAction);
    connect(BaronButton, &QPushButton::clicked, this, &GUI::handleBaronAction);
    connect(GovernorButton, &QPushButton::clicked, this, &GUI::handleGovernorAction);
    connect(JudgeButton, &QPushButton::clicked, this, &GUI::handleJudgeAction);

    actionGroup->setLayout(actionLayout);
    actionGroup->setVisible(false);
    mainLayout->addWidget(actionGroup);

    stackedLayout->addWidget(addPlayerScreen);
    stackedLayout->addWidget(gameScreen);
    stackedLayout->setCurrentWidget(addPlayerScreen);
    logEvent("AddPlayer screen loaded");
}


/**
 * @brief Adds a player to the game.
 * This method retrieves the player's name from the input field, validates it,
 * and attempts to add the player to the game. If successful, it logs the event
 * and clears the input field. If an error occurs, it displays an error message.
 */
void GUI::addPlayer() {
    QString name = nameInput->text().trimmed();
    if (name.isEmpty()) return;

    try {
        game.addPlayer(name.toStdString());
        logEvent("Player added: " + name.toStdString());
        nameInput->clear();
        errorLabel->setText("");
    } catch (const std::exception& e) {
        errorLabel->setText(e.what());
    }
}
/**
    * @brief Starts the game with the current players.
    * This method initializes the game, sets the gameStarted flag to true,
    * and updates the player list in the GUI. If an error occurs during game
    * initialization, it displays an error message.
 */

void GUI::startGame() {
    try {
        game.startGame();
        gameStarted = true;
        logEvent("Game started with " + std::to_string(game.playersList().size()) + " players");

        // Setup player list
        playerList->clear();
        for (const auto& name : game.playersList()) {
            playerList->addItem(QString::fromStdString(name));
        }
        updateGameView();
        actionGroup->setVisible(true);
        stackedLayout->setCurrentWidget(gameScreen);
        gameScreen->update();
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Start Failed", e.what());
    }

}

/**
    * @brief Handles the action selected by the player.
    * 
    * This method creates an action based on the action name, checks if it requires
    * a target, and prompts the user to select a target if necessary. It also handles
    * special cases for actions like Arrest, Coup, and blocking actions.
    * @param actionName The name of the action to handle.
 */
void GUI::handleAction(const QString& actionName) {
    try {
        ActionFactory factory;
        Action* action = factory.createAction(actionName.toStdString());
        bool needsTarget = false;
    
        if (action->isType("Arrest") || action->isType("Sanction") || action->isType("Coup")) {
            needsTarget = true;
        }

        int targetIndex = -1;
        
        if (needsTarget) {
            bool ok;
            QStringList items;
            for (const auto& name : game.playersList()) {
                if (name != game.turn())
                    items << QString::fromStdString(name);
            }

            QString selected = QInputDialog::getItem(this, "Select Target", "Target:", items, 0, false, &ok);
            if (ok) {
                targetIndex = game.getPlayerIndexByName(selected.toStdString());
            } else {
                delete action;
                return;
            }
        }
        
        if (needsTarget && targetIndex >= 0 && action->isType("Arrest") && game.isarrestblocked(*game.getCurrentPlayer())) {
            QMessageBox::warning(this, "Blocked", "You are blocked from using Arrest this turn (Spy effect).");
            delete action;
            return;
        }
        
        Player* current = game.getCurrentPlayer();
        if (!current) {
            QMessageBox::critical(this, "Fatal", "Current player is null. Game state invalid.");
            delete action;
            return;
        }
        
        if (current->isActionBlocked(actionName.toStdString())) {
            QMessageBox::warning(this, "Blocked", 
                "You are blocked from performing this action (" + actionName + ") this turn.");
            delete action;
            return;
        }
        
        if (needsTarget && targetIndex >= 0) {
            Player* targetPlayer = game.getPlayerByIndex(targetIndex);
            QString targetName = QString::fromStdString(targetPlayer->getnameplayer());

            // For Coup actions, we need special handling
            if (action->isType("Coup")) {
                // Check if target can block
                bool coupBlocked = false;
                
                if (targetPlayer->getrole() && targetPlayer->getrole()->canblock(*action)) {
                    // Special handling for General blocking coup (costs 5 coins)
                    if (targetPlayer->getrole()->getrolename() == "General") {
                        if (targetPlayer->getcoins() < 5) {
                            // General can't afford to block
                            logEvent("General " + targetName.toStdString() + " cannot block coup - insufficient coins");
                            QMessageBox::information(this, "Cannot Block", 
                                targetName + ", you need at least 5 coins to block a Coup. You only have " + 
                            QString::number(targetPlayer->getcoins()) + " coins.");
                        } else {
                            QMessageBox::StandardButton reply;
                            reply = QMessageBox::question(this, "Block Action",
                                targetName + ", do you want to pay 5 coins to block the Coup?",
                                QMessageBox::Yes | QMessageBox::No);

                            if (reply == QMessageBox::Yes) {
                                try {
                                    // General pays 5 coins to block
                                    targetPlayer->removecoin(5);
                                    logEvent("General " + targetName.toStdString() + " paid 5 coins to block coup");
                                    
                                    logEvent("Coup was blocked by " + targetName.toStdString());
                                    game.getCurrentPlayer()->blockAction("Coup");
                                    game.blockaction(*targetPlayer, *action, *game.getCurrentPlayer());
                                    QMessageBox::information(this, "Blocked", "The Coup was blocked by General! (Cost: 5 coins)");
                                    coupBlocked = true;
                                } catch (const std::exception& e) {
                                    logEvent("Coup block failed");
                                    QMessageBox::warning(this, "Block Failed", e.what());
                                }
                            }
                        }
                    }
                }
                
                // Check for General block if not already blocked
                if (!coupBlocked && checkGeneralBlock(targetIndex, *action)) {
                    game.getCurrentPlayer()->blockAction("Coup");
                    coupBlocked = true;
                }
                
                // Always call playTurn for Coup (it will handle the blocking internally)
                logEvent("[Before] Coup by " + current->getnameplayer() + 
                        " (Coins: " + std::to_string(current->getcoins()) + ")");
                game.playTurn(*action, targetIndex);
                logEvent("[After] Coup by " + current->getnameplayer() + 
                        " (Coins: " + std::to_string(current->getcoins()) + ")");
                
                updateGameView();
                delete action;
                return;
            }
            
            // For non-Coup actions, handle blocking normally
            if (targetPlayer->getrole() && targetPlayer->getrole()->canblock(*action)) {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Block Action",
                    targetName + ", do you want to block the action: " + actionName + "?",
                    QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    try {
                        logEvent("Action '" + actionName.toStdString() + "' was blocked by " + targetName.toStdString());
                        game.blockaction(*targetPlayer, *action, *game.getCurrentPlayer());
                        QMessageBox::information(this, "Blocked", "The action was blocked!");
                        updateGameView();
                        delete action;
                        return;
                    } catch (const std::exception& e) {
                        logEvent("Action '" + actionName.toStdString() + "' failed to block");
                        QMessageBox::warning(this, "Block Failed", e.what());
                        delete action;
                        return;
                    }
                }
            }

            // Handle Arrest cooldown check
            if (action->isType("Arrest")) {
                std::string targetName = targetPlayer->getnameplayer();
                if (current->arrestCooldown.count(targetName) && current->arrestCooldown[targetName] > 0) {
                    QMessageBox::warning(this, "Cooldown", 
                        "You must wait before arresting this player again.");
                    delete action;
                    return;
                }
            }

            // Execute the action
            logEvent("[Before] " + actionName.toStdString() +
                    " by " + current->getnameplayer() +
                    " (Coins: " + std::to_string(current->getcoins()) + ")");
            game.playTurn(*action, targetIndex);
            logEvent("[After] " + actionName.toStdString() +
                    " by " + current->getnameplayer() +
                    " (Coins: " + std::to_string(current->getcoins()) + ")");
                    
            if (action->isType("Arrest") && targetIndex >= 0) {
                Player* targetPlayer = game.getPlayerByIndex(targetIndex);
                current->arrestCooldown[targetPlayer->getnameplayer()] = 2;
            }
        }

        // Handle actions that don't require a target
        if (!needsTarget) {
            logEvent("[Before] " + actionName.toStdString() +
                    " by " + current->getnameplayer() +
                    " (Coins: " + std::to_string(current->getcoins()) + ")");
            logEventWithRole("Attempting action: " + actionName.toStdString(), current);
            game.playTurn(*action, -1);
            logEvent("[After] " + actionName.toStdString() +
                    " by " + current->getnameplayer() +
                    " (Coins: " + std::to_string(current->getcoins()) + ")");

            if (action->isType("Bribe")) {
                QMessageBox::information(this, "Bribe", "You gained 2 extra turns!");
            }
        }
        
        updateGameView();
        delete action;

    } catch (const std::exception& e) {
        Player* current = game.getCurrentPlayer();
        std::string errorMessage = e.what();
        logEvent("ACTION FAILED: " + actionName.toStdString() + " by " +
                (current ? current->getnameplayer() : "Unknown") +
                " — ERROR: " + errorMessage);
        QMessageBox::warning(this, "Action Error", e.what());
    }
}
/**
    * @brief Checks if a General can and wants to  block a Coup action

 */
bool GUI::checkGeneralBlock(int targetIndex, const Action& action) {
    Player* targetPlayer = game.getPlayerByIndex(targetIndex);
    if (!targetPlayer) return false;

    QString targetName = QString::fromStdString(targetPlayer->getnameplayer());

    for (const auto& playerStr : game.playersList()) {
        QString name = QString::fromStdString(playerStr);
        if (name == QString::fromStdString(game.turn()) || name == targetName)
            continue;

        int index = game.getPlayerIndexByName(name.toStdString());
        Player* potentialProtector = game.getPlayerByIndex(index);
        if (potentialProtector && potentialProtector->getrole() &&
            potentialProtector->getrole()->getrolename() == "General" &&
            potentialProtector->getrole()->canblock(action)) {

            if (potentialProtector->getcoins() < 5) {
                continue; 
            }

            QMessageBox::StandardButton reply = QMessageBox::question(this, "General Block",
                name + ": Do you want to pay 5 coins to protect " + targetName + " and block the Coup?",
                QMessageBox::Yes | QMessageBox::No);

            if (reply == QMessageBox::Yes) {
                try {
                    // General pays 5 coins to block
                    potentialProtector->removecoin(5);
                    logEvent("General " + potentialProtector->getnameplayer() + 
                            " paid 5 coins to block coup");
                    
                    // Mark coup as blocked
                    game.getCurrentPlayer()->blockAction("Coup");
                    
                    game.blockaction(*potentialProtector, action, *game.getCurrentPlayer());
                    QMessageBox::information(this, "Blocked", 
                        "The Coup was blocked by General! (Cost: 5 coins)");
                    updateGameView();
                    return true;
                } catch (const std::exception& e) {
                    QMessageBox::warning(this, "Block Failed", e.what());
                    return true;
                }
            }
        }
    }

    return false;
}


/**
    * @brief Handles the Spy action, allowing the current player to spy on another player.
    * This method prompts the user to select a player to spy on, retrieves their coin count,
    * and displays the result in a message box. It also blocks the target from using Arrest next turn.
 */
void GUI::handleSpyAction() {
   
    bool ok;
    QStringList items;
    for (const auto& name : game.playersList()) {
        if (name != game.turn())
            items << QString::fromStdString(name);
    }
    QString selected = QInputDialog::getItem(this, "Spy", "Choose a player to spy on:", items, 0, false, &ok);

    if (!ok) return;
    int targetIndex = game.getPlayerIndexByName(selected.toStdString());
    if (targetIndex >= 0) {
        Player* current = game.getCurrentPlayer();
        Player* target = game.getPlayerByIndex(targetIndex);
        if (current && target && current->getrole()) {
            int others_coins = current->getrole()->rolespecialities(*current, game, target);
            QMessageBox::information(this, "Spy",
            "You spied on " + QString::fromStdString(target->getnameplayer()) +
            ". They have " + QString::number(others_coins) + " coins.\n"
            "They are now blocked from using Arrest next turn.");
        }
        updateGameView();
    }
}
/**
    * @brief Handles the Baron action, allowing the current player to invest coins.
    * This method checks if the player has enough coins, performs the investment,
    * and updates the game state accordingly. It also displays a message box with the result.
 */
void GUI::handleBaronAction() {
    Player* current = game.getCurrentPlayer();
    logEventWithRole("Baron action triggered", current);
    if (!current || current->getcoins() < 3) {
        QMessageBox::warning(this, "Insufficient Coins", "You need at least 3 coins to use Baron's ability.");
        return;
    }

    if (current && current->getrole()) {
        std::unique_ptr<SpecialAction> special = current->getrole()->getspecial(game, *current);
        if (special) {
            game.playTurn(*special); // No target for Baroninvest
            QMessageBox::information(this, "Baron", "You invested 3 coins and gained 6!");
        } else {
            QMessageBox::warning(this, "Baron", "No special action available.");
        }
    }

    updateGameView();
}
/**
    * @brief Handles the Governor action, allowing the current player to block another player's tax action.
    * This method prompts the user to select a player to block from using Tax, retrieves their index,
    * and performs the blocking action if valid. It also updates the game view and displays a message box.
 */
void GUI::handleGovernorAction() {
    bool ok;
    QStringList items;
    for (const auto& name : game.playersList()) {
        if (name != game.turn())
            items << QString::fromStdString(name);
    }
    QString selected = QInputDialog::getItem(this, "Governor", "Block Tax from player:", items, 0, false, &ok);
    if (!ok) return;

    int targetIndex = game.getPlayerIndexByName(selected.toStdString());
    if (targetIndex >= 0) {
        Player* current = game.getCurrentPlayer();
        Player* target = game.getPlayerByIndex(targetIndex);
        if (current && target && current->getrole()) {
            std::unique_ptr<SpecialAction> special = current->getrole()->getspecial(game, *current, target);
            if (special) {
                game.playTurn(*special, targetIndex);
                QMessageBox::information(this, "Governor", selected + " is now blocked from Tax this turn.");
            }
        }
        updateGameView();
    }
}
/**
 * @brief Handles the Judge action, allowing the current player to block another player's Bribe action.
 * This method prompts the user to select a player to block from using Bribe, retrieves their index,
 * and performs the blocking action if valid. It also updates the game view and displays a message box.
 */
void GUI::handleJudgeAction() {
    bool ok;
    QStringList items;
    for (const auto& name : game.playersList()) {
        if (name != game.turn())
            items << QString::fromStdString(name);
    }
    
    QString selected = QInputDialog::getItem(this, "Judge", "Block Bribe from player:", items, 0, false, &ok);
    if (!ok) return;

    int targetIndex = game.getPlayerIndexByName(selected.toStdString());
    if (targetIndex >= 0) {
        Player* current = game.getCurrentPlayer();
        Player* target = game.getPlayerByIndex(targetIndex);
        if (current && target && current->getrole()) {
            std::unique_ptr<SpecialAction> special = current->getrole()->getspecial(game, *current, target);
            if (special) {
                try {
                    logEvent("[Before] Judge Block Bribe by " + current->getnameplayer() + 
                            " on " + target->getnameplayer());
                    game.playTurn(*special, targetIndex);
                    logEvent("[After] Judge Block Bribe - turn advanced");
                    QMessageBox::information(this, "Judge", 
                        selected + " is now blocked from using Bribe this turn.");
                } catch (const std::exception& e) {
                    QMessageBox::warning(this, "Action Failed", e.what());
                }
            }
        }
        updateGameView();
    }
}

/**
 * @brief Updates the game view with the current player's status and available actions.
 * This method checks if the game has a winner, updates the status label with the current player's
 * name, role, and coin count, and shows or hides action buttons based on the current player's role.
 */
void GUI::updateGameView() {
    if (!gameStarted) {
        return;
    }
    if (game.playersList().size() == 1) {
        std::string winnerName = game.winner();
        statusLabel->setText("Game Over! Winner: " + QString::fromStdString(winnerName));
        actionGroup->setVisible(false);
        logEvent("Game over. Winner: " + winnerName);
        showWinnerDialog();
        return;
    }
    
    std::string current = game.turn();
    QString role = QString::fromStdString(game.getCurrentPlayerRole());
    int coins = game.getCurrentPlayerCoins();
    statusLabel->setText("Turn: " + QString::fromStdString(current) + " | Role: " + role + " | Coins: " + QString::number(coins));

    spyButton->setVisible(role == "Spy");
    BaronButton->setVisible(role == "Baron");
    GovernorButton->setVisible(role == "Governor");
    JudgeButton->setVisible(role == "Judge");
}

/**
 * @brief Displays a dialog showing the winner of the game.
 * This method creates a custom dialog with the winner's name, a trophy emoji,
 * and congratulatory messages. It also provides an option to exit the game.
 */
void GUI::showWinnerDialog() {
    QString winner = QString::fromStdString(game.winner());
    
    // Create a custom dialog for the winner
    QDialog* winnerDialog = new QDialog(this);
    winnerDialog->setWindowTitle("Game Over!");
    winnerDialog->setFixedSize(400, 300);
    
    // Set background style
    winnerDialog->setStyleSheet(R"(
        QDialog {
            background-color: #1a1a1a;
            border: 3px solid #D4AF37;
            border-radius: 15px;
        }
        QLabel {
            color: #D4AF37;
            font-weight: bold;
        }
        QPushButton {
            font-size: 18px;
            padding: 10px;
            color: #D4AF37;
            background-color: rgba(0,0,0,0.6);
            border: 2px solid #D4AF37;
            border-radius: 10px;
            min-width: 150px;
        }
        QPushButton:hover {
            background-color: rgba(255, 255, 255, 0.1);
        }
    )");
    
    QVBoxLayout* layout = new QVBoxLayout(winnerDialog);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(20);
    
    // Trophy emoji or crown
    QLabel* trophyLabel = new QLabel("👑");
    trophyLabel->setAlignment(Qt::AlignCenter);
    trophyLabel->setStyleSheet("font-size: 72px;");
    layout->addWidget(trophyLabel);
    
    // Winner announcement
    QLabel* winnerLabel = new QLabel("WINNER");
    winnerLabel->setAlignment(Qt::AlignCenter);
    winnerLabel->setStyleSheet("font-size: 36px; color: #D4AF37;");
    layout->addWidget(winnerLabel);
    
    // Winner name
    QLabel* nameLabel = new QLabel(winner);
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setStyleSheet("font-size: 48px; color: #F1C40F; font-weight: bold;");
    layout->addWidget(nameLabel);
    
    // Congratulations message
    QLabel* congratsLabel = new QLabel("Congratulations! You ");
    congratsLabel->setAlignment(Qt::AlignCenter);
    congratsLabel->setStyleSheet("font-size: 16px; color: #D4AF37;");
    layout->addWidget(congratsLabel);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();    
    QPushButton* exitBtn = new QPushButton("Exit");
    connect(exitBtn, &QPushButton::clicked, [winnerDialog]() {
        winnerDialog->accept();
    });
    
    buttonLayout->addWidget(exitBtn);
    layout->addLayout(buttonLayout);
    
    int result = winnerDialog->exec();
    QString clickedButtonText = exitBtn->text();  
    delete winnerDialog;

    if (result == QDialog::Accepted && clickedButtonText == "Exit") {
        QApplication::quit();  
    }

}



