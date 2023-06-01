#include "EditorRightPanel.h"

EditorRightPanel::EditorRightPanel(int width_, int height_, QWidget* parent) :
        QWidget(parent) {

    setFixedHeight(height_);

    auto layout = new QVBoxLayout(this);

    layout->addWidget(AddButton("key"));
    layout->addWidget(AddButton("box"));
    layout->addWidget(AddButton("player2"));
    layout->addWidget(AddButton("add_v"));
    layout->addWidget(AddButton("sub_v"));
    layout->addWidget(AddButton("add_h"));
    layout->addWidget(AddButton("sub_h"));

    codes.push_back("k");
    codes.push_back("b");
    codes.push_back("p");
    codes.push_back("_av");
    codes.push_back("_sv");
    codes.push_back("_ah");
    codes.push_back("_sh");

}

QPushButton* EditorRightPanel::AddButton(QString file_name) {
    buttons.push_back(new QPushButton(this));
    buttons.back()->setFixedSize(96, 96);
    buttons.back()->setStyleSheet("QPushButton {border-image: url(:resources/textures/" +
                                  file_name +".png) 0 0 0 0 stretch stretch;}");
    connect(buttons.back(), SIGNAL(clicked()), this, SLOT(GetCurrent()));
    return buttons.back();
}

void EditorRightPanel::GetCurrent() {
    emit ChooseCurrent(codes[std::find(buttons.begin(), buttons.end(), sender()) - buttons.begin()]);
}
