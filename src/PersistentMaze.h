#pragma once

#include <QMainWindow>
#include <QGraphicsView>
#include <QStateMachine>
#include <QStackedWidget>
#include "Game/Game.h"
#include "Menu/MainMenu.h"
#include "Menu/FinishMenu.h"
#include "Editor/Editor.h"

class PersistentMaze : public QMainWindow {
    Q_OBJECT

public:
    PersistentMaze(int width_ = -1, int height_ = -1);

private:
    QStackedWidget* stack;

private slots:
    void OpenMainMenu();
    void OpenFinishMenu(int time, int travels, int moves);
    void OpenEditor();
    void StartGame(int number);
    void StartGame(const QString& level_code);
    void Exit();

};
