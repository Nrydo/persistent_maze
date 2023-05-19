#include "Wall.h"

Wall::Wall() {
    colliding = true;
    setPixmap(QPixmap(":textures/wall.png"));
}

Wall::Wall(const Wall& other) : Object(other) {
    setPixmap(QPixmap(":textures/wall.png"));
}

Wall* Wall::Copy() const {
    return new Wall(*this);
}
