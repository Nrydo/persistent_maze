#include "AnimationAppearance.h"

AnimationAppearance::AnimationAppearance(QGraphicsItem* object_, double speed_, QWidget* parent) :
        Animation(object_, speed_, parent) {
    object_->setOpacity(0);
}

void AnimationAppearance::Move() {
    object->setOpacity(object->opacity() + speed);
}

bool AnimationAppearance::Finished() {
    return object->opacity() == 1;
}
