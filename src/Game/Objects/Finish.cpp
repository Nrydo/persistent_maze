#include "Finish.h"

Finish::Finish(Field *field_, int x_, int y_) : Object(field_, x_, y_) {
    setPixmap(QPixmap(":textures/finish.png"));
}

Finish::Finish(const Finish &other, Field *field_, int x_, int y_) : Object(other, field_, x_, y_) {
    setPixmap(QPixmap(":textures/finish.png"));
}

Finish* Finish::Copy(Field *field_, int x_, int y_) const {
    return new Finish(*this, field_, x, y);
}

void Finish::Press(Player *player) {
    emit GameFinished();
}
