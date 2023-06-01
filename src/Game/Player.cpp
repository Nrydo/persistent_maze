#include "Player.h"
#include "Items/Item.h"
#include "Field.h"

Player::Player() : QGraphicsPixmapItem(QPixmap(":resources/textures/player2.png")), direction(2) {
    setZValue(2);
}

void Player::PutInInventory(Item* item) {
    item->setPos(inventory.size() * 32, 0);
    inventory.push_back(item);
    emit UpdateInventory(inventory);
}

void Player::RemoveFromInventory(Item* item) {
    inventory.erase(std::find(inventory.begin(), inventory.end(), item));
    delete item;
    emit UpdateInventory(inventory);
}

const std::vector<Item*>& Player::GetInventory() const {
    return inventory;
}

int Player::GetDirection() const {
    return direction;
}

void Player::SetDirection(int direction_) {
    direction = direction_;
    setPixmap(QPixmap(":resources/textures/player" + QString::number(direction) + ".png"));
}

Field* Player::GetField() const {
    return field;
}

void Player::SetField(Field* field_) {
    field = field_;
}
