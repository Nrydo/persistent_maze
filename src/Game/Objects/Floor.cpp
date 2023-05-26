#include "Floor.h"

Floor::Floor(Field* field_, int x_, int y_) : Object(field_, x_, y_), item(nullptr) {
    setPixmap(QPixmap(":textures/floor.png"));
}

Floor::Floor(Item* item_, Field* field_, int x_, int y_) : Object(field_, x_, y_), item(item_) {
    setPixmap(QPixmap(":textures/floor.png"));
}

Floor::Floor(const Floor& other, Field* field_, int x_, int y_) : Object(other, field_, x_, y_), item(nullptr) {
    if (other.item) {
        item = other.item->Copy();
    }
    setPixmap(other.pixmap());
}

Floor* Floor::Copy(Field* field_, int x_, int y_) const {
    return new Floor(*this, field_, x, y);
}

bool Floor::GetColliding() const {
    return Object::GetColliding() || (item && item->GetColliding());
}

void Floor::Interact(Player* player) {
    if (item) {
        item->Interact(player, this);
    }
}

void Floor::Press(Player* player) {
    if (item) {
        item->Press(player, this);
    }
}

void Floor::SetItem(Item* item_) {
    item = item_;
    update();
}

Item* Floor::GetItem() {
    return item;
}

void Floor::RemoveItem() {
    item = nullptr;
    update();
}

void Floor::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) {
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

