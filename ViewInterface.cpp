#include "ViewInterface.h"
#include "View.h"

#include <iostream>

ViewInterface::ViewInterface(Player* player_, QWidget* parent) :
        QGraphicsView(parent),
        player(player_),
        scene(new QGraphicsScene(this)),
        inventory(new QGraphicsItemGroup) {

    resize(0, 32 * 4);
    QPalette pal;
    pal.setColor(QPalette::Base, Qt::transparent);
    setPalette(pal);
    setFrameShape(QFrame::NoFrame);

    scene->setSceneRect(0, 0, contentsRect().width(), contentsRect().height());
    scene->addItem(inventory);

    setScene(scene);

}

void ViewInterface::update() {
    for (auto item : inventory->childItems()) {
        inventory->removeFromGroup(item);
        item->setScale(1);
    }
    auto& items = player->GetInventory();
    resize(items.size() * 32 * 4, 32 * 4);
    setSceneRect(0, 0, contentsRect().width(), contentsRect().height());
    for (int i = 0; i < items.size(); i++) {
        inventory->addToGroup(items[i]);
        items[i]->setScale(4);
        items[i]->setPos(i * 32 * 4, 0);
    }
    QWidget::update();
}

void ViewInterface::wheelEvent(QWheelEvent *event) {
    dynamic_cast<View*>(parent())->wheelEvent(event);
    QGraphicsView::wheelEvent(event);
}
