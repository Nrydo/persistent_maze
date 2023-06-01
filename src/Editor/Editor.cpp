#include "Editor.h"
#include <cmath>

Editor::Editor(int width_, int height_, int field_height_, int field_width_, QWidget* parent) :
        QWidget(parent),
        space(new EditorSpace(field_height_, field_width_, parent)),
        left_panel(new EditorLeftPanel(width_, height_, this)),
        right_panel(new EditorRightPanel(width_, height_, this)) {

    resize(width_, height_);

    space->setFocus();

    connect(space, SIGNAL(ReturnToMainMenu()), this, SIGNAL(ReturnToMainMenu()));
    connect(space, SIGNAL(StartGame(QString)), this, SIGNAL(StartGame(QString)));
    connect(left_panel, SIGNAL(ChooseCurrent(QString)), this, SLOT(ChooseCurrent(QString)));
    connect(right_panel, SIGNAL(ChooseCurrent(QString)), this, SLOT(ChooseCurrent(QString)));

    auto layout = new QHBoxLayout(this);
    layout->addWidget(left_panel, 1, Qt::AlignLeft | Qt::AlignVCenter);
    layout->addWidget(space, 10);
    space->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    layout->addWidget(right_panel, 1, Qt::AlignRight | Qt::AlignVCenter);

}

void Editor::ChooseCurrent(QString code) {
    space->ChooseCurrent(code);
}
