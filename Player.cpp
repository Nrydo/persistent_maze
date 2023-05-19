#include "Player.h"
#include "Item.h"

Player::Player() : QGraphicsPixmapItem(QPixmap(":textures/player.png")) {
    setZValue(2);
}

void Player::PutInInventory(Item* item) {
    item->setPos(inventory.size() * 32, 0);
    inventory.push_back(item);
}

void Player::RemoveFromInventory(Item* item) {
    inventory.erase(std::find(inventory.begin(), inventory.end(), item));
}

const std::vector<Item*>& Player::GetInventory() const {
    return inventory;
}

int Player::GetDirection() const {
    return direction;
}

void Player::SetDirection(int direction_) {
    direction = direction_;
}
