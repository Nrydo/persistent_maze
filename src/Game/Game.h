#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QGraphicsTextItem>
#include <QFont>
#include <QLine>
#include <unordered_map>
#include "GameInterface.h"
#include "Animations/AnimationController.h"
#include "Field.h"

class Game : public QGraphicsView {
    Q_OBJECT

public:
    Game(int width_, int height_, QString field_code_, QWidget* parent = nullptr);
    void UpdateConnections(int layer_);
    AnimationController* GetAnimationController();
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    GameInterface* interface;
    AnimationController* animator;
    QGraphicsScene* scene;
    double k_scale;
    Field* field;
    Player* player;
    std::vector< std::vector<Field*> > fields;
    std::vector< std::vector<QGraphicsLineItem*> > connections;
    std::unordered_map<Field*, int> layers;
    int layer;
    QString field_code;
    int time;
    int travels;
    int moves;
    QTimer* timer;

signals:
    void RestartGame(const QString& code);
    void GameFinished(int time = -1, int travels = -1, int moves = -1);
    void ReturnToMainMenu();

private slots:
    void FinishGame();
    void FieldClick(Field* field_);
    void Update();
    void IncreaseTime();

};
