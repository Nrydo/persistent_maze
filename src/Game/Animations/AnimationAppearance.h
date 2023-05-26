#pragma once

#include <QGraphicsItem>
#include <cmath>
#include <queue>
#include "Animation.h"

class AnimationAppearance : public Animation {
    Q_OBJECT

public:
    AnimationAppearance(QGraphicsItem* object_, double speed_, QWidget* parent = nullptr);
    void Move() override;
    bool Finished() override;

};
