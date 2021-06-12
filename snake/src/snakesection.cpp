#include "../headers/snakesection.hpp"
#include "../headers/utils.hpp"

SnakeSection::SnakeSection(Vector2f startPosition) {
    section.setSize(Vector2f(BLOCK, BLOCK));
    section.setFillColor(Color::Green);
    section.setPosition(startPosition);
    position = startPosition;
}

Vector2f SnakeSection::getPosition() {
    return position;
}

void SnakeSection::setPosition(Vector2f newPosition) {
    position = newPosition;
}

RectangleShape SnakeSection::getShape() {
    return section;
}

void SnakeSection::update() {
    section.setPosition(position);
}
