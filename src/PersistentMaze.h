#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QStateMachine>
#include <QStackedWidget>
#include "Game/Game.h"
#include "Menu/MainMenu.h"

class PersistentMaze : public QMainWindow {
    Q_OBJECT

public:
    PersistentMaze(int width, int height);

private:
    QStateMachine* states;
    QState* menu;
    QState* game;
    QState* creator;
    QWidget* current;
    QStackedWidget* widgets;

private slots:
    void OpenMainMenu();
    void StartGame();
    void Exit();

};
