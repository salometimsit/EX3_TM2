#ifndef GUI_HPP
#define GUI_HPP
#include <QMainWindow>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QStackedLayout>

#include <vector>
#include "Gamelogic/Game.hpp"

// Logs a general event message (not tied to a specific player)
void logEvent(const std::string& message);
// Logs an event message related to a specific player and their role
void logEventWithRole(const std::string& message, const Player* player);
/**
 * @class GUI
 * @brief Main window class that handles the game's graphical user interface using Qt.
 */
class GUI : public QMainWindow {
    Q_OBJECT

public:
    /**
     * @brief Constructs the GUI object.
     * @param g Reference to the game logic object.
     * @param parent Optional parent QWidget.
     */
    explicit GUI(Game& g, QWidget* parent = nullptr);

private slots:
    /**
     * @brief Adds a player to the game when the corresponding button is clicked.
     */
    void addPlayer();

    /**
     * @brief Starts the game and transitions to the game screen.
     */
    void startGame();

    /**
     * @brief Handles a general action performed by a player.
     * @param actionName Name of the action as a QString.
     */
    void handleAction(const QString& actionName);

    /**
     * @brief Handles the specific action associated with the Spy role.
     */
    void handleSpyAction();

    /**
     * @brief Handles the specific action associated with the Baron role.
     */
    void handleBaronAction();

    /**
     * @brief Handles the specific action associated with the Governor role.
     */
    void handleGovernorAction();

    /**
     * @brief Handles the specific action associated with the Judge role.
     */
    void handleJudgeAction();

    /**
     * @brief Updates the visual components to reflect the current state of the game.
     */
    void updateGameView();

    /**
     * @brief Checks whether a general block action is possible against a target.
     * @param targetIndex Index of the target player.
     * @param action The action being attempted.
     * @return True if the action is blocked, false otherwise.
     */
    bool checkGeneralBlock(int targetIndex, const Action& action);

    /**
     * @brief Displays a dialog showing the game winner.
     */
    void showWinnerDialog();

private:
    bool gameStarted = false;  ///< Tracks whether the game has started
    Game& game;                ///< Reference to the game logic object

    // UI components
    QLabel* statusLabel;             ///< Displays game status messages
    QListWidget* playerList;         ///< List of players in the game
    QLineEdit* playerNameInput;      ///< Input field for entering player names
    QGroupBox* actionGroup;          ///< Group box containing action buttons
    std::vector<QPushButton*> actionButtons; ///< Buttons for different actions

    // Specific role action buttons
    QPushButton* spyButton;
    QPushButton* BaronButton;
    QPushButton* GovernorButton;
    QPushButton* JudgeButton;

    // Screens managed by the stacked layout
    QWidget* addPlayerScreen;        ///< Screen for adding players
    QWidget* gameScreen;             ///< Main game screen
    QStackedLayout* stackedLayout;   ///< Layout that switches between screens

    QLineEdit* nameInput;            ///< Input for player name (possibly duplicate, consider unifying)
    QLabel* errorLabel;              ///< Label for displaying input errors
};

#endif // GUI_HPP
