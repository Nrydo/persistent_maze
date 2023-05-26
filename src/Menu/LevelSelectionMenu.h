#pragma once

#include <QWidget>
#include <QGridLayout>

class LevelSelectionMenu : public QWidget {
    Q_OBJECT

public:
    LevelSelectionMenu(QWidget* parent = nullptr);

private:
    QGridLayout* main_layout;
    QWidget* levels_panel;
    QGridLayout* levels_layout;

};
