#pragma once

#include "Item.h"
#include "../Objects/Floor.h"

class Box : public Item {
    Q_OBJECT

public:
    Box();
    Box(const Box& other);
    Box* Copy() const override;
    void Interact(Player *player = nullptr, Object *object = nullptr) override;

};
