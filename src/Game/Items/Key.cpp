#include "Key.h"

Key::Key(const QColor& color_) : color(color_) {
    auto image = QPixmap(":resources/textures/key.png").toImage();
    image.setPixel(11, 11, color.rgba());
    image.setPixel(10, 11, color.rgba());
    image.setPixel(11, 10, color.rgba());
    image.setPixel(11, 12, color.rgba());
    image.setPixel(12, 11, color.rgba());
    setPixmap(QPixmap::fromImage(image));
}

Key::Key(const Key& other) : Item(other), color(other.color) {}

Key* Key::Copy() const {
    return new Key(*this);
}

QString Key::Code() const {
    return "K";
}

void Key::Press(Player* player, Object* object) {
    dynamic_cast<Floor*>(object)->RemoveItem();
    player->PutInInventory(this);
}

QColor Key::GetColor() const {
    return color;
}

void Key::SetColor(const QColor& color_) {
    color = color_;
}
