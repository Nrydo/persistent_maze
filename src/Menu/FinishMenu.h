#pragma once

#include <QGraphicsView>
#include <QLabel>
#include <QGridLayout>
#include "LevelSelectionMenu.h"

class FinishMenu : public QWidget {
Q_OBJECT

public:
    FinishMenu(int width_, int height_, QWidget* parent);
    void UpdateData(int time_, int travels_, int moves_);
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

private:
    QLabel* time;
    QLabel* travels;
    QLabel* moves;

signals:
    void OpenMainMenu();

};
