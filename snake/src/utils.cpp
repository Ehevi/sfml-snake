#include "../headers/utils.hpp"

void centerHorizontally(Text &text, int y) {
    text.setPosition(SCREEN_WIDTH / 2 - text.getGlobalBounds().width / 2, y);
}

void centerHorizontally(RectangleShape &shape, int y) {
    shape.setPosition(SCREEN_WIDTH / 2 - shape.getGlobalBounds().width / 2, y);
}

void centerHorizontally(Text &text1, Text &text2, Text &text3, int y) {
    float space = SCREEN_WIDTH / 2 - text2.getGlobalBounds().width / 2;
    text1.setPosition(space / 2 - text1.getGlobalBounds().width / 2, y);
    text2.setPosition(space, y);
    text3.setPosition(space + text3.getGlobalBounds().width, y);
}

void setCheckBox(RectangleShape &checkBox, int y) {
    checkBox.setSize(_CheckBoxSize);
    checkBox.setOutlineColor(Color::Magenta);
    checkBox.setFillColor(Color::Black);
    checkBox.setOutlineThickness(3);
    centerHorizontally(checkBox, y);
}