#pragma once

#include <QWidget>
#include <QGraphicsItem>

class Animation : public QWidget {
    Q_OBJECT

public:
    Animation(QGraphicsItem* object_, double speed_, QWidget* parent = nullptr);
    virtual void Move() = 0;
    virtual bool Finished() = 0;

protected:
    QGraphicsItem* object;
    double speed;

};
