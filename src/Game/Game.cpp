#include "Game.h"
#include <cmath>

Game::Game(int width_, int height_, QString field_code_, QWidget* parent) :
        QGraphicsView(parent),
        interface(new GameInterface(this)),
        animator(new AnimationController(this)),
        player(new Player),
        scene(new QGraphicsScene(this)),
        k_scale(2),
        field_code(field_code_),
        fields(50),
        connections(50),
        layer(0),
        time(0),
        travels(0),
        moves(0),
        timer(new QTimer(this)){

    resize(width_, height_);
    scale(k_scale, k_scale);
    setFocus();
    setDragMode(DragMode::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(player, SIGNAL(UpdateInventory(std::vector<Item*>)), interface, SLOT(UpdateInventory(std::vector<Item*>)));
    connect(animator, SIGNAL(Update()), this, SLOT(Update()));

    field = new Field(field_code, player);

    fields[0].push_back(field);

    connect(field, SIGNAL(GameFinished()), this, SLOT(FinishGame()));
    connect(field, SIGNAL(Clicked(Field*)), this, SLOT(FieldClick(Field*)));

    setScene(scene);
    scene->addItem(field);

    layers[field] = 0;

    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(IncreaseTime()));
    timer->start();

}

void Game::UpdateConnections(int layer_) {
    for (int i = 0; i < fields[layer_].size(); i++) {
        connections[layer_][i]->setLine(QLineF(fields[layer_][i]->pos(), fields[layer_][i]->GetNeighbors()[0]->pos()));
    }
}

AnimationController* Game::GetAnimationController() {
    return animator;
}

void Game::wheelEvent(QWheelEvent *event) {
    auto angle = event->angleDelta();
    if (angle.x() || abs(angle.y()) != 120) {
        QGraphicsView::wheelEvent(event);
        return;
    }
    double k = exp(angle.y() / 720.0);
    scale(k, k);
    k_scale *= k;
    double min_scale = 0.5, max_scale = 4;
    if (k_scale < min_scale) {
        scale(min_scale / k_scale, min_scale / k_scale);
        k_scale = min_scale;
    }
    if (k_scale > max_scale) {
        scale(max_scale / k_scale, max_scale / k_scale);
        k_scale = max_scale;
    }
}

void Game::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            field->MovePlayer(0);
            moves++;
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            field->MovePlayer(1);
            moves++;
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            field->MovePlayer(2);
            moves++;
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            field->MovePlayer(3);
            moves++;
            break;
        case Qt::Key_E:
            field->Interact();
            moves++;
            break;
        case Qt::Key_R:
            emit RestartGame(field_code);
            break;
        case Qt::Key_F:
            field->TimeTravel(field = field->Copy());
            travels++;
            layers[field] = ++layer;
            connect(field, SIGNAL(GameFinished()), this, SLOT(FinishGame()));
            connect(field, SIGNAL(Clicked(Field*)), this, SLOT(FieldClick(Field*)));
            connections[layer].push_back(new QGraphicsLineItem);
            connections[layer].back()->setPen(QPen(Qt::black, 5));
            connections[layer].back()->setZValue(-1);
            {
                int it = fields[layer].size();
                for (int i = fields[layer - 1].size() - 1; field->GetNeighbors()[0] != fields[layer - 1][i]; i--) {
                    it -= fields[layer - 1][i]->GetNeighbors().size() - 1;
                }
                fields[layer].insert(fields[layer].begin() + it, field);
                int layer_x = layer * 32 * (field->Width() + 1);
                int layer_y = 32 * (field->Height() + 1) / 2;
                int size = fields[layer].size();
//                animator->AddAnimationMove(field,
//                                           {QPointF(field->x(), (2 * it - size) * layer_y),
//                                            QPointF(layer_x, (2 * it - size) * layer_y)}, 5);
                animator->AddMoveAnimation(field, {QPointF(layer_x, (2 * it - size + 1) * layer_y)}, 5);
                for (int i = 0; i < size; i++) {
                    if (fields[layer][i] == field) {
                        continue;
                    }
                    animator->AddMoveAnimation(fields[layer][i], {QPointF(layer_x, (2 * i - size + 1) * layer_y)}, 5);
                }
            }
            UpdateConnections(layer);
            UpdateConnections(layer + 1);
            scene->addItem(connections[layer].back());
            scene->addItem(field);
            break;
        case Qt::Key_Escape:
            timer->stop();
            ReturnToMainMenu();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}

void Game::FinishGame() {
    timer->stop();
    emit GameFinished(time, travels, moves);
}

void Game::FieldClick(Field* field_) {
    const auto& neighbors = field->GetNeighbors();
    if (std::find(neighbors.begin(), neighbors.end(), field_) != neighbors.end() && field->TimeTravel(field_)) {
        travels++;
        field = field_;
        layer = layers[field];
    }
//    if (field->TimeTravel(field_)) {
//        field = field_;
//        layer = layers[field];
//    }
}

void Game::Update() {
    for (int i = 1; i < connections.size(); i++) {
        UpdateConnections(i);
    }
}

void Game::IncreaseTime() {
    time += 10;
}
