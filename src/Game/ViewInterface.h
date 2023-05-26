#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Player.h"
#include "Items/Item.h"

class ViewInterface : public QGraphicsView {
    Q_OBJECT

public:
    ViewInterface(QWidget* parent = nullptr);
    void wheelEvent(QWheelEvent* event) override;

private:
    QGraphicsScene* scene;
    QGraphicsItemGroup* inventory;

public slots:
     void UpdateInventory(const std::vector<Item*>& items);

};
