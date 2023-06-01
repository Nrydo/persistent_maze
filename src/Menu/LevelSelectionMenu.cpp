#include "LevelSelectionMenu.h"
#include <QHeaderView>
#include <QKeyEvent>

LevelSelectionMenu::LevelSelectionMenu(int row_count, int column_count, QWidget* parent) :
        QWidget(parent),
        main_layout(new QGridLayout(this)),
        levels_panel(new QTableWidget(this)) {

    main_layout->setRowStretch(0, 1);
    main_layout->setRowStretch(1, 2);
    main_layout->setRowStretch(2, 1);

    main_layout->setColumnStretch(0, 1);
    main_layout->setColumnStretch(1, 2);
    main_layout->setColumnStretch(2, 1);

    main_layout->addWidget(levels_panel, 1, 1);

    levels_panel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    levels_panel->verticalHeader()->setVisible(false);
    levels_panel->horizontalHeader()->setVisible(false);
    levels_panel->resizeColumnsToContents();
    levels_panel->resizeRowsToContents();
    levels_panel->setRowCount(row_count);
    levels_panel->setColumnCount(column_count);

    for (int i = 0; i < levels_panel->rowCount(); i++) {
        levels_panel->verticalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        levels_panel->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
        for (int j = 0; j < levels_panel->columnCount(); j++) {
            levels.push_back(new QPushButton(QString::number(i * 3 + j + 1), levels_panel));
            levels.back()->setFont(QFont("Areal", 40, QFont::Bold));
            levels_panel->setCellWidget(i, j, levels.back());
            connect(levels.back(), SIGNAL(clicked()), this, SLOT(LevelSelection()));
        }
    }

}

void LevelSelectionMenu::LevelSelection() {
    auto button = qobject_cast<QPushButton*>(sender());
    if (button) {
        emit LevelSelected(levels.indexOf(button) + 1);
    }
}

void LevelSelectionMenu::mousePressEvent(QMouseEvent *event) {
    hide();
    QWidget::mousePressEvent(event);
}

void LevelSelectionMenu::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape:
            hide();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}
