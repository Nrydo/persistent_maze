#pragma once

#include "Object.h"

class Wall : public Object {
    Q_OBJECT

public:
    Wall(Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Wall(const Wall& other, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Wall* Copy(Field *field_ = nullptr, int x_ = -1, int y_ = -1) const override;

};
