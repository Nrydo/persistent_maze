#pragma once

#include "Object.h"

class Void : public Object {
Q_OBJECT

public:
    Void(Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Void(const Void& other, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Void* Copy(Field *field_ = nullptr, int x_ = -1, int y_ = -1) const override;

};
