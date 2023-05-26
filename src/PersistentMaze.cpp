#include "PersistentMaze.h"

PersistentMaze::PersistentMaze(int width, int height) :
        states(new QStateMachine(this)),
        menu(new QState(states)),
        game(new QState(states)),
        creator(new QState(states)) {

    resize(width, height);

    states->setInitialState(menu);

    current = new MainMenu(width, height, this);
    connect(current, SIGNAL(StartGame()), this, SLOT(StartGame()));
    connect(current, SIGNAL(Exit()), this, SLOT(Exit()));
}


void PersistentMaze::OpenMainMenu() {
    disconnect(current, SIGNAL(GameFinished()), this, SLOT(OpenMainMenu()));
    delete current;
    current = new MainMenu(width(), height(), this);
    current->show();
    connect(current, SIGNAL(StartGame()), this, SLOT(StartGame()));
    connect(current, SIGNAL(Exit()), this, SLOT(Exit()));
}

void PersistentMaze::StartGame() {
    disconnect(current, SIGNAL(StartGame()), this, SLOT(StartGame()));
    delete current;
    current = new Game(width(), height(), 5, 5, "F-F-F-W-F-F-F-F-B-F-W-D-W-W-W-F-F-F-W-E-F-F-A,0-D-F|K,1,4-B,3,1", this);
    current->show();
    connect(current, SIGNAL(GameFinished()), this, SLOT(OpenMainMenu()));
}

void PersistentMaze::Exit() {
    close();
}
