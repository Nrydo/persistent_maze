#pragma once

#include "Object.h"

class Finish : public Object {
Q_OBJECT

public:
    Finish(Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Finish(const Finish& other, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Finish* Copy(Field *field_ = nullptr, int x_ = -1, int y_ = -1) const override;
    QString Code() const override;
    void Press(Player *player = nullptr) override;

signals:
    void GameFinished();

};
