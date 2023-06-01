#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QGraphicsTextItem>
#include <QFont>
#include <unordered_map>
#include "EditorLeftPanel.h"
#include "EditorRightPanel.h"
#include "EditorSpace.h"

class Editor : public QWidget {
    Q_OBJECT

public:
    Editor(int width_, int height_, QWidget* parent = nullptr);

private:
    EditorSpace* space;
    EditorLeftPanel* left_panel;
    EditorRightPanel* right_panel;

signals:
    void StartGame(const QString& code);
    void ReturnToMainMenu();

private slots:
    void ChooseCurrent(QString code);

};
