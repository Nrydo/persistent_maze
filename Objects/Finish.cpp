#include "Finish.h"

Finish::Finish() {
    setPixmap(QPixmap(":textures/finish.png"));
}

Finish::Finish(const Finish &other) : Object(other) {
    setPixmap(QPixmap(":textures/finish.png"));
}

Finish* Finish::Copy() const {
    return new Finish(*this);
}

void Finish::Press(Player *player) {
    emit FinishGame();
}


