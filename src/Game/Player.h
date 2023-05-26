#pragma once

#include <algorithm>
#include <QGraphicsPixmapItem>

class Item;
class Field;

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Player();
    void PutInInventory(Item* item);
    void RemoveFromInventory(Item* item);
    const std::vector<Item*>& GetInventory() const;
    int GetDirection() const;
    void SetDirection(int direction_);
    Field* GetField() const;
    void SetField(Field* field_);

private:
    std::vector<Item*> inventory;
    int direction;
    Field* field;

signals:
    void UpdateInventory(const std::vector<Item*>& items);

};
