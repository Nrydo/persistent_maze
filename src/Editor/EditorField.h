#pragma once

#include "../Game/Field.h"

class EditorField : public Field {
    Q_OBJECT

public:
    EditorField(int height_, int width_);
    EditorField(const QString& field_code, Player* player_ = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

signals:
    void Clicked(QPoint cell);

};
