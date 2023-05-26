#include "Item.h"
#include "../Objects/Object.h"

Item::Item() : colliding(false) {
    setZValue(1);
}

Item::Item(const Item &other) : colliding(other.colliding) {
    setPixmap(other.pixmap());
    setZValue(other.zValue());
}

Item* Item::Copy() const {
    return new Item(*this);
}

bool Item::GetColliding() const {
    return colliding;
}

void Item::SetColliding(bool value) {
    colliding = value;
}

void Item::Press(Player *player, Object *object) {}

void Item::Interact(Player *player, Object *object) {}
