#include "Void.h"

Void::Void(Field *field_, int x_, int y_) : Object(field_, x_, y_) {
    colliding = true;
    auto pixmap_ = QPixmap(32, 32);
//    pixmap_.fill(Qt::transparent);
    pixmap_.fill(Qt::white);
    setPixmap(pixmap_);
}

Void::Void(const Void& other, Field *field_, int x_, int y_) : Object(other, field_, x_, y_) {
    setPixmap(other.pixmap());
}

Void* Void::Copy(Field *field_, int x_, int y_) const {
    return new Void(*this, field_, x, y);
}
