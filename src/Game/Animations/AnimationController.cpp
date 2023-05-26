#include "AnimationController.h"

AnimationController::AnimationController(QWidget* parent) : QWidget(parent), timer(new QTimer(this)) {
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(MakeMove()));
    timer->start();
}

void AnimationController::AddAnimation(Animation* animation) {
    objects.push_back(animation);
}

void AnimationController::AddAnimationMove(QGraphicsItem *object, const std::deque<QPointF>& way, double speed) {
    objects.push_back(new AnimationMove(object, way, speed, this));
}

void AnimationController::AddAnimationAppearance(QGraphicsItem *object, double speed) {
    objects.push_back(new AnimationAppearance(object, speed, this));
}

void AnimationController::Move() {
    std::vector<Animation*> for_delete;
    for (auto object : objects) {
        object->Move();
        if (object->Finished()) {
            for_delete.push_back(object);
        }
    }
    for (auto object : for_delete) {
        objects.erase(std::find(objects.begin(), objects.end(), object));
    }
}

void AnimationController::MakeMove() {
    Move();
    emit Update();
}
