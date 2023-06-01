#include "FragileFloor.h"
#include "../Field.h"

FragileFloor::FragileFloor(Field *field_, int x_, int y_) : Floor(field_, x_, y_) {
    setPixmap(QPixmap(":resources/textures/fragile_floor.png"));
}

FragileFloor::FragileFloor(Item* item_, Field *field_, int x_, int y_) : Floor(item_, field_, x_, y_) {
    setPixmap(QPixmap(":resources/textures/fragile_floor.png"));
}

FragileFloor::FragileFloor(const FragileFloor& other, Field *field_, int x_, int y_) :
        Floor(other, field_, x_, y_) {
    setPixmap(other.pixmap());
}

FragileFloor* FragileFloor::Copy(Field *field_, int x_, int y_) const {
    return new FragileFloor(*this, field_, x, y);
}

QString FragileFloor::Code() const {
    return "B";
}

void FragileFloor::Release(Player *player) {
    field->RemoveObject(x, y);
    new Void(field, x, y);
    delete this;
}
