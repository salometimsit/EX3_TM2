#include "GUI.hpp"
#include <QInputDialog>
#include <QMessageBox>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QFile>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QApplication>
#include "Actions/ActionFactory.hpp"


GUI::GUI(Game& g, QWidget* parent) : QMainWindow(parent), game(g) {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    stackedLayout = new QStackedLayout();
    central->setLayout(stackedLayout);

    // === Add Player Screen ===
    addPlayerScreen = new QWidget();
    addPlayerScreen->setObjectName("AddPlayerScreen");
    
    QPixmap addBg("/home/salome/projects/EX3/images/player_background.jpg");
    addBg = addBg.scaled(600, 800, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation); // or your fixed size

    QPalette addPalette;
    addPalette.setBrush(QPalette::Window, addBg);
    addPlayerScreen->setAutoFillBackground(true);
    addPlayerScreen->setPalette(addPalette);
    QVBoxLayout* addLayout = new QVBoxLayout(addPlayerScreen);
    addLayout->setContentsMargins(150, 300, 150, 100);

    nameInput = new QLineEdit();
    nameInput->setPlaceholderText("Enter player name");
    addLayout->addWidget(nameInput);

    QPushButton* addBtn = new QPushButton("ADD");
    QPushButton* startBtn = new QPushButton("START");
    errorLabel = new QLabel();
    errorLabel->setStyleSheet("color: red; font-size: 16px");

    addLayout->addWidget(addBtn);
    addLayout->addWidget(startBtn);
    addLayout->addWidget(errorLabel);

    connect(addBtn, &QPushButton::clicked, this, &GUI::addPlayer);
    connect(startBtn, &QPushButton::clicked, this, &GUI::startGame);
    

    // === Main Game Screen ===
    gameScreen = new QWidget(this);  // Ensure parent is set
    addPlayerScreen->setObjectName("AddPlayerScreen");
    gameScreen->setObjectName("GameScreen");

    QPixmap gameBg("/home/salome/projects/EX3/images/main_background.jpg");
    gameBg = gameBg.scaled(600, 800, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPalette gamePalette;
    gamePalette.setBrush(QPalette::Window, gameBg);

    gameScreen->setAutoFillBackground(true);
    gameScreen->setPalette(gamePalette);

    QVBoxLayout* mainLayout = new QVBoxLayout(gameScreen);
    mainLayout->setContentsMargins(20, 20, 20, 20);  // Optional spacing from edge

    statusLabel = new QLabel("Welcome to Coup");
    statusLabel->setStyleSheet("color: #F9E79F; font-size: 20px; font-weight: bold;"); // Optional style
    mainLayout->addWidget(statusLabel);

    playerList = new QListWidget();
    mainLayout->addWidget(playerList);

    actionGroup = new QGroupBox("Actions");
    QVBoxLayout* actionLayout = new QVBoxLayout();

    QStringList actions = {"Gather", "Tax", "Bribe", "Arrest", "Sanction", "Coup"};
    for (const QString& act : actions) {
        QPushButton* btn = new QPushButton(act);
        btn->setStyleSheet("font-size: 18px; padding: 6px; color: #D4AF37; background-color: rgba(0,0,0,0.6); border: 1px solid #D4AF37;");
        actionButtons.push_back(btn);
        actionLayout->addWidget(btn);

        connect(btn, &QPushButton::clicked, this, [this, act]() {
            handleAction(act);
        });
    }

    spyButton = new QPushButton("Spy on Player");
    BaronButton = new QPushButton("Barons investment");
    BaronButton->setStyleSheet("font-size: 18px; padding: 6px; color: #D4AF37; background-color: rgba(0,0,0,0.6); border: 1px solid #D4AF37;");
    spyButton->setStyleSheet("font-size: 18px; padding: 6px; color: #D4AF37; background-color: rgba(0,0,0,0.6); border: 1px solid #D4AF37;");
    actionLayout->addWidget(spyButton);
    actionLayout->addWidget(BaronButton);
    spyButton->hide();
    BaronButton->hide();

    connect(spyButton, &QPushButton::clicked, this, &GUI::handleSpyAction);
    connect(BaronButton, &QPushButton::clicked, this, &GUI::handleBaronAction);

    actionGroup->setLayout(actionLayout);
    actionGroup->setVisible(false);
    mainLayout->addWidget(actionGroup);

    stackedLayout->addWidget(addPlayerScreen);
    stackedLayout->addWidget(gameScreen);
    stackedLayout->setCurrentWidget(addPlayerScreen);
    qDebug() << "GUI ready, showing AddPlayer screen";
}


void GUI::addPlayer() {
    QString name = nameInput->text().trimmed();
    if (name.isEmpty()) return;

    try {
        game.addPlayer(name.toStdString());
        nameInput->clear();
        errorLabel->setText("");
    } catch (const std::exception& e) {
        errorLabel->setText(e.what());
    }
}


void GUI::startGame() {
    try {
        game.startGame();

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

void GUI::handleAction(const QString& actionName) {
    try {
        ActionFactory factory;
        std::unique_ptr<Action> action = factory.createAction(actionName.toStdString());
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
                return;
            }
        }

        if (needsTarget && targetIndex >= 0) {
            Player* targetPlayer = game.getPlayerByIndex(targetIndex);
            QString targetName = QString::fromStdString(targetPlayer->getnameplayer());

            // Ask target player if they want to block
            if (targetPlayer->getrole() && targetPlayer->getrole()->canblock(*action)) {
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Block Action",
                    targetName + ", do you want to block the action: " + actionName + "?",
                    QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    try {
                        game.blockaction(*targetPlayer, *action, *game.getCurrentPlayer());
                        QMessageBox::information(this, "Blocked", "The action was blocked!");
                        updateGameView();
                        return;
                    } catch (const std::exception& e) {
                        QMessageBox::warning(this, "Block Failed", e.what());
                        return;
                    }
                }
            }

            // If not blocked, continue with the action
            game.playTurn(*action, targetIndex);
            updateGameView();
        }

        // Handle actions that don't require a target
        if (!needsTarget) {
            game.playTurn(*action, -1);
            updateGameView();
        }

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
            int others_coins = current->getrole()->rolespecialities(*current, game, target);
            QMessageBox::information(this, "Spy",
            "You spied on " + QString::fromStdString(target->getnameplayer()) +
            ". They have " + QString::number(others_coins) + " coins.\n"
            "They are now blocked from using Arrest next turn.");
        }

        updateGameView();
    }
}
void  GUI::handleBaronAction(){
    Player* current = game.getCurrentPlayer();
    if (current->getcoins() < 3) {
        QMessageBox::warning(this, "Insufficient Coins", "You need at least 3 coins to use Baron's ability.");
        return;
    }
    bool ok;
    QStringList items;
    for (const auto& name : game.playersList()) {
        if (name != game.turn())
            items << QString::fromStdString(name);
    }
    QString selected = QInputDialog::getItem(this, "Baron", "Invest 3 coins get 6:", items, 0, false, &ok);
    if (!ok) return;
    if (current && current->getrole()) {
        current->getrole()->rolespecialities(*current,game);
    }
    updateGameView();
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
        BaronButton->setVisible(role == "Baron");
    }
}
