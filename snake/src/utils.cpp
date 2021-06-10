#include "../headers/utils.hpp"

void centerHorizontally(Text &text, int y) {
    text.setPosition(SCREEN_WIDTH / 2 - text.getGlobalBounds().width / 2, y);
}

void centerHorizontally(RectangleShape &shape, int y) {
    shape.setPosition(SCREEN_WIDTH / 2 - shape.getGlobalBounds().width / 2, y);
}