#include "Item.h"
#include "Object.h"

Item::Item() {
    setZValue(1);
}

Item::Item(const Item &other) {
    setZValue(1);
}

Item* Item::Copy() const {
    return new Item(*this);
}

void Item::Interact(Player *player, Object *object) {}
