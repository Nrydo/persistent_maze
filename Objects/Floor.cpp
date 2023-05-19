#include "Floor.h"

Floor::Floor(Item* item_) : item(item_) {
    setPixmap(QPixmap(":textures/floor.png"));
}

Floor::Floor(const Floor& other) : Object(other), item(nullptr) {
    if (other.item) {
        item = other.item->Copy();
    }
    setPixmap(QPixmap(":textures/floor.png"));
}

Floor* Floor::Copy() const {
    return new Floor(*this);
}

void Floor::Press(Player* player) {
    if (item) {
        item->Interact(player, this);
    }
}

void Floor::SetItem(Item *item_) {
    item = item_;
}

Item *Floor::GetItem() {
    return item;
}

void Floor::RemoveItem() {
    item = nullptr;
    update();
}

void Floor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QGraphicsPixmapItem::paint(painter, option, widget);
    if (item) {
        item->setPos(pos());
        item->paint(painter, option, widget);
    }
}

Floor::~Floor() {
    if (item) {
        delete item;
    }
}
