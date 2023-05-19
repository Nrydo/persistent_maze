#pragma once

#include <QGraphicsItem>
#include "Player.h"

class Object : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Object();
    Object(const Object& other);
    virtual Object* Copy() const;
    bool GetColliding() const;
    void SetColliding(bool value);
    virtual void Interact(Player* player = nullptr);
    virtual void Press(Player* player = nullptr);

protected:
    bool colliding;

};
