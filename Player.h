#pragma once

#include <algorithm>
#include <QGraphicsPixmapItem>

class Item;

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    Player();
    void PutInInventory(Item* item);
    void RemoveFromInventory(Item* item);
    const std::vector<Item*>& GetInventory() const;
    int GetDirection() const;
    void SetDirection(int direction_);

private:
    std::vector<Item*> inventory;
    int direction;

};
