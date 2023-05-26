#include "Animation.h"

Animation::Animation(QGraphicsItem* object_, double speed_, QWidget* parent) :
        QWidget(parent), object(object_), speed(speed_) {}
