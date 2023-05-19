#include "Door.h"

Door::Door(const QColor& color_) : color(color_)  {
    colliding = true;
    setPixmap(QPixmap(":textures/closed_door.png"));
}

Door::Door(const Door& other) : Object(other), color(other.color) {
    setPixmap(other.pixmap());
}

Door* Door::Copy() const {
    return new Door(*this);
}

void Door::Interact(Player* player) {
    for (const auto& item : player->GetInventory()) {
        if (dynamic_cast<Key*>(item)->GetColor() == color) {
            colliding = !colliding;
            setPixmap(QPixmap(":textures/opened_door.png"));
            break;
        }
    }
}

void Door::Open() {
    colliding = false;

}

void Door::Close() {
    colliding = true;
}
