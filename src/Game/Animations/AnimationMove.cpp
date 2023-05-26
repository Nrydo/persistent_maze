#include "AnimationMove.h"

AnimationMove::AnimationMove(QGraphicsItem* object_, const std::deque<QPointF>& way_, double speed_, QWidget* parent) :
        Animation(object_, speed_, parent), way(way_) {}

void AnimationMove::Move() {
    if (way.empty()) {
        return;
    }
    QPointF vec = way.front() - object->pos();
    double len = hypot(vec.x(), vec.y());
    if (len < speed) {
        object->setPos(way.front());
        way.pop_front();
        return;
    }
    vec *= speed / len;
    object->moveBy(vec.x(), vec.y());
}

bool AnimationMove::Finished() {
    return way.empty();
}
