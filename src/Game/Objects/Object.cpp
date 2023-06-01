#include "Object.h"
#include "../Field.h"

Object::Object(Field* field_, int x_, int y_) :
        colliding(false), field(field_), x(x_), y(y_) {
    field->PutObject(this, x, y);
}

Object::Object(const Object& other, Field* field_, int x_, int y_) :
        colliding(other.colliding), field(field_), x(x_), y(y_) {
    field->PutObject(this, x, y);
}

Object* Object::Copy(Field *field_, int x_, int y_) const {
    return new Object(*this, field_, x, y);
}

QString Object::Code() const {
    return "O";
}

bool Object::GetColliding() const {
    return colliding;
}

void Object::SetColliding(bool value) {
    colliding = value;
}

Field* Object::GetField() const {
    return field;
}

void Object::SetField(Field *field_) {
    field = field_;
}

int Object::GetX() const {
    return x;
}

int Object::GetY() const {
    return y;
}

void Object::SetX(int x_) {
    x = x_;
}

void Object::SetY(int y_) {
    y = y_;
}

void Object::SetPos(int x_, int y_) {
    x = x_;
    y = y_;
}

AnimationController* Object::GetAnimationController() {
    return field->GetAnimationController();
}

void Object::Interact(Player* player) {}

void Object::Press(Player* player) {}

void Object::Release(Player *player) {}
