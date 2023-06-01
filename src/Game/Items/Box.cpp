#include "Box.h"
#include "../Field.h"

Box::Box() {
    setPixmap(QPixmap(":resources/textures/box.png"));
    colliding = true;
}

Box::Box(const Box& other) : Item(other) {}

Box* Box::Copy() const {
    return new Box(*this);
}

QString Box::Code() const {
    return "B";
}

void Box::Interact(Player* player, Object* object) {
    int direction = player->GetDirection();
    int pnx = object->GetX() + (direction - 1) % 2;
    int pny = object->GetY() + (2 - direction) % 2;
    if (pnx < 0 || pny < 0 || pnx >= object->GetField()->Width() || pny >= object->GetField()->Width()) {
        return;
    }
    if ((*object->GetField())[pnx][pny]->GetColliding()) {
        return;
    }
    auto begin = pos();
    dynamic_cast<Floor*>(object)->SetColliding(false);
    dynamic_cast<Floor*>(object)->RemoveItem();
    (*object->GetField())[pnx][pny]->SetColliding(true);
    object->GetField()->PutItem(this, pnx, pny);
    auto end = pos();
    setPos(begin);
    object->GetAnimationController()->AddMoveAnimation(this, {end}, 2);
}
