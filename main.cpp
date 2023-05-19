#include "View.h"
#include <QApplication>

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    View view(750, 750);
    view.show();
    return QApplication::exec();
}
