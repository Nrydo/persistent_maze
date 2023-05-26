#include "LevelSelectionMenu.h"


LevelSelectionMenu::LevelSelectionMenu(QWidget* parent) :
        QWidget(parent),
        main_layout(new QGridLayout(this)),
        levels_panel(new QWidget(this)),
        levels_layout(new QGridLayout(levels_panel)) {

    main_layout->setColumnStretch(0, 1);
    main_layout->setColumnStretch(1, 2);
    main_layout->setColumnStretch(2, 1);

    main_layout->setRowStretch(0, 1);
    main_layout->setRowStretch(1, 2);
    main_layout->setRowStretch(2, 1);

    main_layout->addWidget(levels_panel, 1, 1);
    levels_panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    for (int i = 0; i < 3; i++) {
        levels_layout->setColumnStretch(i, 1);
        levels_layout->setRowStretch(i, 1);
    }

}
