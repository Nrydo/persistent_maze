#include <QApplication>
#include "PersistentMaze.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    PersistentMaze window(1200, 900);
    window.show();
    return QApplication::exec();
}
