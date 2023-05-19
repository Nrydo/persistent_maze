#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Player.h"
#include "Item.h"

class ViewInterface : QGraphicsView {
    Q_OBJECT

public:
    ViewInterface(Player* player_, QWidget* parent = nullptr);
    void update();
    void wheelEvent(QWheelEvent* event) override;

private:
    QGraphicsScene* scene;
    QGraphicsItemGroup* inventory;
    Player* player;

};
