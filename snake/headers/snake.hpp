#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "snakesection.hpp"

#define snakeInitialPosition {Vector2f(100, 100), Vector2f(80, 100), Vector2f(60, 100)}
#define head sections[0]

using namespace sf;
using namespace std;

class Snake {
private:
    vector<SnakeSection> sections;
    int direction;

public:
    Snake() {};
    
    int getDirection();
    void setDirection(int direction);
    
    void newSnake();
    void addSection();

    bool intersects(const Rect<float> &rectangle);
    bool ate(const Rect<float> &rectangle);
    bool ateSelf();

    void update();
    void draw(RenderWindow &window);
};

#endif //SNAKE_HPP