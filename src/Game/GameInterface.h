#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Player.h"
#include "Items/Item.h"

class GameInterface : public QGraphicsView {
    Q_OBJECT

public:
    GameInterface(QWidget* parent = nullptr);
    void wheelEvent(QWheelEvent* event) override;

private:
    QGraphicsScene* scene;
    QGraphicsItemGroup* inventory;

public slots:
     void UpdateInventory(const std::vector<Item*>& items);

};
