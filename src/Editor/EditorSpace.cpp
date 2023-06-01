#include "EditorSpace.h"
#include <cmath>

EditorSpace::EditorSpace(int field_height_, int field_width_, QWidget* parent) :
        QGraphicsView(parent),
        scene(new QGraphicsScene(this)),
        k_scale(2),
        player(new Player) {

    scale(k_scale, k_scale);
    setFocus();
    setDragMode(DragMode::ScrollHandDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    int cells_count = field_height_ * field_width_ - 1;
    field = new EditorField(QString::number(field_height_) + "-" +
                            QString::number(field_width_) + "|0-0|F" +
                            QString("-F").repeated(cells_count) + "|", player);

    setScene(scene);
    scene->addItem(field);
    connect(field, SIGNAL(Clicked(QPoint)), this, SLOT(ObjectClick(QPoint)));

}

void EditorSpace::wheelEvent(QWheelEvent *event) {
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

void EditorSpace::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_P:
            emit StartGame(field->Code());
            break;
        case Qt::Key_Escape:
            emit ReturnToMainMenu();
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}

void EditorSpace::ObjectClick(QPoint cell) {
    if (current.isEmpty()) {
        return;
    }
    int x = cell.x();
    int y = cell.y();
    if (isupper(current[0].toLatin1())) {
        delete (*field)[x][y];
    }
    switch (current[0].toLatin1()) {
        case 'F':
            new Floor(field, x, y);
            break;
        case 'B':
            new FragileFloor(field, x, y);
            break;
        case 'A':
            new ArrowFloor(current.split(',')[1].toInt(), field, x, y);
            break;
        case 'W':
            new Wall(field, x, y);
            break;
        case 'V':
            new Void(field, x, y);
            break;
        case 'D':
            new Door(field, x, y);
            break;
        case 'E':
            new Finish(field, x, y);
            break;
        case 'k':
            field->Code();
            field->PutItem(new Key, x, y);
            break;
        case 'b':
            field->PutItem(new class Box, x, y);
            break;
        case 'p':
            field->PutPlayer(field->RemovePlayer(), x, y);
            break;
        default:
            new Void(field, x, y);
    }
}

void EditorSpace::ChooseCurrent(QString code) {
    current = code;
}
