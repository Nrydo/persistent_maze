#include "ArrowFloor.h"
#include "../Field.h"

ArrowFloor::ArrowFloor(int direction_, Field *field_, int x_, int y_) : Floor(field_, x_, y_), direction(direction_) {
    setPixmap(QPixmap(":resources/textures/arrow_floor.png").transformed(QTransform().rotate(90 * direction)));
}

ArrowFloor::ArrowFloor(Item* item_, int direction_, Field *field_, int x_, int y_) :
        Floor(item_, field_, x_, y_), direction(direction_) {
    setPixmap(QPixmap(":resources/textures/arrow_floor.png").transformed(QTransform().rotate(90 * direction)));
}

ArrowFloor::ArrowFloor(const ArrowFloor& other, Field *field_, int x_, int y_) :
        Floor(other, field_, x_, y_), direction(other.direction) {
    setPixmap(other.pixmap());
}

ArrowFloor* ArrowFloor::Copy(Field *field_, int x_, int y_) const {
    return new ArrowFloor(*this, field_, x, y);
}

QString ArrowFloor::Code() const {
    return "A," + QString::number(direction);
}

void ArrowFloor::Press(Player *player) {
    int player_direction = player->GetDirection();
    field->MovePlayer(direction);
    player->SetDirection(player_direction);
}
