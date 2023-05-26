#pragma once

#include "Object.h"
#include "../Items/Item.h"

class Floor : public Object {
    Q_OBJECT

public:
    Floor(Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Floor(Item* item, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Floor(const Floor& other, Field* field_ = nullptr, int x_ = -1, int y_ = -1);
    Floor* Copy(Field *field_ = nullptr, int x_ = -1, int y_ = -1) const override;
    bool GetColliding() const override;
    void Interact(Player *player = nullptr) override;
    void Press(Player *player = nullptr) override;
    void SetItem(Item *item_);
    Item *GetItem();
    void RemoveItem();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    ~Floor();

private:
    Item *item;

};
