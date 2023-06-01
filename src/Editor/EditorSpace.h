#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QGraphicsTextItem>
#include <QFont>
#include <unordered_map>
#include "EditorField.h"

class EditorSpace : public QGraphicsView {
    Q_OBJECT

public:
    EditorSpace(int field_height_, int field_width_, QWidget* parent = nullptr);
    void wheelEvent(QWheelEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void ChooseCurrent(QString code);

private:
    QGraphicsScene* scene;
    double k_scale;
    EditorField* field;
    QString current;
    Player* player;

signals:
    void StartGame(const QString& code);
    void ReturnToMainMenu();

private slots:
    void ObjectClick(QPoint cell);

};
