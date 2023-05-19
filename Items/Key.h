#pragma once

#include "../Item.h"
#include "../Objects/Floor.h"

class Key : public Item {
    Q_OBJECT

public:
    Key(const QColor &color_ = Qt::transparent);
    Key(const Key& other);
    Key* Copy() const override;
    void Interact(Player *player = nullptr, Object *object = nullptr) override;
    QColor GetColor() const;
    void SetColor(const QColor &color_);

private:
    QColor color;

};
