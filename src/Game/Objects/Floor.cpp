#include "Floor.h"
#include "../Field.h"
#include <QGraphicsScene.h>

Floor::Floor(Field* field_, int x_, int y_) : Object(field_, x_, y_), item(nullptr) {
    setPixmap(QPixmap(":resources/textures/floor.png"));
}

Floor::Floor(Item* item_, Field* field_, int x_, int y_) : Object(field_, x_, y_), item(item_) {
    setPixmap(QPixmap(":resources/textures/floor.png"));
    field->addToGroup(item);
    item->setPos(pos());
}

Floor::Floor(const Floor& other, Field* field_, int x_, int y_) : Object(other, field_, x_, y_), item(nullptr) {
    if (other.item) {
        item = other.item->Copy();
        field->addToGroup(item);
        item->setPos(pos());
    }
    setPixmap(other.pixmap());
}

Floor* Floor::Copy(Field* field_, int x_, int y_) const {
    return new Floor(*this, field_, x, y);
}

QString Floor::Code() const {
    return "F";
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

#include <iostream>

void Floor::SetItem(Item* item_) {
    item = item_;
    field->addToGroup(item);
    item->setPos(pos());
}

Item* Floor::GetItem() {
    return item;
}

void Floor::RemoveItem() {
    field->removeFromGroup(item);
    item->setPos(0, 0);
    scene()->removeItem(item);
    item = nullptr;
}

Floor::~Floor() {
    if (item) {
        delete item;
    }
}

