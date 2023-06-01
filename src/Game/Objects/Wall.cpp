#include "Wall.h"

Wall::Wall(Field *field_, int x_, int y_) : Object(field_, x_, y_) {
    colliding = true;
    setPixmap(QPixmap(":resources/textures/wall.png"));
}

Wall::Wall(const Wall& other, Field *field_, int x_, int y_) : Object(other, field_, x_, y_) {
    setPixmap(QPixmap(":resources/textures/wall.png"));
}

Wall* Wall::Copy(Field *field_, int x_, int y_) const {
    return new Wall(*this, field_, x, y);
}

QString Wall::Code() const {
    return "W";
}
