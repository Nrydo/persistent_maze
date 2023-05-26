#include "ViewInterface.h"
#include "Game.h"

#include <iostream>

ViewInterface::ViewInterface(QWidget* parent) :
        QGraphicsView(parent),
        scene(new QGraphicsScene(this)),
        inventory(new QGraphicsItemGroup) {

    resize(0, 0);
    scale(4, 4);
    QPalette pal;
    pal.setColor(QPalette::Base, Qt::transparent);
    setPalette(pal);
    setFrameShape(QFrame::NoFrame);

    scene->setSceneRect(QRect());
    scene->addItem(inventory);

    setScene(scene);

}

void ViewInterface::wheelEvent(QWheelEvent *event) {
    dynamic_cast<Game*>(parent())->wheelEvent(event);
    QGraphicsView::wheelEvent(event);
}

void ViewInterface::UpdateInventory(const std::vector<Item*>& items) {
    for (auto item : inventory->childItems()) {
        inventory->removeFromGroup(item);
    }
    resize(items.size() * 32 * 4, 32 * 4);
    setSceneRect(0, 0, items.size() * 32, 32);
    for (int i = 0; i < items.size(); i++) {
        inventory->addToGroup(items[i]);
        items[i]->setPos(i * 32, 0);
    }
}
