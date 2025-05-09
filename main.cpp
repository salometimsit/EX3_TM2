#include <QApplication>
#include "GUI.hpp"
#include "Game.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Game game;
    GUI gui(game);
    gui.show();

    return app.exec();
}

