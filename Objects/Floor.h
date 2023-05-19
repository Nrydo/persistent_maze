#pragma once

#include "../Object.h"
#include "../Item.h"

class Floor : public Object{
    Q_OBJECT

public:
    Floor(Item *item_ = nullptr);
    Floor(const Floor& other);
    Floor* Copy() const override;
    void Press(Player *player = nullptr) override;
    void SetItem(Item *item_);
    Item *GetItem();
    void RemoveItem();
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
    ~Floor();

private:
    Item *item;

};
