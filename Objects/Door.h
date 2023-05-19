#pragma once

#include "Floor.h"
#include "../Items/Key.h"

class Door : public Object {
    Q_OBJECT

public:
    Door(const QColor &color_ = Qt::transparent);
    Door(const Door& other);
    Door* Copy() const override;
    void Interact(Player *player = nullptr) override;
    void Open();
    void Close();

private:
    QColor color;

};
