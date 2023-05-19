#include "Object.h"

Object::Object() : colliding(false) {}

Object::Object(const Object& other) : colliding(other.colliding) {}

Object* Object::Copy() const {
    return new Object(*this);
}

bool Object::GetColliding() const {
    return colliding;
}

void Object::SetColliding(bool value) {
    colliding = value;
}

void Object::Interact(Player* player) {}

void Object::Press(Player* player) {}
