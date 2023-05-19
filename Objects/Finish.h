#pragma once

#include "../Object.h"

class Finish : public Object {
Q_OBJECT

public:
    Finish();
    Finish(const Finish& other);
    Finish* Copy() const override;
    void Press(Player *player = nullptr) override;

signals:
    void FinishGame();

};
