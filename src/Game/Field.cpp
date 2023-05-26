#include "Field.h"
#include <QDebug>

Field::Field(int height_, int width_) : height(height_), width(width_) {
    neighbors.push_back(nullptr);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            new Floor(this, i, j);
        }
    }
}

Field::Field(int height_, int width_, const QString& field_code) :
        height(height_), width(width_), field(height, std::vector<Object*>(width)) {

    neighbors.push_back(nullptr);
    auto objects_and_items = field_code.split('|');
    auto objects = objects_and_items[0].split('-');
    auto items = objects_and_items[1].split('-');
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto& object = objects[i * width + j];
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
                    connect(field[i][j], SIGNAL(GameFinished()), this, SLOT(FinishGame()));
                    break;
                default:
                    new Void(this, i, j);
            }
        }
    }
    for (const auto& item : items) {
        auto item_data = item.split(',');
        int x = item_data[1].toInt();
        int y = item_data[2].toInt();
        switch (item_data[0][0].toLatin1()) {
            case 'K':
                PutItem(new Key, x, y);
                break;
            case 'B':
                PutItem(new Box, x, y);
            default:
                break;
        }
    }
}

Field::Field(const Field& other) :
        height(other.height),
        width(other.width),
        field(height, std::vector<Object*>(width)) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            other[i][j]->Copy(this, i, j);
            if (field[i][j]->metaObject()->indexOfSignal("GameFinished()") != -1) {
                connect(field[i][j], SIGNAL(GameFinished()), this, SLOT(FinishGame()));          }
        }
    }
    setPos(other.pos());
}

Field* Field::Copy() {
    neighbors.push_back(new Field(*this));
    neighbors.back()->neighbors.push_back(this);
    return neighbors.back();
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
}

void Field::MovePlayer(int direction) {
    player->SetDirection(direction);
    int pnx = player_x + (direction - 1) % 2;
    int pny = player_y + (2 - direction) % 2;
    if (pnx < 0 || pny < 0 || pnx >= height || pny >= height || field[pnx][pny]->GetColliding()) {
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
    dynamic_cast<Floor*>(field[x][y])->SetItem(item);
    item->setPos(field[x][y]->pos());
}

void Field::RemoveItem(int x, int y) {
    dynamic_cast<Floor*>(field[x][y])->RemoveItem();
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

void Field::Interact() {
    int pnx = player_x + (player->GetDirection() - 1) % 2;
    int pny = player_y + (2 - player->GetDirection()) % 2;
    if (pnx < 0 || pny < 0 || pnx >= height || pny >= height) {
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

void Field::FinishGame() {
    emit GameFinished();
}
