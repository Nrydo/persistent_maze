#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include <QPushButton>

class LevelSelectionMenu : public QWidget {
    Q_OBJECT

public:
    LevelSelectionMenu(int row_count, int column_count, QWidget* parent = nullptr);
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    QGridLayout* main_layout;
    QTableWidget* levels_panel;
    QVector<QPushButton*> levels;

signals:
    void LevelSelected(int number);

public slots:
    void LevelSelection();

};
