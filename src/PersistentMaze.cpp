#include "PersistentMaze.h"
#include <QTextStream>
#include <QDebug>

PersistentMaze::PersistentMaze(int width_, int height_) :
        stack(new QStackedWidget(this)) {

    if (width_ > 0) {
        resize(width_, height_);
    }
    else {
        showFullScreen();
    }

    stack->resize(width(), height());
    stack->addWidget(new MainMenu(width(), height(), stack));
    connect(stack->widget(0), SIGNAL(StartGame(int)), this, SLOT(StartGame(int)));
    connect(stack->widget(0), SIGNAL(Exit()), this, SLOT(Exit()));
    connect(stack->widget(0), SIGNAL(OpenEditor()), this, SLOT(OpenEditor()));
    stack->addWidget(new QWidget);
    stack->addWidget(new FinishMenu(width(), height(), stack));
    connect(stack->widget(2), SIGNAL(OpenMainMenu()), this, SLOT(OpenMainMenu()));
    stack->addWidget(new QWidget);

}

void PersistentMaze::OpenMainMenu() {
    stack->setCurrentIndex(0);
}

void PersistentMaze::OpenFinishMenu(int time, int travels, int moves) {
    dynamic_cast<FinishMenu*>(stack->widget(2))->UpdateData(time, travels, moves);
    stack->setCurrentIndex(2);
}

void PersistentMaze::OpenEditor() {
    auto last_editor = stack->widget(3);
    stack->removeWidget(last_editor);
    delete last_editor;
    stack->insertWidget(3, new Editor(width(), height(), stack));
    stack->setCurrentIndex(3);
    connect(stack->widget(3), SIGNAL(StartGame(QString)), this, SLOT(StartGame(QString)));
    connect(stack->widget(3), SIGNAL(ReturnToMainMenu()), this, SLOT(OpenMainMenu()));
}

void PersistentMaze::StartGame(int number) {
    QFile file(":resources/levels/game_levels/level" + QString::number(number) + ".txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        QString line = in.readLine();
        file.close();
        StartGame(line);
    }
}

void PersistentMaze::StartGame(const QString& level_code) {
    auto new_game = new Game(width(), height(), level_code, this);
    auto last_game = stack->widget(1);
    stack->removeWidget(last_game);
    delete last_game;
    stack->insertWidget(1, new_game);
    stack->setCurrentIndex(1);
    connect(stack->widget(1), SIGNAL(GameFinished(int,int,int)), this, SLOT(OpenFinishMenu(int,int,int)));
    connect(stack->widget(1), SIGNAL(ReturnToMainMenu()), this, SLOT(OpenMainMenu()));
    connect(stack->widget(1), SIGNAL(RestartGame(QString)), this, SLOT(StartGame(QString)));
}

void PersistentMaze::Exit() {
    close();
}
