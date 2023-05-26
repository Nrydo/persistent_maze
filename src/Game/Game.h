#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QGraphicsTextItem>
#include <QFont>
#include <QLine>
#include <QQueue>
#include <unordered_map>
#include "ViewInterface.h"
#include "Animations/AnimationController.h"
#include "Field.h"

class Game : public QGraphicsView {
    Q_OBJECT

public:
    Game(int width_, int height_, int field_width_, int field_height_, QString field_str_, QWidget* parent = nullptr);
    void UpdateConnections(int layer_);
    void Restart();
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    ViewInterface* interface;
    AnimationController* animator;
    QGraphicsScene* scene;
    double k_scale;
    Field* field;
    Player* player;
    std::vector< std::vector<Field*> > fields;
    std::vector< std::vector<QGraphicsLineItem*> > connections;
    std::unordered_map<Field*, int> layers;
    int layer;
    int field_width;
    int field_height;
    QString field_str;

signals:
    void GameFinished();

private slots:
    void FinishGame();
    void FieldClick(Field* field_);
    void Update();

};
