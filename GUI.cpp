#include "GUI.hpp"
#include <QInputDialog>
#include <QMessageBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QApplication>
#include "Actions/ActionFactory.hpp"


GUI::GUI(Game& g, QWidget* parent) : QMainWindow(parent), game(g) {
    QWidget* central = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(central);

    statusLabel = new QLabel("Welcome to Coup");
    mainLayout->addWidget(statusLabel);

    playerList = new QListWidget();
    mainLayout->addWidget(playerList);

    QHBoxLayout* addPlayerLayout = new QHBoxLayout();
    playerNameInput = new QLineEdit();
    QPushButton* addPlayerButton = new QPushButton("Add Player");
    addPlayerLayout->addWidget(playerNameInput);
    addPlayerLayout->addWidget(addPlayerButton);
    mainLayout->addLayout(addPlayerLayout);

    QPushButton* startGameButton = new QPushButton("Start Game");
    mainLayout->addWidget(startGameButton);

    actionGroup = new QGroupBox("Actions");
    QVBoxLayout* actionLayout = new QVBoxLayout();
    for (const QString& act : {"Gather", "Tax", "Bribe", "Arrest", "Sanction", "Coup"}) {
        QPushButton* btn = new QPushButton(act);
        actionButtons.push_back(btn);
        actionLayout->addWidget(btn);
        connect(btn, &QPushButton::clicked, this, [this, act]() {
            handleAction(act);
        });
    }

    spyButton = new QPushButton("Spy on Player");
    actionLayout->addWidget(spyButton);
    spyButton->hide();
    connect(spyButton, &QPushButton::clicked, this, &GUI::handleSpyAction);

    actionGroup->setLayout(actionLayout);
    actionGroup->setVisible(false);
    mainLayout->addWidget(actionGroup);

    connect(addPlayerButton, &QPushButton::clicked, this, &GUI::addPlayer);
    connect(startGameButton, &QPushButton::clicked, this, &GUI::startGame);

    setCentralWidget(central);
    resize(600, 500);
}

void GUI::addPlayer() {
    QString name = playerNameInput->text().trimmed();
    if (name.isEmpty()) return;

    try {
        game.addPlayer(name.toStdString());
        playerList->addItem(name);
        playerNameInput->clear();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void GUI::startGame() {
    try {
        game.startGame();
        updateGameView();
        actionGroup->setVisible(true);
    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Start Failed", e.what());
    }
}

void GUI::handleAction(const QString& actionName) {
    try {
        ActionFactory factory;
        std::unique_ptr<Action> action = factory.createAction(actionName.toStdString());

        bool needsTarget = action->isType("Arrest") || action->isType("Sanction") || action->isType("Coup");
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
                return;
            }
        }

        game.playTurn(*action, targetIndex);
        updateGameView();

    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Action Error", e.what());
    }
}

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
            Action dummy(Action::ActionType::Tax); // Safe dummy
            current->getrole()->roleonaction(*current, dummy,target);
        }
        updateGameView();
    }
}

void GUI::updateGameView() {
    std::string current = game.turn();
    if (current.empty()) {
        statusLabel->setText("Game Over! Winner: " + QString::fromStdString(game.winner()));
        actionGroup->setVisible(false);
    } else {
        QString role = QString::fromStdString(game.getCurrentPlayerRole());
        int coins = game.getCurrentPlayerCoins();
        statusLabel->setText("Turn: " + QString::fromStdString(current) + " | Role: " + role + " | Coins: " + QString::number(coins));

        spyButton->setVisible(role == "Spy");
    }
}
