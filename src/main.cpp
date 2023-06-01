#include <QApplication>
#include "PersistentMaze.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    PersistentMaze window;
    window.show();
    return QApplication::exec();
}
