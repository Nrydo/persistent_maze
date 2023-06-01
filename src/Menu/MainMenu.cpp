#include "MainMenu.h"
#include <QLabel>
#include <QKeyEvent>

MainMenu::MainMenu(int width_, int height_, QWidget *parent) :
        QWidget(parent),
        levels_button(new QPushButton("Levels", this)),
        editor_button(new QPushButton("Editor", this)),
        exit_button(new QPushButton("Exit", this)),
        level_selection(new LevelSelectionMenu(3, 3, this)) {

    resize(width_, height_);

    auto layout = new QGridLayout(this);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    layout->setColumnStretch(2, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 2);

    auto name = new QLabel("Persistent Maze", this);
    layout->addWidget(name, 0, 1, Qt::AlignCenter);
    name->setFont(QFont("Areal",  40, QFont::Bold));

    auto buttons_layout = new QGridLayout();

    buttons_layout->setRowStretch(0, 1);
    buttons_layout->setRowStretch(1, 1);
    buttons_layout->setRowStretch(2, 1);

    buttons_layout->addWidget(levels_button, 0, 0);
    buttons_layout->addWidget(editor_button, 1, 0);
    buttons_layout->addWidget(exit_button, 2, 0);

    levels_button->setFont(QFont("Areal",  30, QFont::Bold));
    levels_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(levels_button, SIGNAL(pressed()), this, SLOT(LevelPressed()));

    editor_button->setFont(QFont("Areal",  30, QFont::Bold));
    editor_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(editor_button, SIGNAL(pressed()), this, SLOT(EditorPressed()));

    exit_button->setFont(QFont("Areal",  30, QFont::Bold));
    exit_button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(exit_button, SIGNAL(pressed()), this, SLOT(ExitPressed()));

    layout->addLayout(buttons_layout, 1, 1);

    level_selection->resize(width(), height());
    level_selection->hide();

    connect(level_selection, SIGNAL(LevelSelected(int)), this, SLOT(StartLevel(int)));

}

void MainMenu::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape:
            ExitPressed();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void MainMenu::LevelPressed() {
    level_selection->show();
    level_selection->setFocus();
}

void MainMenu::ExitPressed() {
    emit Exit();
}

void MainMenu::StartLevel(int number) {
    emit StartGame(number);
}

void MainMenu::EditorPressed() {
    emit OpenEditor();
}
