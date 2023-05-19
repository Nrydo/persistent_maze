#pragma once

#include "../Object.h"

class Wall : public Object {
    Q_OBJECT

public:
    Wall();
    Wall(const Wall& other);
    Wall* Copy() const override;

};
