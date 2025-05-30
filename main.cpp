//timsitmelosa@gmail.com
#include <QApplication>
#include "Gamelogic/GUI.hpp"
#include "Gamelogic/Game.hpp"
int main(int argc, char *argv[]) {
    try {
        QApplication app(argc, argv);
        Game game;
        GUI gui(game);
        gui.show();
        return app.exec();
    } catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}

