#include "Field.h"

Field::Field(int height_, int width_, const std::string& field_code) :
        height(height_),
        width(width_),
        field(height, std::vector<Object*>(width)) {
    if (field_code.empty()) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                field[i][j] = new Floor;
                addToGroup(field[i][j]);
                field[i][j]->setPos((2 * j - width) * 32 / 2, (2 * i - height) * 32 / 2);
            }
        }
        return;
    }
    if (height_ * width_ != field_code.size()) {
        throw "Incorrect data for Field constructor.\n";
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            switch (field_code[i * width + j]) {
                case 'F':
                    field[i][j] = new Floor;
                    break;
                case 'W':
                    field[i][j] = new Wall;
                    break;
                case 'D':
                    field[i][j] = new Door;
                    break;
                case 'E':
                    field[i][j] = new Finish;
                    connect(field[i][j], SIGNAL(FinishGame()), this, SLOT(GameFinished()));
                    break;
                default:
                    field[i][j] = new Wall;
            }
            addToGroup(field[i][j]);
            field[i][j]->setPos((2 * j - width) * 32 / 2, (2 * i - height) * 32 / 2);
        }
    }
}

Field::Field(const Field& other) :
        height(other.height),
        width(other.width),
        field(height, std::vector<Object*>(width)) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            field[i][j] = other[i][j]->Copy();
            addToGroup(field[i][j]);
            field[i][j]->setPos((2 * j - width) * 32 / 2, (2 * i - height) * 32 / 2);
            if (field[i][j]->metaObject()->indexOfSignal("FinishGame()") != -1) {
                connect(field[i][j], SIGNAL(FinishGame()), this, SLOT(GameFinished()));
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
}

void Field::MovePlayer(int direction) {
    player->SetDirection(direction);
    int pnx = player_x + (direction - 1) % 2;
    int pny = player_y + (2 - direction) % 2;
    if (pnx < 0 || pny < 0 || pnx >= height || pny >= height || field[pnx][pny]->GetColliding()) {
        return;
    }
    player->setPos(field[player_x = pnx][player_y = pny]->pos());
    field[pnx][pny]->Press(player);
}

Player* Field::RemovePlayer() {
    auto player_ = player;
    removeFromGroup(player);
    player = nullptr;
    return player_;
}

void Field::TimeTravel(Field *other) {
    other->PutPlayer(RemovePlayer(), player_x, player_y);
}

void Field::PutItem(Item* item, int x, int y) {
    dynamic_cast<Floor*>(field[x][y])->SetItem(item);
    item->setPos(field[x][y]->pos());
}

void Field::RemoveItem(int x, int y) {
    dynamic_cast<Floor*>(field[x][y])->RemoveItem();
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

const std::vector<Object*>& Field::operator[](int x) const {
    return field[x];
}

void Field::GameFinished() {
    emit FinishGame();
}
