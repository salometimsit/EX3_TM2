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
#include "Game.hpp"

class GUI : public QMainWindow {
    Q_OBJECT

public:

    explicit GUI(Game& g, QWidget* parent = nullptr);

private slots:
    void addPlayer();
    void startGame();
    void handleAction(const QString& actionName);
    void handleSpyAction();
    void handleBaronAction();
    void updateGameView();

private:
    Game& game;
    QLabel* statusLabel;
    QListWidget* playerList;
    QLineEdit* playerNameInput;
    QGroupBox* actionGroup;
    std::vector<QPushButton*> actionButtons;
    QPushButton* spyButton;
    QPushButton* BaronButton;
    QWidget* addPlayerScreen;
    QWidget* gameScreen;
    QStackedLayout* stackedLayout;

    QLineEdit* nameInput;
    QLabel* errorLabel;
};

#endif // GUI_HPP
