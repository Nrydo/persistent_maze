#include "Field.h"
#include "Game.h"

Field::Field(int height_, int width_) :
        height(height_),
        width(width_),
        field(height, std::vector<Object*>(width)) {

    ConfigureFrame();
    neighbors.push_back(nullptr);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            new Floor(this, i, j);
        }
    }

}

Field::Field(const QString& field_code, Player* player_) {

    neighbors.push_back(nullptr);

    auto objects_and_items = field_code.split('|');
    auto sizes = objects_and_items[0].split('-');
    auto player_pos = objects_and_items[1].split('-');
    auto objects = objects_and_items[2].split('-');
    auto items = objects_and_items[3].split('-');

    height = sizes[0].toInt();
    width = sizes[1].toInt();
    field.resize(height, std::vector<Object*>(width));

    ConfigureFrame();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto& object = objects[i * width + j];
            if (object.isEmpty()) {
                continue;
            }
            switch (object[0].toLatin1()) {
                case 'F':
                    new Floor(this, i, j);
                    break;
                case 'B':
                    new FragileFloor(this, i, j);
                    break;
                case 'A':
                    new ArrowFloor(object.split(',')[1].toInt(), this, i, j);
                    break;
                case 'W':
                    new Wall(this, i, j);
                    break;
                case 'V':
                    new Void(this, i, j);
                    break;
                case 'D':
                    new Door(this, i, j);
                    break;
                case 'E':
                    new Finish(this, i, j);
                    connect(field[i][j], SIGNAL(GameFinished()), this, SIGNAL(GameFinished()));
                    break;
                default:
                    new Void(this, i, j);
            }
        }
    }

    for (const auto& item : items) {
        if (item.isEmpty()) {
            continue;
        }
        auto item_data = item.split(',');
        int x = item_data[1].toInt();
        int y = item_data[2].toInt();
        switch (item_data[0][0].toLatin1()) {
            case 'K':
                PutItem(new Key, x, y);
                break;
            case 'B':
                PutItem(new Box, x, y);
                break;
            default:
                break;
        }

    }

    if (!player_pos[0].isEmpty()) {
        PutPlayer(player_, player_pos[0].toInt(), player_pos[1].toInt());
    }

}

Field::Field(const Field& other) :
        height(other.height),
        width(other.width),
        field(height, std::vector<Object*>(width)) {

    ConfigureFrame();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            other[i][j]->Copy(this, i, j);
            if (field[i][j]->metaObject()->indexOfSignal("GameFinished()") != -1) {
                connect(field[i][j], SIGNAL(GameFinished()), this, SIGNAL(GameFinished()));
            }
        }
    }
    setPos(other.pos());

}

Field* Field::Copy() {
    neighbors.push_back(new Field(*this));
    neighbors.back()->neighbors.push_back(this);
    return neighbors.back();
}

QString Field::Code() {
    QString code = QString::number(height) + "-" + QString::number(width) + "|";
    if (player) {
        code += QString::number(player_x) + "-" + QString::number(player_y);
    }
    code += "|";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (code.back() != "|") {
                code += "-";
            }
            code += field[i][j]->Code();
        }
    }
    code += "|";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto type = field[i][j]->Code()[0];
            if (type == 'F' || type == 'A' || type == 'B') {
                auto item = dynamic_cast<Floor*>(field[i][j])->GetItem();
                if (item) {
                    if (code.back() != "|") {
                        code += "-";
                    }
                    code += item->Code() + "," + QString::number(i) + "," + QString::number(j);
                }
            }
        }
    }
    return code;
}

const std::vector<Field*>& Field::GetNeighbors() {
    return neighbors;
}

int Field::Height() const {
    return height;
}

int Field::Width() const {
    return width;
}

void Field::PutPlayer(Player *player_, int x, int y) {
    addToGroup(player = player_);
    player->setPos(field[player_x = x][player_y = y]->pos());
    field[x][y]->Press(player);
    player->SetField(this);
    frame->show();
}

void Field::MovePlayer(int direction) {
    player->SetDirection(direction);
    int pnx = player_x + (direction - 1) % 2;
    int pny = player_y + (2 - direction) % 2;
    if (pnx < 0 || pny < 0 || pnx >= height || pny >= width || field[pnx][pny]->GetColliding()) {
        return;
    }
    field[player_x][player_y]->Release(player);
    player->setPos(field[player_x = pnx][player_y = pny]->pos());
    field[pnx][pny]->Press(player);
}

Player* Field::RemovePlayer() {
    field[player_x][player_y]->Release(player);
    player->SetField(nullptr);
    auto player_ = player;
    removeFromGroup(player);
    player = nullptr;
    frame->hide();
    return player_;
}

bool Field::TimeTravel(Field *other) {
    if (!(*other)[player_x][player_y]->GetColliding()) {
        other->PutPlayer(RemovePlayer(), player_x, player_y);
        return true;
    }
    return false;
}

void Field::PutItem(Item* item, int x, int y) {
    auto type = field[x][y]->Code()[0];
    if (type == 'F' || type == 'A' || type == 'B') {
        dynamic_cast<Floor*>(field[x][y])->SetItem(item);
        item->setPos(field[x][y]->pos());
    }
}

void Field::RemoveItem(int x, int y) {
    auto type = field[x][y]->Code()[0];
    if (type == 'F' || type == 'A' || type == 'B') {
        dynamic_cast<Floor*>(field[x][y])->RemoveItem();
    }
}

void Field::PutObject(Object *object, int x, int y) {
    field[x][y] = object;
    addToGroup(field[x][y]);
    field[x][y]->setPos((2 * y - width) * 32 / 2, (2 * x - height) * 32 / 2);
}

void Field::RemoveObject(int x, int y) {
    removeFromGroup(field[x][y]);
    field[x][y] = nullptr;
}

AnimationController* Field::GetAnimationController() {
    return dynamic_cast<Game*>(scene()->views()[0])->GetAnimationController();
}

void Field::Interact() {
    int pnx = player_x + (player->GetDirection() - 1) % 2;
    int pny = player_y + (2 - player->GetDirection()) % 2;
    if (pnx < 0 || pny < 0 || pnx >= height || pny >= width) {
        return;
    }
    field[pnx][pny]->Interact(player);
}

std::vector<Object*>& Field::operator[](int x) {
    return field[x];
}

void Field::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsItem::mousePressEvent(event);
    emit Clicked(this);
}

const std::vector<Object*>& Field::operator[](int x) const {
    return field[x];
}

void Field::ConfigureFrame() {
    auto inner = new QGraphicsRectItem(-width * 32 / 2 - 2, -height * 32 / 2 - 2, width * 32 + 4, height * 32 + 4);
    inner->setPen(QPen(Qt::white, 3));
    auto outer = new QGraphicsRectItem(-width * 32 / 2 - 4, -height * 32 / 2 - 4, width * 32 + 8, height * 32 + 8);
    outer->setPen(QPen(Qt::black, 2));
    frame = new QGraphicsItemGroup;
    frame->addToGroup(inner);
    frame->addToGroup(outer);
    frame->setZValue(1);
    frame->hide();
    addToGroup(frame);
}
