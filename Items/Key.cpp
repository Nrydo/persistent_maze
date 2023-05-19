#include "Key.h"

Key::Key(const QColor& color_) : color(color_) {
    setPixmap(QPixmap(":textures/key.png"));
}

Key::Key(const Key& other) : Item(other), color(other.color) {
    setPixmap(QPixmap(":textures/key.png"));
}

Key* Key::Copy() const {
    return new Key(*this);
}

void Key::Interact(Player* player, Object* object) {
    if (player) {
        player->PutInInventory(this);
    }
    if (object) {
        dynamic_cast<Floor*>(object)->RemoveItem();
    }
}

QColor Key::GetColor() const {
    return color;
}

void Key::SetColor(const QColor& color_) {
    color = color_;
}
