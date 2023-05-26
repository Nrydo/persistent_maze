#pragma once

#include "../Items/Item.h"
#include "Floor.h"
#include "Void.h"

class FragileFloor : public Floor {
Q_OBJECT

public:
    FragileFloor(Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    FragileFloor(Item* item, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    FragileFloor(const FragileFloor& other, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    FragileFloor* Copy(Field *field_ = nullptr, int x_ = -1, int y_ = -1) const override;
    void Release(Player *player = nullptr) override;

};
