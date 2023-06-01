#pragma once

#include <QGraphicsItemGroup>
#include <vector>
#include <QPen>
#include "Animations/AnimationController.h"
#include "Objects/Wall.h"
#include "Objects/Door.h"
#include "Objects/Floor.h"
#include "Objects/FragileFloor.h"
#include "Objects/ArrowFloor.h"
#include "Objects/Finish.h"
#include "Objects/Void.h"
#include "Items/Key.h"
#include "Items/Box.h"

class Field : public QObject, public QGraphicsItemGroup {
    Q_OBJECT

public:
    Field(int height_, int width_);
    Field(const QString& field_code, Player* player_ = nullptr);
    Field(const Field& other);
    Field* Copy();
    QString Code();
    const std::vector<Field*>& GetNeighbors();
    int Height() const;
    int Width() const;
    void PutPlayer(Player* player_, int x = 0, int y = 0);
    void MovePlayer(int direction);
    Player* RemovePlayer();
    bool TimeTravel(Field* other);
    void PutItem(Item* item, int x, int y);
    void RemoveItem(int x, int y);
    void PutObject(Object* object, int x, int y);
    void RemoveObject(int x, int y);
    AnimationController* GetAnimationController();
    void Interact();
    std::vector<Object*>& operator[](int x);
    const std::vector<Object*>& operator[](int x) const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

protected:
    void ConfigureFrame();

    int height;
    int width;
    QGraphicsItemGroup* frame;
    std::vector< std::vector<Object*> > field;
    std::vector<Field*> neighbors;
    Player* player;
    int player_x;
    int player_y;

signals:
    void GameFinished();
    void Clicked(Field* field_);

};
