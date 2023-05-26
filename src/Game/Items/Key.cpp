#include "Key.h"

Key::Key(const QColor& color_) : color(color_) {
    setPixmap(QPixmap(":textures/key.png"));
}

Key::Key(const Key& other) : Item(other), color(other.color) {}

Key* Key::Copy() const {
    return new Key(*this);
}

void Key::Press(Player* player, Object* object) {
    player->PutInInventory(this);
    dynamic_cast<Floor*>(object)->RemoveItem();
}

QColor Key::GetColor() const {
    return color;
}

void Key::SetColor(const QColor& color_) {
    color = color_;
}
