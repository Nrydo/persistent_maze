#pragma once

#include <QGraphicsItem>
#include <cmath>
#include <deque>
#include "Animation.h"

class AnimationMove : public Animation {
    Q_OBJECT

public:
    AnimationMove(QGraphicsItem* object_, const std::deque<QPointF>& way_, double speed_, QWidget* parent = nullptr);
    void Move() override;
    bool Finished() override;

private:
    std::deque<QPointF> way;

};
