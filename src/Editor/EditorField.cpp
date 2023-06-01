#include "EditorField.h"
#include <QGraphicsSceneMouseEvent>

EditorField::EditorField(int height_, int width_) : Field(height_, width_) {
    frame->show();
}

EditorField::EditorField(const QString& field_code, Player* player_) : Field(field_code, player_) {
    frame->show();
}

void EditorField::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        auto point = (event->pos() + QPoint(16 * width, 16 * height)) / 32;
        if (point.x() >= 0 && point.y() >= 0 && point.x() < width && point.y() < height) {
            emit Clicked(QPoint(point.y(), point.x()));
        }
    }
}

void EditorField::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        auto point = (event->pos() + QPoint(16 * width, 16 * height)) / 32;
        if (point.x() >= 0 && point.y() >= 0 && point.x() < width && point.y() < height) {
            emit Clicked(QPoint(point.y(), point.x()));
        }
    }
}
