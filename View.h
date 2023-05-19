#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QGraphicsTextItem>
#include <QFont>
#include <QLine>
#include "ViewInterface.h"
#include "Field.h"

class View : public QGraphicsView {
    Q_OBJECT

public:
    View(int width_, int height_);
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    ViewInterface* interface;
    QGraphicsScene* scene;
    double k_scale;
    Field* field;
    Player* player;
    std::vector< std::vector<Field*> > layers;
    std::vector< std::vector<QGraphicsLineItem*> > connections;
    QPen connections_pen;
    int layer;

private slots:
    void GameFinished();

};
