#pragma once

#include <QGraphicsItem>
#include "Player.h"

class Object;

class Item : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Item();
    Item(const Item& other);
    virtual Item* Copy() const;
    virtual void Interact(Player *player = nullptr, Object *object = nullptr);

};
