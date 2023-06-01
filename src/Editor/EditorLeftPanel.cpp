#include "EditorLeftPanel.h"

EditorLeftPanel::EditorLeftPanel(int width_, int height_, QWidget* parent) :
        QWidget(parent) {

    setFixedHeight(height_);

    auto layout = new QVBoxLayout(this);

    layout->addWidget(AddButton("floor"));
    layout->addWidget(AddButton("wall"));
    layout->addWidget(AddButton("door"));
    layout->addWidget(AddButton("eraser"));
    layout->addWidget(AddButton("fragile_floor"));
    layout->addWidget(AddButton("arrow_floor_0"));
    layout->addWidget(AddButton("arrow_floor_1"));
    layout->addWidget(AddButton("arrow_floor_2"));
    layout->addWidget(AddButton("arrow_floor_3"));
    layout->addWidget(AddButton("finish"));

    codes.push_back("F");
    codes.push_back("W");
    codes.push_back("D");
    codes.push_back("V");
    codes.push_back("B");
    codes.push_back("A,0");
    codes.push_back("A,1");
    codes.push_back("A,2");
    codes.push_back("A,3");
    codes.push_back("E");

}

QPushButton* EditorLeftPanel::AddButton(QString file_name) {
    buttons.push_back(new QPushButton(this));
    buttons.back()->setFixedSize(96, 96);
    buttons.back()->setStyleSheet("QPushButton {border-image: url(:resources/textures/" +
                                    file_name +".png) 0 0 0 0 stretch stretch;}");
    connect(buttons.back(), SIGNAL(clicked()), this, SLOT(GetCurrent()));
    return buttons.back();
}

void EditorLeftPanel::GetCurrent() {
    emit ChooseCurrent(codes[std::find(buttons.begin(), buttons.end(), sender()) - buttons.begin()]);
}
