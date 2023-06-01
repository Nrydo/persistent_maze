#pragma once

#include <QGraphicsView>
#include <QPushButton>
#include <QGridLayout>
#include <vector>
#include "LevelSelectionMenu.h"

class MainMenu : public QWidget {
    Q_OBJECT

public:
    MainMenu(int width_, int height_, QWidget* parent);

private:
    QPushButton* levels_button;
    QPushButton* editor_button;
    QPushButton* exit_button;
    LevelSelectionMenu* level_selection;
    void keyPressEvent(QKeyEvent* event) override;

signals:
    void StartGame(int number);
    void OpenEditor();
    void Exit();

private slots:
    void LevelPressed();
    void ExitPressed();
    void StartLevel(int number);
    void EditorPressed();

};
