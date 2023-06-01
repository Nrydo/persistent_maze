#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QVector>

class EditorLeftPanel : public QWidget {
    Q_OBJECT

public:
    EditorLeftPanel(int width_, int height_, QWidget* parent);

private:
    QPushButton* AddButton(QString file_name);
    QVector<QPushButton*> buttons;
    QVector<QString> codes;

signals:
    void ChooseCurrent(QString code);

private slots:
    void GetCurrent();

};
