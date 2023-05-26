#pragma once

#include "../Items/Item.h"
#include "Floor.h"
#include "Void.h"

class ArrowFloor : public Floor {
    Q_OBJECT

public:
    ArrowFloor(int direction_, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    ArrowFloor(Item* item, int direction_, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    ArrowFloor(const ArrowFloor& other, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    ArrowFloor* Copy(Field *field_ = nullptr, int x_ = -1, int y_ = -1) const override;
    void Press(Player *player = nullptr) override;

private:
    int direction;

};
