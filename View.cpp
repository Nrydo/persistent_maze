#include "View.h"
#include <cmath>

View::View(int height_, int width_) :
        player(new Player),
        scene(new QGraphicsScene(this)),
        k_scale(1),
        field(new Field(5, 5, "FFFFFFFFFFWWDWWFFFFFFFFFE")),
        layers(50),
        connections(50),
        connections_pen(QPen(Qt::black, 5)) {

    resize(width_, height_);
    setFocus();
    setDragMode(DragMode::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    interface = new ViewInterface(player, this);

    Key* key = new Key;

    layers[0].push_back(field);

    field->moveBy(0, -32 * (field->Width() + 1) / 2);
    field->PutItem(key, 1, 2);
    field->PutPlayer(player);
    connect(field, SIGNAL(FinishGame()), this, SLOT(GameFinished()));

//    scene->setSceneRect(0, 0, contentsRect().width(), contentsRect().height());
    setScene(scene);
    scene->addItem(field);

    layer = 0;
}

void View::wheelEvent(QWheelEvent *event) {
    auto angle = event->angleDelta();
    if (angle.x() || abs(angle.y()) != 120) {
        return;
    }
    double k = exp(angle.y() / 720.0);
    scale(k, k);
    k_scale *= k;
    if (k_scale < 1) {
        scale(1 / k_scale, 1 / k_scale);
        k_scale = 1;
    }
    if (k_scale > 4) {
        scale(4 / k_scale, 4 / k_scale);
        k_scale = 4;
    }
}

void View::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W:
        case Qt::Key_Up:
            field->MovePlayer(0);
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            field->MovePlayer(1);
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            field->MovePlayer(2);
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            field->MovePlayer(3);
            break;
        case Qt::Key_E:
            field->Interact();
            break;
        case Qt::Key_F:
            field->TimeTravel(field = field->Copy());
            layers[++layer].push_back(field);
            connections[layer].push_back(new QGraphicsLineItem);
            connections[layer].back()->setPen(connections_pen);
            connections[layer].back()->setZValue(-1);
            connect(field, SIGNAL(FinishGame()), this, SLOT(GameFinished()));
            field->moveBy(field->Width() * 32 + 32, 0);
            for (int i = 0, size = layers[layer].size(); i < size; i++) {
                layers[layer][i]->setY(0);
                layers[layer][i]->moveBy(0, (2 * i - size) * 32 * (field->Width() + 1) / 2);
                connections[layer][i]->setLine(
                        QLineF(layers[layer][i]->pos(), layers[layer][i]->GetNeighbors()[0]->pos()));
            }
            for (int i = 0; i < layers[layer + 1].size(); i++) {
                connections[layer + 1][i]->setLine(
                        QLineF(layers[layer + 1][i]->pos(), layers[layer + 1][i]->GetNeighbors()[0]->pos()));
            }
            scene->addItem(connections[layer].back());
            scene->addItem(field);
            break;
        case Qt::Key_Z:
            field->TimeTravel(field->GetNeighbors()[0]);
            layer--;
            field = field->GetNeighbors()[0];
            break;
        case Qt::Key_X:
            field->TimeTravel(field->GetNeighbors().back());
            layer++;
            field = field->GetNeighbors().back();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
    interface->update();
}

void View::GameFinished() {
    exit(0);
}
