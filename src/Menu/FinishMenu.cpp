#include "FinishMenu.h"
#include <QVBoxLayout>
#include <QKeyEvent>

FinishMenu::FinishMenu(int width_, int height_, QWidget *parent) :
        QWidget(parent) {

    resize(width_, height_);

    auto layout = new QGridLayout(this);

    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 3);
    layout->setColumnStretch(2, 1);
    layout->setRowStretch(0, 1);
    layout->setRowStretch(1, 3);
    layout->setRowStretch(2, 1);

    auto data = new QWidget(this);
    data->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    layout->addWidget(data, 1, 1);

    auto data_layout = new QVBoxLayout(data);
    auto head = new QLabel("Statistics", this);
    head->setFont(QFont("Areal", 50));
    data_layout->addWidget(head, 1, Qt::AlignCenter);
    auto table = new QGridLayout;
    data_layout->addLayout(table, 6);
    table->setColumnStretch(0, 1);
    table->setColumnStretch(1, 1);
    table->setRowStretch(0, 1);
    table->setRowStretch(1, 1);
    table->setRowStretch(2, 1);

    QFont font("Areal", 40);
    auto time_label = new QLabel("Time:", this);
    time_label->setFont(font);
    table->addWidget(time_label, 0, 0, Qt::AlignLeft);
    auto travels_label = new QLabel("Time Travels:", this);
    travels_label->setFont(font);
    table->addWidget(travels_label, 1, 0, Qt::AlignLeft);
    auto moves_label = new QLabel("Moves:", this);
    moves_label->setFont(font);
    table->addWidget(moves_label, 2, 0, Qt::AlignLeft);
    time = new QLabel("0", this);
    time->setFont(font);
    table->addWidget(time, 0, 1, Qt::AlignRight);
    travels = new QLabel("0", this);
    travels->setFont(font);
    table->addWidget(travels, 1, 1, Qt::AlignRight);
    moves = new QLabel("0", this);
    moves->setFont(font);
    table->addWidget(moves, 2, 1, Qt::AlignRight);

}

void FinishMenu::UpdateData(int time_, int travels_, int moves_) {
    time->setText(QString::number(time_ / 1000.0) + " s");
    travels->setText(QString::number(travels_));
    moves->setText(QString::number(moves_));
}

void FinishMenu::keyPressEvent(QKeyEvent* event) {
    emit OpenMainMenu();
}

void FinishMenu::mousePressEvent(QMouseEvent* event) {
    emit OpenMainMenu();
}
