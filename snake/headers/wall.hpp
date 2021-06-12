#ifndef WALL_HPP
#define WALL_HPP

#include <SFML/Graphics.hpp>

using namespace sf;

class Wall {
private:
    Vector2f position;
    RectangleShape shape;

public:
    explicit Wall(Vector2f Position);

    Vector2f getPosition();
    RectangleShape getShape();

};

#endif //WALL_HPP