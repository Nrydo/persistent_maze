#pragma once

#include "Floor.h"
#include "../Items/Key.h"

class Door : public Object {
    Q_OBJECT

public:
    Door(Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Door(const QColor &color_, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Door(const Door& other, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Door* Copy(Field *field_ = nullptr, int x_ = -1, int y_ = -1) const override;
    void Interact(Player *player = nullptr) override;

private:
    QColor color;

};
