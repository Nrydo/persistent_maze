#pragma once

#include <QWidget>
#include <QGraphicsItem>
#include <QTimer>
#include <vector>
#include "Animation.h"
#include "AnimationMove.h"
#include "AnimationAppearance.h"

class AnimationController : public QWidget {
    Q_OBJECT

public:
    AnimationController(QWidget* parent = nullptr);
    void AddAnimation(Animation* animation);
    void AddAnimationMove(QGraphicsItem* object, const std::deque<QPointF>& way, double speed);
    void AddAnimationAppearance(QGraphicsItem* object, double speed);
    void Move();

private:
    QTimer* timer;
    std::vector<Animation*> objects;

signals:
    void Update();

private slots:
    void MakeMove();

};
