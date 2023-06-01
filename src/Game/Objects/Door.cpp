#include "Door.h"
#include "../Field.h"

Door::Door(Field *field_, int x_, int y_) : Object(field_, x_, y_), color(Qt::transparent) {
    colliding = true;
    setPixmap(QPixmap(":resources/textures/door.png"));
}

Door::Door(const QColor& color_, Field *field_, int x_, int y_) : Object(field_, x_, y_), color(color_)  {
    colliding = true;
    setPixmap(QPixmap(":resources/textures/door.png"));
}

Door::Door(const Door& other, Field *field_, int x_, int y_) : Object(other, field_, x_, y_), color(other.color) {
    setPixmap(other.pixmap());
}

Door* Door::Copy(Field *field_, int x_, int y_) const {
    return new Door(*this, field_, x, y);
}

QString Door::Code() const {
    return "D";
}

void Door::Interact(Player* player) {
    for (const auto& item : player->GetInventory()) {
        if (dynamic_cast<Key*>(item)->GetColor() == color) {
            player->RemoveFromInventory(item);
            field->RemoveObject(x, y);
            new Floor(field, x, y);
            delete this;
            return;
        }
    }
}
