#pragma once

#include <QGraphicsItem>
#include "../Player.h"
#include "../Animations/AnimationController.h"

class Field;

class Object : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Object(Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Object(const Object& other, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    virtual Object* Copy(Field *field_ = nullptr, int x_ = -1, int y_ = -1) const;
    virtual QString Code() const;
    virtual bool GetColliding() const;
    virtual void SetColliding(bool value);
    Field* GetField() const;
    void SetField(Field* field_);
    int GetX() const;
    int GetY() const;
    void SetX(int x_);
    void SetY(int y_);
    void SetPos(int x_, int y_);
    AnimationController* GetAnimationController();
    virtual void Interact(Player* player = nullptr);
    virtual void Press(Player* player = nullptr);
    virtual void Release(Player* player = nullptr);

protected:
    bool colliding;
    Field* field;
    int x;
    int y;

};
