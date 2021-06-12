#include "../headers/wall.hpp"
#include "../headers/utils.hpp"

Wall::Wall(Vector2f position) {
    shape.setSize(Vector2f(BLOCK, BLOCK));
    shape.setFillColor(Color::White);
    shape.setPosition(position);
    position = position;
}

Vector2f Wall::getPosition() {
    return position;
}

RectangleShape Wall::getShape() {
    return shape;
}
