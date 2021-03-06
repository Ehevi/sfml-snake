#include <iostream>
#include "../headers/utils.hpp"

void loadFont(Font &font) {
    if (!font.loadFromFile("font/Poppins-Regular.otf")) {
        std::cout << "Failed to load font! :(";
        return;
  }
}

void center(Text &text) {
    text.setPosition(SCREEN_WIDTH / 2 - text.getGlobalBounds().width / 2, SCREEN_HEIGHT / 2 - text.getGlobalBounds().height / 2);
}

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

void initCheckBox(RectangleShape &checkBox, int y) {
    checkBox.setSize(_CheckBoxSize);
    checkBox.setOutlineColor(Color::Magenta);
    checkBox.setFillColor(Color::Black);
    checkBox.setOutlineThickness(3);
    centerHorizontally(checkBox, y);
}

void handleCheckBoxSelection(RectangleShape &checkBox, bool predicate) {
    if (predicate) checkBox.setFillColor(Color::Cyan);
}

void highlightOnHover(Text &text, Vector2f mouse) {
    text.setFillColor(text.getGlobalBounds().contains(mouse)? Color::Yellow : Color::White);
}

void highlightOnHover(RectangleShape &shape, Vector2f mouse) {
    shape.setFillColor(shape.getGlobalBounds().contains(mouse)? Color::Yellow : Color::Black);
}

void highlightChosen(Text &text) {
    text.setFillColor(Color::Cyan);
}
